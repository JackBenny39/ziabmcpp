// Taker.cpp
// Taker class

#include "stdafx.h"

#include "Taker.h"

Taker::Taker(const Step arr, const int tnum, const int maxq)
	: arrInt(arr), tId(tnum), orderSize(maxq), quoteSequence(0) { traderType = 'T'; }

Order Taker::processSignal(Step step, double qTake, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	++quoteSequence;
	if (dist(engine) < qTake)
		return Order{ tId, quoteSequence, step, 'A', orderSize, Side::BUY, 2000000 };
	else
		return Order{ tId, quoteSequence, step, 'A', orderSize, Side::SELL, 0 };
}