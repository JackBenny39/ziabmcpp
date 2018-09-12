// ZITrader.cpp
// ZITrader class

#include "stdafx.h"

#include <string>

#include "ZITrader.h"


ZITrader::ZITrader(const Step arr, const int tnum, const int maxq, const Prc mpi)
	: arrInt(arr), tId(tnum), orderSize(maxq), mpi(mpi), quoteSequence(0) { traderType = 'Z'; }

ZITrader::ZITrader(const int tnum, const int maxq, Side side, const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA)
	: tId(tnum), orderSize(maxq), side(side), price(side == Side::BUY ? 2000000 : 0), quoteSequence(0) { }


Order ZITrader::makeAddQuote(Step timestamp, Side side, Prc price)
{
	return Order{ tId, ++quoteSequence, timestamp, 'A', orderSize, side, price };
}

Order ZITrader::makeCancelQuote(Order &q, Step timestamp)
{
	return Order{ q.id, q.oid, timestamp, 'C', q.qty, q.side, q.price };
}

void ZITrader::confirmCancel(Id oid)
{
	localBook.erase(oid);
}

void ZITrader::makeSteps(const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA)
{
	unsigned count;
	Step j;
	for (auto i = 1; i != numChoices; ++i)
	{
		j = distA(engine);
		count = 0;
		while (count < runL)
		{
			while (steps.count(j) > 0)
				j++;
			steps.insert(j);
			count++;
		}
	}
	it = steps.begin();
	arrInt = *it++;
}


void ZITrader::processSignal(Step step, double qTake, std::mt19937 &engine, std::uniform_real_distribution<> &dist) { }
void ZITrader::processSignal(Step step) {}

void ZITrader::confirmTrade(TConfirm &c) { }
