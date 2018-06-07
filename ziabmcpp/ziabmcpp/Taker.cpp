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
	if (dist(engine) < qTake)
		quoteCollector.emplace_back(makeAddQuote(step, Side::BUY, 2000000));
	else
		quoteCollector.emplace_back(makeAddQuote(step, Side::SELL, 0));
}