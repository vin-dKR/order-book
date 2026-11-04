#include <iostream>
#include <vector>
#include <memory>

#include "orderbook/OrderBook.hpp"
#include "orderbook/Order.hpp"
#include "orderbook/OrderType.hpp"
#include "orderbook/SideType.hpp"

int main() {
    Orderbook orderbook;
    OrderId orderId = 1;

    orderbook.AddOrders(std::make_shared<Order>(orderId, OrderType::GoodTillCancel, 10, Side::Buy, 100));

    std::cout << orderbook.Size() << std::endl;

    orderbook.CancelOrder(orderId);

    std::cout << orderbook.Size() << std::endl;

    return 0;
}
