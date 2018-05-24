// Provider.cpp
// Provider class

#include "stdafx.h"

#include "Provider.h"

Provider::Provider(const int tnum, const int maxq, const double delta)
	: ZITrader(tnum, maxq), delta(delta)
{
	traderType = 'P';
}

Order Provider::makeCancelQuote(Order &q, Step timestamp)
{
	return Order{ q.id, q.oid, timestamp, 'C', q.qty, q.side, q.price };
}

void Provider::confirmCancel(Id oid)
{
	localBook.erase(oid);
}

void Provider::confirmTrade(TConfirm &c)
{
	if (c.qty == localBook[c.restoid].qty)
		confirmCancel(c.restoid);
	else
		localBook[c.restoid].qty -= c.qty;
}

void Provider::bulkCancel(Step step, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	for (auto &x : localBook)
	{
		if (dist(engine) < delta)
			cancelCollector.emplace_back(makeCancelQuote(x.second, step));
	}
}

void Provider::processSignal(TopOfBook &tob, Step step, double qProvide, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Order q;
	if (dist(engine) < qProvide)
		q = makeAddQuote(step, Side::BUY, chooseP(Side::BUY, tob.bestask, lambdaT, engine, dist));
	else
		q = makeAddQuote(step, Side::SELL, chooseP(Side::SELL, tob.bestbid, lambdaT, engine, dist));
	quoteCollector.push_back(q);
	localBook[q.oid] = q;
}

Prc Provider::chooseP(Side side, Prc inside, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Prc plug = (int)(lambdaT * log(dist(engine)));
	if (side == Side::BUY)
		return inside - 1 - plug;
	else
		return inside + 1 + plug;
}