// Orderbook.cpp
// Orderbook class

#include "stdafx.h"

#include "Orderbook.h"

Orderbook::Orderbook()
{

}

void Orderbook::add(Id id, Side side, Prc prc, Qty qty)
{

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