use crate::types::OrderBook;
use std::collections::HashMap;

pub struct MyOrderBook {
    orders: HashMap<u64, Order>,

    bids: Vec<i64>, // price -> total qty
    asks: Vec<i64>, // price -> total qty

    best_bid: i64,
    best_ask: i64,
}

#[derive(Clone)]
struct Order {
    side: i32,
    price: i64,
    quantity: i64,
}

const MAX_PRICE: usize = 1_000_000;

impl OrderBook for MyOrderBook {
    fn new() -> Self {
        Self {
            orders: HashMap::with_capacity(1_000_000),

            bids: vec![0; MAX_PRICE + 1],
            asks: vec![0; MAX_PRICE + 1],

            best_bid: 0,
            best_ask: MAX_PRICE as i64,
        }
    }

    #[inline(always)]
    fn add_order(&mut self, id: u64, side: i32, price: i64, quantity: i64) {
        self.orders.insert(id, Order { side, price, quantity });

        if side == 0 {
            let p = price as usize;
            self.bids[p] += quantity;

            if price > self.best_bid {
                self.best_bid = price;
            }
        } else {
            let p = price as usize;
            self.asks[p] += quantity;

            if self.asks[self.best_ask as usize] == 0 || price < self.best_ask {
                self.best_ask = price;
            }
        }
    }

    #[inline(always)]
    fn cancel_order(&mut self, id: u64) {
        let Some(order) = self.orders.remove(&id) else {
            return;
        };

        if order.side == 0 {
            let p = order.price as usize;
            self.bids[p] -= order.quantity;

            if order.price == self.best_bid && self.bids[p] == 0 {
                while self.best_bid > 0 && self.bids[self.best_bid as usize] == 0 {
                    self.best_bid -= 1;
                }
            }
        } else {
            let p = order.price as usize;
            self.asks[p] -= order.quantity;

            if order.price == self.best_ask && self.asks[p] == 0 {
                while self.best_ask < MAX_PRICE as i64
                    && self.asks[self.best_ask as usize] == 0
                {
                    self.best_ask += 1;
                }
            }
        }
    }

    #[inline(always)]
    fn best_bid(&self) -> i64 {
        if self.best_bid == 0 { 0 } else { self.best_bid }
    }

    #[inline(always)]
    fn best_ask(&self) -> i64 {
        if self.best_ask == MAX_PRICE as i64 { 0 } else { self.best_ask }
    }
}
