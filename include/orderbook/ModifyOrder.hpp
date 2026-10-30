#pragma once

#include "Order.hpp"
#include "OrderType.hpp"
#include "SideType.hpp"
#include "Types.hpp"

#include <memory>

class ModifyOder {
    public:
        ModifyOder(OrderId orderId, Price price, Quantity quantity, Side side):
            orderId_{ orderId },
            price_{ price },
            quantity_{ quantity },
            side_{ side }
        { }

        OrderId GetOrderId() const {
            return orderId_;
        }

        Price GetPrice() const {
            return price_;
        }

        Quantity GetQuantity() const {
            return quantity_;
        }

        Side GetSide() const {
            return side_;
        }

        OrderPointer ToOrderPointer(OrderType type) const {
            return std::make_shared<Order>(GetOrderId(), type, GetQuantity(), GetSide(), GetPrice());
        }

    private:
        OrderId orderId_;
        Price price_;
        Quantity quantity_;
        Side side_;
};
