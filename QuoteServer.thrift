struct TradeT {
  1: i32 price,
  2: i32 amount,
  3: string symbol
  4: i32 type
}

struct LimitOrderBookT {
	1: i32 sth,
	2: string id
}

struct SymbolT {
	1: string id
}

service QuoteAnalisys {
	void subscribe(1: SymbolT symbol);
	TradeT getTrade();
	LimitOrderBookT getLimitOrderBook();
}