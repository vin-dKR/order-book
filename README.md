# Order Book

I'm rebuilding an order book in C++20 by following [Coding Jesus' order book tutorial](https://www.youtube.com/watch?v=XeLWe0Cx_Lg).

The idea is to understand how an order book works properly: how buy and sell orders are stored, how prices are organised, and how orders get matched. I'm building it step by step and learning the C++ side along the way, especially STL containers, smart pointers, and organising code across files.

I started with everything in `app/main.cpp`. As the code grew, I moved the types and classes into separate headers so it is easier to follow and work on.

## Where things stand

This is still a work in progress. The basic types and data structures are in place; the matching logic and a working demo are still pending.

What I have so far:

- Shared types for prices, quantities, and order IDs.
- Buy and sell sides, with `GoodTillCancel` and `FillAndKill` order type definitions.
- Classes for orders, modification requests, and trade information.
- Structures for bid and ask price-level information.
- Internal bid/ask price maps and an order ID lookup for the book.

The order types are defined, but their execution rules are still to be implemented. `main.cpp` currently contains only the entry point.

## Project layout

```text
order-book/
├── app/
│   └── main.cpp                  # Application entry point
├── include/
│   └── orderbook/
│       ├── Types.hpp             # Price, quantity, and order ID aliases
│       ├── SideType.hpp          # Buy and sell sides
│       ├── OrderType.hpp         # Order type definitions
│       ├── Order.hpp             # Order data and existing fill bookkeeping
│       ├── ModifyOrder.hpp       # Order modification request
│       ├── LevelsType.hpp        # Price-level information
│       ├── OrderBookLevelInfos.hpp # Bid and ask level snapshots
│       ├── TradeAndTypes.hpp     # Trade information and trade collections
│       └── OrderBook.hpp         # Internal book storage
└── README.md
```

The code currently lives in the headers. I've also kept these folders locally for the next stages; they are empty at the moment:

| Folder | Intended use |
| --- | --- |
| `src/` | Implementation files as the logic grows |
| `test/` | Tests for order handling and matching |
| `example/` | Small examples of using the book |
| `docs/` | Notes on the design and matching rules |
| `build/` | Generated build output |

## Building the current entry point

Use a C++20 compiler and standard library with support for `std::format`.

From the project root:

```sh
mkdir -p build
c++ -std=c++20 -Wall -Wextra -Wpedantic -Iinclude app/main.cpp -o build/order-book
./build/order-book
```

At present, this builds the placeholder application, which exits without printing anything. It does not exercise the order-book headers yet. CMake and automated tests are still to be set up.

## What I'll work on next

- Add the public operations for placing, cancelling, and modifying orders.
- Implement matching and the execution rules for the order types.
- Connect the book to a small example in `main.cpp`.
- Add tests for partial fills, unmatched orders, and cancellation.
- Set up a repeatable build and document the behaviour as it takes shape.

## Credit

The starting design and walkthrough come from Coding Jesus' [Coding a multi-order type orderbook in C++ from scratch](https://www.youtube.com/watch?v=XeLWe0Cx_Lg). This repository is my rebuild of that project as I work through it and understand the decisions behind the code.
