// Orderbook.h

#pragma once

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <list>			// std::list
#include <map>			// std::map
#include <string>		// std::string
#include <tuple>        // std::tuple
#include <unordered_map>        // std::unordered_map
#include <vector>        // std::vector

using Id = std::string;
using Qty = unsigned;
using Prc = unsigned;

enum struct Side { BUY, SELL };

struct Quote { Id id; Qty qty; };
using Quotes = std::list<Quote>;

struct Level {Qty qty; Quotes quotes;};
using BookSide = std::map<Prc, Level>;

using BLQ = std::tuple<BookSide*, BookSide::iterator, Quotes::reverse_iterator>;
using Lookup = std::unordered_map<Id, BLQ>;

struct Execution {Id id; Prc prc; Qty executed; Qty remaining;};


class Orderbook
{
public:
	Orderbook();
	Lookup lookup;
	BookSide bids, asks;
	void add(Id, Side, Prc, Qty);
	void modify(Id, Qty);
	std::vector<Execution> cross(Side, Prc, Qty);
	auto bid();
	auto ask();
};

#endif