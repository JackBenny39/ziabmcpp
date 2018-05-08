// ZITrader.cpp
// ZITrader class

#include "stdafx.h"

#include <string>

#include "ZITrader.h"

ZITrader::ZITrader(const int tnum, const int maxq)
{
	traderType = 'Z'; 
	tId = tnum;
	orderSize = maxq;
	quoteSequence = 0;
}

Order ZITrader::makeAddQuote(Step timestamp, Side side, Prc price)
{
	return Order{ tId, ++quoteSequence, timestamp, 'A', orderSize, side, price };
}