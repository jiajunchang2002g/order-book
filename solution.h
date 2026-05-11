#pragma once
// Challenge 01: Order Book
// Edit this file and solution.cpp to implement your solution.

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace hftu {

class OrderBook {
public:
    // Add a new order. side: false=buy(bid), true=sell(ask)
    void add_order(uint32_t id, bool side, int32_t price, int32_t quantity);

    // Cancel an order by ID. No-op if ID doesn't exist.
    void cancel_order(uint32_t id);

    // Return highest bid price, or 0 if no bids.
    int32_t best_bid();

    // Return lowest ask price, or 0 if no asks.
    int32_t best_ask();

    OrderBook() : best_bid_price_(0), best_ask_price_(0) {
        orders_.resize(1'000'000, {0, 0, false});
        bids_.resize(1'000'001, 0); 
        asks_.resize(1'000'001, 0);
    }

private:
    // Replace these with your own data structures
    struct Order {
        int32_t price;
        int32_t quantity;
        bool side; // false=bid, true=ask
    };

    using OrderId = uint32_t;
    using Price = int32_t;

    std::vector<Order> orders_; // order ID to order 
    std::vector<Price> bids_;   // price level to quantity
    std::vector<Price> asks_;

    Price best_bid_price_;
    Price best_ask_price_;
};

} // namespace hftu