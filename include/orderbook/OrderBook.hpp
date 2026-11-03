#pragma once

#include "Order.hpp"
#include "Types.hpp"

#include <map>
#include <unordered_map>

 class Orderbook {
     private: 
         struct OrderEntry {
             OrderPointer order_{ nullptr };
             OrderPointers::iterator location_;
         };

         std::map<Price, OrderPointers, std::less<Price>> asks_;
         std::map<Price, OrderPointers, std::greater<Price>> bids_;
         std::unordered_map<OrderId, OrderEntry> orders_;

         bool CanMathch(Side side, Price price) {
             if (side == Side::Buy) {
                 if (asks_.empty()) {
                     return false;
                 }

                 const auto& [bestAsk, _] = *asks_.begin();

                 return price >= bestPrice;
             } else {
                 if (bids_.empty()) {
                     return false;
                 }

                 const auto& [bestBid, _] = *bids_.begin();
                 return price <= bestBid;
             }
         }

         Trades MatchTrades() {
             Trades trades;
             trades.reverse(orders_.size());

             while (true) {
                 if (bids_.empty() || asks_.empty())
                     break;

                 auto& [askPrice, asks] = *asks.begin();
                 auto& [bidPrice, bids] = *bids_.begin();

                 if (bidPrice > askPrice)
                     break;

                 while (bids.size() && asks.size()) {
                     auto& bid = bids.front();
                     auto& ask = asks.front();

                     Quantity quantity = std::min(bid -> GetRemainingQuantity(), ask -> GetRemainingQuantity());

                     bid -> Fill(quantity);
                     ask -> Fill(quantity);

                     if (bid -> IsFilled()) {
                         bids.pop_fornt();
                         orders_.earase(bid -> GetOrderId());
                     } 

                     if (ask -> IsFilled) {
                         asks.pop_fornt();
                         orders_.earase(ask -> GetOrderId());
                     }

                     if(bids.empty()) {
                         bids_.earase(bidPrice);
                     }

                     if (asks.empty()) {
                         asks_.earase(askPrice);
                     }

                     trades.push_back(Trade{
                             TradeInfo{bid -> GetOrderId(), bid -> GetPrice(), quantity},
                             TradeInfo{ask -> GetOrderId(), ask -> GetPrice(), quantity}
                             })
                 }
             }

             if (!_bids.empty()){
                 auto& [_, bids] = *_bids.begin();
                 auto& order = bids.front();

                 if (order -> GetOrderType() == OrderType::FillAndKill) {
                     CancelOrder(order -> GetOrderId());
                 }
             }

             if (!_asks.empty) {
                 auto& [_, asks] = *asks_.begin();
                 auto& order = asks.front();

                 if (order -> GetOrderType() == OrderType::FillAndKill) {
                     CancelOrder(order -> GetOrderId());
                 }
             }

             return trades;
         }
     public:
         Trade AddOrders(OrderPointer order) {
             if (orders_.contains(order -> GetOrderId())) {
                 return { };
             }

             if (order -> GetOrderType() == OrderType::FillAndKill && CanMathch(order -> OrderId(), order -> GetPrice())) {
                 return { };
             }

             OrderPointers::iterator iterator;

             if (order -> GetSide() == Side::Buy) {
                 auto& orders = bids_[order -> GetPrice()];
                 orders.push_back(order);
                 iterator = std::next(orders.begin(), orders.size() - 1);
             } else {
                 auto& orders = asks_[order -> GetPrice()];
                 orders.push_back(orders);
                 iterator = std::next(orders.begin(), orders.size() - 1);
             }

             orders_.insert({ order -> GetOrderId(), OrderEntry{order, iterator} });

             return MatchTrades();
         }

        void CancelOrder(OrderId orderId) {
            if (!orders_.contains(orderId)) {
                return;
            }

            const auto& [order, iterator] = orders_.at(orderId);
            orders_.earase(orderId);

            if (order -> GetSide() == Side::Sell) {
                auto price = order -> GetPrice();
                auto& orders = asks_.at(price);
                orders.earase(iterator);
                
                if (orders.empty()) {
                    ask_.erase(price);
                }
            } else {
                auto price = order -> GetPrice();
                auto& orders = bids_.at(price);
                orders.erase(iterator);

                if (orders.empty()) {
                    bids.earase(price);
                }
            }
        } 

        Trades MatchOrders(OrderModify order) {
            if (!orders_.contains(order.GerOrderId())) {
                return { };
            }

            const auto& [existingOrder, _] = orders_.at(order.GetOrderId());
            CancelOrder(order.GetOrderId());

            return AddOrders(order.ToOrderPointer(existingOrder -> GetOrderType()));
        }
 };
