// ZITrader.cpp
// ZITrader class

#include "stdafx.h"

#include <string>

#include "ZITrader.h"


ZITrader::ZITrader(const int tnum, const int maxq)
	: tId(tnum), orderSize(maxq), quoteSequence(0) { traderType = 'Z'; }

ZITrader::ZITrader(const int tnum, const int maxq, Side side)
	: tId(tnum), orderSize(maxq), side(side), price(side == Side::BUY ? 2000000 : 0), quoteSequence(0) { }

ZITrader::ZITrader(const int tnum, const int maxq, const double dlt)
	: tId(tnum), orderSize(maxq), delta(dlt), quoteSequence(0) { }

ZITrader::ZITrader(const int tnum, const int maxq, const double dlt, const int qRange, const int numQ)
	: tId(tnum), orderSize(maxq), delta(dlt), quoteRange(qRange), numQuotes(numQ + 1), position(0), cashFlow(0), quoteSequence(0) { }

ZITrader::ZITrader(const int tnum, const int maxq, const Prc mpi)
	: tId(tnum), orderSize(maxq), mpi(mpi), quoteSequence(0) { }

Order ZITrader::makeAddQuote(Step timestamp, Side side, Prc price)
{
	return Order{ tId, ++quoteSequence, timestamp, 'A', orderSize, side, price };
}