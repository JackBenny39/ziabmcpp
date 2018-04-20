// Taker.cpp
// Taker class

#include "stdafx.h"

#include "Taker.h"

Taker::Taker(const int tnum, const int maxq)
	: ZITrader(tnum, maxq)
{
	traderType = 'T';
	tId = traderId{ traderType, tnum };
}

void Taker::processSignal(int step, double qTake, double buyP)
{
	int price;
	char side;

	if (buyP < qTake)
	{
		price = 2000000;
		side = 'B';
	}
	else
	{
		price = 0;
		side = 'S';
	}
	Order q = makeAddQuote(step, side, price);
	quoteCollector.push_back(q);
}