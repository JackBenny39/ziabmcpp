// Provider.cpp
// Provider class

#include "stdafx.h"

#include "Provider.h"

Provider::Provider(const Step arr, const int tnum, const int maxq, const double dlt, const Prc mpi)
	: ZITrader(arr, tnum, maxq, dlt, mpi) { traderType = 'P'; }

Provider::Provider(const Step arr, const int tnum, const int maxq, const double dlt, const int qRange, const int numQ)
	: ZITrader(arr, tnum, maxq, dlt, qRange, numQ) { }

void Provider::confirmTrade(TConfirm &c)
{
	if (c.qty == localBook[c.restoid].qty)
		confirmCancel(c.restoid);
	else
		localBook[c.restoid].qty -= c.qty;
}

void Provider::processSignal(TopOfBook &tob, Step step, double qProvide, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Order q;
	quoteCollector.clear();
	if (dist(engine) < qProvide)
		q = makeAddQuote(step, Side::BUY, chooseP(Side::BUY, tob.bestask, lambdaT, engine, dist));
	else
		q = makeAddQuote(step, Side::SELL, chooseP(Side::SELL, tob.bestbid, lambdaT, engine, dist));
	quoteCollector.push_back(q);
	localBook[q.oid] = q;
}