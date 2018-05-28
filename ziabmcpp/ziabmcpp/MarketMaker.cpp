// MarketMaker.cpp
// MarketMaker class

#include "stdafx.h"

#include "MarketMaker.h"

MarketMaker::MarketMaker(const int tnum, const int maxq, const double delta, const int qRange, const int numQ)
	: Provider(tnum, maxq, delta), quoteRange(qRange), numQuotes(numQ + 1), position(0), cashFlow(0)
{
	traderType = 'M';
}

void MarketMaker::confirmTrade(TConfirm &c)
{
	if (c.side == Side::BUY)
	{
		cashFlow -= c.price * c.qty;
		position += c.qty;
	}
	else
	{
		cashFlow += c.price * c.qty;
		position -= c.qty;
	}
	if (c.qty == localBook[c.restoid].qty)
		confirmCancel(c.restoid);
	else
		localBook[c.restoid].qty -= c.qty;
	cashFlowCollector.emplace_back(CFlow{ tId, c.reststep, cashFlow, position });
}

void MarketMaker::processSignal(TopOfBook &tob, Step step, double qProvide, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Prc maxBid, minAsk;
	Order q;
	if (dist(engine) < qProvide)
	{
		maxBid = tob.bestbidsz > 1 ? tob.bestbid : tob.bestbid - 1;
		std::uniform_int_distribution<Prc> distU(maxBid - quoteRange + 1, maxBid);
		for (int i = 1; i < numQuotes; i++)
		{
			q = makeAddQuote(step, Side::BUY, distU(engine));
			quoteCollector.push_back(q);
			localBook[q.oid] = q;
		}
	}
	else
	{
		minAsk = tob.bestasksz > 1 ? tob.bestask : tob.bestask + 1;
		std::uniform_int_distribution<Prc> distU(minAsk, minAsk + quoteRange - 1);
		for (int i = 1; i < numQuotes; i++)
		{
			q = makeAddQuote(step, Side::SELL, distU(engine));
			quoteCollector.push_back(q);
			localBook[q.oid] = q;
		}
	}
}
