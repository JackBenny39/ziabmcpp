// MarketMaker.cpp
// MarketMaker class

#include "stdafx.h"

#include "MarketMaker5.h"

MarketMaker5::MarketMaker5(const int tnum, const int maxq, const double delta, const int qRange, const int numQ)
	: MarketMaker(tnum, maxq, delta, qRange, numQ) { }

void MarketMaker5::processSignal(TopOfBook &tob, Step step, double qProvide, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Prc maxBid, minAsk;
	Order q;
	if (dist(engine) < qProvide)
	{
		maxBid = tob.bestbidsz > 1 ? tob.bestbid : tob.bestbid - 5;
		std::uniform_int_distribution<Prc> distU(maxBid - quoteRange + 1, maxBid);
		for (int i = 1; i < numQuotes; i++)
		{
			q = makeAddQuote(step, Side::BUY, static_cast<Prc>(5 * nearbyint(distU(engine) / 5.0)));
			quoteCollector.push_back(q);
			localBook[q.oid] = q;
		}
	}
	else
	{
		minAsk = tob.bestasksz > 1 ? tob.bestask : tob.bestask + 5;
		std::uniform_int_distribution<Prc> distU(minAsk, minAsk + quoteRange - 1);
		for (int i = 1; i < numQuotes; i++)
		{
			q = makeAddQuote(step, Side::SELL, static_cast<Prc>(5 * nearbyint(distU(engine) / 5.0)));
			quoteCollector.push_back(q);
			localBook[q.oid] = q;
		}
	}
}

