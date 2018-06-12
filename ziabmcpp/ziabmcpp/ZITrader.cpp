// ZITrader.cpp
// ZITrader class

#include "stdafx.h"

#include <string>

#include "ZITrader.h"


ZITrader::ZITrader(const Step arr, const int tnum, const int maxq, const Prc mpi)
	: arrInt(arr), tId(tnum), orderSize(maxq), mpi(mpi), quoteSequence(0) { traderType = 'Z'; }

ZITrader::ZITrader(const int tnum, const int maxq, Side side, const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA)
	: tId(tnum), orderSize(maxq), side(side), price(side == Side::BUY ? 2000000 : 0), quoteSequence(0) { }

ZITrader::ZITrader(const Step arr, const int tnum, const int maxq, const double dlt, const Prc mpi)
	: arrInt(arr), tId(tnum), orderSize(maxq), delta(dlt), mpi(mpi), quoteSequence(0) { }

ZITrader::ZITrader(const Step arr, const int tnum, const int maxq, const double dlt, const int qRange, const int numQ)
	: arrInt(arr), tId(tnum), orderSize(maxq), delta(dlt), quoteRange(qRange), numQuotes(numQ + 1), position(0), cashFlow(0), quoteSequence(0) { }

Order ZITrader::makeAddQuote(Step timestamp, Side side, Prc price)
{
	return Order{ tId, ++quoteSequence, timestamp, 'A', orderSize, side, price };
}

void ZITrader::processSignal(Step step, double qTake, std::mt19937 &engine, std::uniform_real_distribution<> &dist) {}
void ZITrader::processSignal(Step step) {}

void ZITrader::makeSteps(const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA) {}