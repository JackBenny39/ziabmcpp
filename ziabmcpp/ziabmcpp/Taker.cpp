// Taker.cpp
// Taker class

#include "stdafx.h"


#include "Taker.h"

Taker::Taker(const int tnum, const int maxq)
	: ZITrader(tnum, maxq)
{
	traderType = 'T';
	tId = tnum;
}

void Taker::processSignal(Step step, double qTake, double buyP)
{
	Prc price;
	Side side;

	if (buyP < qTake)
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