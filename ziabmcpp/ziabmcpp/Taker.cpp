// Taker.cpp
// Taker class

#include "stdafx.h"


#include "Taker.h"

Taker::Taker(const int tnum, const int maxq)
	: ZITrader(tnum, maxq)
{
	traderType = 'T';
}

void Taker::processSignal(Step step, double qTake, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Prc price;
	Side side;

	if (dist(engine) < qTake)
	{
		price = 2000000;
		side = Side::BUY;
	}
	else
	{
		price = 0;
		side = Side::SELL;
	}
	quoteCollector.emplace_back(makeAddQuote(step, side, price));
}