// PennyJumper.cpp
// PennyJumper class

#include "stdafx.h"

#include "PennyJumper.h"

PennyJumper::PennyJumper(const int tnum, const int maxq, Prc mpi)
	: ZITrader(tnum, maxq), mpi(mpi)
{
	traderType = 'J';
	Order nullBid{ 1001, 0, 0, 'A', 0, Side::BUY, 0 };
	Order nullAsk{ 1001, 0, 0, 'A', 0, Side::SELL, 0 };
	askQuote = nullAsk;
	bidQuote = nullBid;
}

Order PennyJumper::makeCancelQuote(Order &q, Step timestamp)
{
	return Order{ q.id, q.oid, timestamp, 'C', q.qty, q.side, q.price };
}

void PennyJumper::confirmTrade(TConfirm &c)
{
	if (c.side == Side::BUY)
		bidQuote = nullBid;
	else
		askQuote = nullAsk;
}

void PennyJumper::processSignal(TopOfBook &tob, Step step, double qTake, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Order q;
	if (tob.bestask - tob.bestbid > mpi)
	{
		if (dist(engine) < qTake)
		{
			if (bidQuote.price > 0)
			{

			}
		}
	}
	if (dist(engine) < qProvide)
		q = makeAddQuote(step, Side::BUY, chooseP(Side::BUY, tob.bestask, lambdaT, engine, dist));
	else
		q = makeAddQuote(step, Side::SELL, chooseP(Side::SELL, tob.bestbid, lambdaT, engine, dist));
	quoteCollector.push_back(q);
	localBook[q.oid] = q;

}
