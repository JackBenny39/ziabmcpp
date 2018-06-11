// ZITrader.h

#pragma once

#ifndef ZITRADER_H
#define ZITRADER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>
#include <unordered_set>
#include <vector>		// std::vector

using stepset = std::unordered_set<Step>;


class ZITrader
{
public:
	ZITrader(const Step, const int, const int, const Prc); // ZITrader, Taker, PennyJumper
	ZITrader(const int, const int, Side, const unsigned, const unsigned, std::mt19937 &, std::uniform_int_distribution<> &); //Informed
	ZITrader(const Step, const int, const int, const double, const Prc); // Provider, Provider5
	ZITrader(const Step, const int, const int, const double, const int, const int); // Provider, MarketMaker, MarketMaker5
	Step arrInt;
	traderId tId;
	Qty orderSize;
	char traderType;
	Side side; // must precede price
	Prc price, mpi;
	double delta;
	int numQuotes, quoteRange;
	unsigned position;
	int64_t cashFlow;
	stepset steps;
	Order makeAddQuote(Step, Side, Prc);
	std::vector<Order> quoteCollector;
private:
	Id quoteSequence;
};

#endif