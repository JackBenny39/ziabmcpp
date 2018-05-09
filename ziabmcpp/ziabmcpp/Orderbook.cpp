// Orderbook.cpp
// Orderbook class

#include "stdafx.h"

#include <iostream>

#include "Orderbook.h"

Orderbook::Orderbook()
{
	orderSequence = 0;
}

void Orderbook::addHistory(Order &q)
{
	history.emplace_back(ExOrder{ ++orderSequence, q.id, q.oid, q.step, q.otype, q.qty, q.side, q.price });
}

void Orderbook::addBook(traderId tid, Id id, Side side, Prc prc, Qty qty)
{
	auto b = side == Side::BUY ? &bids : &asks;
	if (b->count(prc) > 0)
	{
		b->at(prc).qty += qty;
		b->at(prc).ocnt++;
		b->at(prc).quotes.emplace_back(Quote{ tid, id, qty, prc, side });
	}
	else
		b->emplace(prc, Level{ qty, 1, Quotes{ Quote{ tid, id, qty, prc, side } } });
	auto l = b->find(prc);
	auto q = l->second.quotes.begin();
	lookup[std::make_pair(tid, id)] = std::make_tuple(b, l, q);
	std::cout << "Trader: " << tid << ", Order: " << id << ", Quote info:" << q->oid << std::endl;
}

void Orderbook::addBook2(traderId tid, Id id, Side side, Prc prc, Qty qty)
{
	auto b = side == Side::BUY ? &bids : &asks;
	auto l = b->find(prc);
	if (l == b->end())
		l = b->emplace(std::make_pair(prc, Level{ 0, 0, Quotes{ } })).first;
	l->second.ocnt++;
	l->second.qty += qty;
	auto q = l->second.quotes.emplace(l->second.quotes.end(), Quote{ tid, id, qty, prc, side });
	lookup[std::make_pair(tid, id)] = std::make_tuple(b, l, q);
}

void Orderbook::remove(traderId tid, Id id, Qty qty)
{
	auto& blq = lookup[std::make_pair(tid, id)];
	auto& b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	l->second.qty -= qty;
	l->second.ocnt--;
	l->second.quotes.erase(q);
	if (!(l->second.ocnt))
		b->erase(l);
}

void Orderbook::modify(traderId tid, Id id, Qty qty)
{
	auto& blq = lookup[std::make_pair(tid, id)];
	auto& b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	q->qty -= qty;
	l->second.qty -= qty;
	if (!(q->qty))
	{
		l->second.quotes.erase(q);
		l->second.ocnt--;
		if (!(l->second.ocnt)) { b->erase(l); }
//		if (!(--l->second.ocnt)) { b->erase(l); }
	}
}

//std::vector<Execution> Orderbook::cross(Side side, Prc price, Qty qty)
//{
//	
//}

auto Orderbook::bid() { return bids.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(bids.rbegin()->first, bids.rbegin()->second.qty); }
auto Orderbook::ask() { return asks.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(asks.begin()->first, asks.begin()->second.qty); }