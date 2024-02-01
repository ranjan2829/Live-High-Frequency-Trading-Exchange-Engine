
enum BidorAsk{
    Bid,
    Ask,
}

struct Order{
    size: f64,
    bid_or_ask:BidorAsk,


}
imple Order{
    fn new(bid_or_ask:BidorAsk,size:f64)->Order{
        Order{bid_or_ask,size}
    }
}
fn main(){
    
}