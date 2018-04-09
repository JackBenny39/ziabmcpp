// Taker.cpp
// Taker class

#include "stdafx.h"

#include "Taker.h"

Taker::Taker(const std::string &name, const int maxq)
	: ZITrader(name, maxq)
{
	traderType = "Taker";
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
	quote_t q = makeAddQuote(step, side, price);
	quoteCollector.push_back(q);
}