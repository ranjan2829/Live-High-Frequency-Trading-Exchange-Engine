use std::collections::HashMap;
#[derive(Debug)]
enum BidorAsk {
    Bid,
    Ask,
}
#[derive(Debug)]
struct OrderBook {
    ask: HashMap<Price, Limit>,
    bid: HashMap<Price, Limit>,
}
impl OrderBook {
    fn new() -> OrderBook {
        OrderBook {
            ask: HashMap::new(),
            bid: HashMap::new(),
        }
    }
    fn add_order(&mut self, price: f64, order: Order) {
        match order.bid_or_ask {
            BidorAsk::Bid => {
                let price = Price::new(price);
                let limit = self.bid.get_mut(&price);
                match (limit) {
                    Some(limit) => println!("Already got a n limit !"),
                    None => println!(" new limit to be created"),
                }
            }
            BidorAsk::Ask => {}
        }
    }
}
#[derive(Debug, Eq, Hash, PartialEq)]
struct Price {
    integral: u64,
    fractional: u64,
    scalar: u64,
}

impl Price {
    fn new(price: f64) -> Price {
        let scalar = 100000;
        let integral = price as u64;
        let fractional = ((price % 1.0) * scalar as f64) as u64;
        Price {
            scalar,
            integral,
            fractional,
        }
    }
}

#[derive(Debug)]
struct Limit {
    price: Price,
    orders: Vec<Order>,
}
impl Limit {
    fn new(price: f64) -> Limit {
        Limit {
            price: Price::new(price),
            orders: Vec::new(),
        }
    }
    fn add_order(&mut self, order: Order) {
        self.orders.push(order);
    }
}
#[derive(Debug)]

struct Order {
    size: f64,
    bid_or_ask: BidorAsk,
}
impl Order {
    fn new(bid_or_ask: BidorAsk, size: f64) -> Order {
        Order { bid_or_ask, size }
    }
}
fn main() {
    //let price=Price::new(50.5);
    //let mut limit=Limit::new(1200.0);
    //println!("{:?}",limit);
    //println!("{:?}",price);
    let buy_order = Order::new(BidorAsk::Bid, 1199.5);
    let sell_order = Order::new(BidorAsk::Ask, 1202.5);
    //limit.add_order(buy_order);
    //limit.add_order(sell_order);
    println!("{:?}", limit);
    let mut orderbook = OrderBook::new();
    orderbook.add_order(1199.5, buy_order);
    println!("{:?}", orderbook);
} //hi ranjan it's me trading the rust servers my man !
