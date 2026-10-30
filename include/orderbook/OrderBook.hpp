#pragma once

#include "Order.hpp"
#include "Types.hpp"

#include <functional>
#include <map>
#include <unordered_map>

 class Orderbook {
     private: 
         struct OrderEntry {
             OrderPointer order_{ nullptr };
             OrderPointers::iterator location_;
         };

         std::map<Price, OrderPointers, std::greater<Price>> bids_;
         std::map<Price, OrderPointers, std::less<Price>> asks_;
         std::unordered_map<OrderId, OrderEntry> orders_;
 };
