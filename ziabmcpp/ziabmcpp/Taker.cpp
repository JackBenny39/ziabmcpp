// Taker.cpp
// Taker class

#include "stdafx.h"


#include "Taker.h"

Taker::Taker(const Step arr, const int tnum, const int maxq, const Prc mpi)
	: ZITrader(arr, tnum, maxq, mpi)
{
	traderType = 'T';
}

void Taker::processSignal(Step step, double qTake, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	quoteCollector.clear();
	if (dist(engine) < qTake)
		quoteCollector.emplace_back(makeAddQuote(step, Side::BUY, 2000000));
	else
		quoteCollector.emplace_back(makeAddQuote(step, Side::SELL, 0));
}