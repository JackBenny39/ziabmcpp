// Informed.cpp
// Informed class

#include "stdafx.h"


#include "Informed.h"

Informed::Informed(const int tnum, const int maxq, Side sidein)
	: ZITrader(tnum, maxq)
{
	traderType = 'I';
	side = sidein;
	price = side == Side::BUY ? 2000000 : 0;
}

void Informed::processSignal(Step step)
{
	quoteCollector.emplace_back(makeAddQuote(step, side, price));
}