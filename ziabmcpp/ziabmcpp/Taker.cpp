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
	std::uniform_real_distribution<> distUreal(0, 1);

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
	Order q = makeAddQuote(step, side, price);
	quoteCollector.push_back(q);
}