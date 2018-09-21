// MarketMaker.cpp
// MarketMaker class

#include "stdafx.h"

#include "MarketMaker.h"

MarketMaker::MarketMaker(const Step arr, const traderId tnum, const Qty maxq, const double dlt, const int qRange, const int numQ)
	: arrInt(arr), tId(tnum), orderSize(maxq), delta(dlt), quoteRange(qRange), numQuotes(numQ + 1), position(0), cashFlow(0), quoteSequence(0) { }

const char MarketMaker::traderType{ 'M' };

Order MarketMaker::makeCancelQuote(Order &q, Step timestamp)
{
	return Order{ q.id, q.oid, timestamp, 'C', q.qty, q.side, q.price };
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
		localBook.erase(c.restoid);
	else
		localBook[c.restoid].qty -= c.qty;
	cashFlowCollector.emplace_back(CFlow{ tId, c.reststep, cashFlow, position });
}

void MarketMaker::bulkCancel(Step step, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	cancelCollector.clear();
	for (auto &x : localBook)
	{
		if (dist(engine) < delta)
			cancelCollector.emplace_back(makeCancelQuote(x.second, step));
	}
	for (auto &x : cancelCollector)
	{
		localBook.erase(x.oid);
	}
}

void MarketMaker::processSignal(TopOfBook &tob, Step step, double qProvide, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Prc maxBid, minAsk;
	quoteCollector.clear();
	if (dist(engine) < qProvide)
	{
		maxBid = tob.bestbidsz > 1 ? tob.bestbid : tob.bestbid - 1;
		std::uniform_int_distribution<Prc> distU(maxBid - quoteRange + 1, maxBid);
		for (int i = 1; i < numQuotes; i++)
		{
			++quoteSequence;
			quoteCollector.push_back(localBook.emplace(quoteSequence, Order{ tId, quoteSequence, step, 'A', orderSize, Side::BUY, distU(engine) }).first->second);
		}
	}
	else
	{
		minAsk = tob.bestasksz > 1 ? tob.bestask : tob.bestask + 1;
		std::uniform_int_distribution<Prc> distU(minAsk, minAsk + quoteRange - 1);
		for (int i = 1; i < numQuotes; i++)
		{
			++quoteSequence;
			quoteCollector.push_back(localBook.emplace(quoteSequence, Order{ tId, quoteSequence, step, 'A', orderSize, Side::SELL, distU(engine) }).first->second);
		}
	}
}
