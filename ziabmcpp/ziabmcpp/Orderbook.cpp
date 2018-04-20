// Orderbook.cpp
// Orderbook class

#include "stdafx.h"

#include "Orderbook.h"

Orderbook::Orderbook()
{
	orderSequence = 0;
}

void Orderbook::addHistory(Order &q)
{
	history.emplace_back(ExOrder{ ++orderSequence, q.id, q.oid, q.step, q.otype, q.qty, q.side, q.price });
}

void Orderbook::add(Id id, Side side, Prc prc, Qty qty)
{
	auto b = side == Side::BUY ? &bids : &asks;
	if (b->count(prc) > 0)
	{
		b->at(prc).qty += qty;
		b->at(prc).quotes.emplace_back(Quote{ id, qty });
	}
	else
		b->emplace(prc, Level{ qty, Quotes{ Quote{ id, qty } } });
	auto l = b->find(prc);
	auto q = l->second.quotes.rbegin();
	lookup[id] = std::make_tuple(b, l, q);
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