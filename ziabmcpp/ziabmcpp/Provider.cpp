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

void Provider::bulkCancel(Step)
{
	
}

void Provider::processSignal(TopOfBook &tob, Step step, double qProvide, double lambdaT, double buyP)
{
	Order q;
	if (buyP < qProvide)
		q = makeAddQuote(step, Side::BUY, chooseP(Side::BUY, tob.bestask, lambdaT));
	else
		q = makeAddQuote(step, Side::SELL, chooseP(Side::SELL, tob.bestbid, lambdaT));
	quoteCollector.push_back(q);
	localBook[q.oid] = q;
}

Prc Provider::chooseP(Side side, Prc inside, double lambdaT)
{
	int plug = 4;
	if (side == Side::BUY)
		return inside - 1 - plug;
	else
		return inside + 1 + plug;
}