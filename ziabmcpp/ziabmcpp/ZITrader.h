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
	Qty orderSize;
	char traderType;
	Side side;
	traderId tId;
	Prc price;
	double delta;
	int numQuotes;
	int quoteRange;
	unsigned position;
	int64_t cashFlow;
	Prc mpi;
	Order makeAddQuote(Step, Side, Prc);
	std::vector<Order> quoteCollector;
private:
	Id quoteSequence;
};

#endif