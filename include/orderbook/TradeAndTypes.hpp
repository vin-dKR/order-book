#pragma once

#include "Types.hpp"

#include <vector>

struct TradeInfo {
    OrderId orderId;
    Price price;
    Quantity quantity;
};

class Trade {
    public:
        Trade(const TradeInfo& bid, const TradeInfo& ask):
            bid_{ bid },
            ask_{ ask }
        { }

        const TradeInfo& GetBidTrade() const {
            return bid_;
        }

        const TradeInfo& GetAskTrade() const {
            return ask_;
        }

    private:
        TradeInfo bid_;
        TradeInfo ask_;
};

using Trades = std::vector<Trade>;
