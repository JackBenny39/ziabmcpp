// Orderbook.cpp
// Orderbook class

#include "stdafx.h"

#include "Orderbook.h"

Orderbook::Orderbook()
{

}

void Orderbook::add(Id id, Side side, Prc prc, Qty qty)
{
	if (side == Side::BUY)
		if (bids.count(prc) > 0)
		{
			bids.at(prc).qty += qty;
			bids.at(prc).quotes.emplace_back(Quote{ id, qty });
		}
		else
			bids.emplace(prc, Level{ qty, Quotes{ Quote{ id, qty } } });
	else
		if (asks.count(prc) > 0)
		{
			asks.at(prc).qty += qty;
			asks.at(prc).quotes.emplace_back(Quote{ id, qty });
		}
		else
			asks.emplace(prc, Level{ qty, Quotes{ Quote{ id, qty } } });
}

void Orderbook::modify(Id id, Qty qty)
{

}

//std::vector<Execution> Orderbook::cross(Side side, Prc price, Qty qty)
//{
//	
//}

auto Orderbook::bid() { return bids.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(bids.rbegin()->first, bids.rbegin()->second.qty); }
auto Orderbook::ask() { return asks.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(asks.begin()->first, asks.begin()->second.qty); }