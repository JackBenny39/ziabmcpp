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
	OrderId oid = std::make_pair(tid, id);
	auto& blq = lookup[oid];
	auto& b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	l->second.qty -= qty;
	l->second.quotes.erase(q);
	l->second.ocnt--;
	if (!(l->second.ocnt))
		b->erase(l);
	lookup.erase(oid);
}

void Orderbook::modify(traderId tid, Id id, Qty qty)
{
	OrderId oid = std::make_pair(tid, id);
	auto& blq = lookup[oid];
	auto& b = std::get<0>(blq);
	auto& l = std::get<1>(blq);
	auto& q = std::get<2>(blq);
	l->second.qty -= qty;
	q->qty -= qty;
	if (!(q->qty))
	{
		l->second.quotes.erase(q);
		l->second.ocnt--;
		if (!(l->second.ocnt)) { b->erase(l); }
		lookup.erase(oid);
	}
}

void Orderbook::addTrade(traderId restid, Id restoid, Step reststep, traderId incid, Id incoid, Step incstep, Qty qty, Side side, Prc price)
{
	trades.emplace_back(ExTrade{ restid, restoid, reststep, incid, incoid, incstep, qty, side, price });
}

void Orderbook::confirmTrade(traderId restid, Id restoid, Step reststep, Qty qty, Side side, Prc price)
{
	tradeconfirms.emplace_back(TConfirm{ restid, restoid, reststep, qty, side, price });
}

void Orderbook::confirmModify(traderId restid, Id restoid, Step reststep, Qty qty, Side side)
{
	modifyconfirms.emplace_back(MConfirm{ restid, restoid, reststep, qty, side});
}

//std::vector<Execution> Orderbook::cross(Side side, Prc price, Qty qty)
//{
//	
//}

auto Orderbook::bid() { return bids.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(bids.rbegin()->first, bids.rbegin()->second.qty); }
auto Orderbook::ask() { return asks.empty() ? std::make_tuple(Prc(0), Qty(0)) : std::make_tuple(asks.begin()->first, asks.begin()->second.qty); }

std::vector<TopOfBook>::iterator Orderbook::bookTop(Step step)
{
	auto bestbid = bid();
	auto bestask = ask();
	return tob.emplace(tob.end(), TopOfBook{ step, std::get<0>(bestbid), std::get<1>(bestbid), std::get<0>(bestask), std::get<1>(bestask) });
}

void Orderbook::bookTop2(Step step)
{
	auto bestbid = bid();
	auto bestask = ask();
	tob.emplace_back(TopOfBook{ step, std::get<0>(bestbid), std::get<1>(bestbid), std::get<0>(bestask), std::get<1>(bestask) });
}