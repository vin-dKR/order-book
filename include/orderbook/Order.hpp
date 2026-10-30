#pragma once

#include "OrderType.hpp"
#include "SideType.hpp"
#include "Types.hpp"

#include <format>
#include <list>
#include <memory>
#include <stdexcept>

class Order {
    public:
        Order(OrderId orderId, OrderType orderType, Quantity quantity, Side side, Price price):
            side_{ side },
            price_{ price },
            orderId_{ orderId },
            initialQuantity_{ quantity },
            orderType_{ orderType },
            remainingQuantity_{ quantity }
        { }

    private:
        OrderId GetOrderId() const {
            return orderId_;
        }

        Side GetOderSide() const {
            return side_;
        }

        Price GetPrice() const {
            return price_;
        }

        OrderType GetOrderType() const {
            return orderType_;
        }

        Quantity GetInitialQuantity() const {
            return initialQuantity_;
        }

        Quantity GetRemainingQuantity() const {
            return remainingQuantity_;
        }

        Quantity GetFillQuantity() const {
            return GetInitialQuantity() - GetRemainingQuantity();
        }

        void Fill(Quantity quantity) {

            if (quantity > GetRemainingQuantity())
                throw std::logic_error(std::format("Order ({}) - this has quantity < remainingQuantity", GetOrderId()));

            remainingQuantity_ -= quantity;
        } 

    public:
        Side side_;
        Price price_;
        OrderId orderId_;
        Quantity initialQuantity_;
        OrderType orderType_;
        Quantity remainingQuantity_;
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;
