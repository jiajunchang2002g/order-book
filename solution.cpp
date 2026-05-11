// Challenge 01: Order Book — Skeleton Implementation
// This is a naive reference. You can do much better!

#include "solution.h"

namespace hftu {

void OrderBook::add_order(uint32_t id, bool side, int32_t price, int32_t quantity) {
    orders_[id] = {price, quantity, side};
    if (side == false) {
        bids_[price] += quantity;
        if (price > best_bid_price_) {
            best_bid_price_ = price;
        }
    } else {
        asks_[price] += quantity;
        if (price < best_ask_price_ || best_ask_price_ == 0) {
            best_ask_price_ = price;
        }
    }
}

void OrderBook::cancel_order(uint32_t id) {
    auto order = orders_[id];
    if (order.side == false) {
        bids_[order.price] -= order.quantity;
    } else {
        asks_[order.price] -= order.quantity;
    }
    orders_[id] = {0, 0, false}; // mark as cancelled
}

int32_t OrderBook::best_bid() {
    while (best_bid_price_ > 0 &&
           bids_[best_bid_price_] == 0) {
        --best_bid_price_;
    }

    return best_bid_price_;
}

int32_t OrderBook::best_ask() {
    while (best_ask_price_ <= 1000000 &&
           asks_[best_ask_price_] == 0) {
        ++best_ask_price_;
    }
    if (best_ask_price_ > 1000000) {
        best_ask_price_ = 0;
    }

    return best_ask_price_;
}

} // namespace hftu