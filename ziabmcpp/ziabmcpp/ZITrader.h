// ZITrader.h

#pragma once

#ifndef ZITRADER_H
#define ZITRADER_H

#include "stdafx.h"

#include "Sharedstx.h"

#include <random>
#include <vector>		// std::vector


class ZITrader
{
public:
	ZITrader(const int, const int);
	ZITrader(const int, const int, Side);
	ZITrader(const int, const int, const double);
	ZITrader(const int, const int, const double, const int, const int);
	ZITrader(const int, const int, const Prc);
	traderId tId;
	Qty orderSize;
	char traderType;
	Side side; // must precede price
	Prc price, mpi;
	double delta;
	int numQuotes, quoteRange;
	unsigned position;
	int64_t cashFlow;
	Order makeAddQuote(Step, Side, Prc);
	std::vector<Order> quoteCollector;
private:
	Id quoteSequence;
};

#endif