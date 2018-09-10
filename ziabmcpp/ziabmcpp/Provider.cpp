// Provider.cpp
// Provider class

#include "stdafx.h"

#include "Provider.h"


Provider::Provider(const Step arr, const int tnum, const int maxq, const double dlt, const Prc mpi)
	: arrInt(arr), tId(tnum), orderSize(maxq), delta(dlt), mpi(mpi), quoteSequence(0) { traderType = 'P'; }

Order Provider::makeCancelQuote(Order &q, Step timestamp)
{
	return Order{ q.id, q.oid, timestamp, 'C', q.qty, q.side, q.price };
}

void Provider::confirmTrade(TConfirm &c)
{
	if (c.qty == localBook[c.restoid].qty)
		localBook.erase(c.restoid);
	else
		localBook[c.restoid].qty -= c.qty;
}

void Provider::bulkCancel(Step step, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
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

Order Provider::processSignal(TopOfBook &tob, Step step, double qProvide, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	++quoteSequence;
	if (dist(engine) < qProvide)
		return localBook.emplace(quoteSequence, Order{ tId, quoteSequence, step, 'A', orderSize, Side::BUY, chooseP(Side::BUY, tob.bestask, lambdaT, engine, dist) }).first->second;
	else
		return localBook.emplace(quoteSequence, Order{ tId, quoteSequence, step, 'A', orderSize, Side::SELL, chooseP(Side::SELL, tob.bestask, lambdaT, engine, dist) }).first->second;
}

Prc Provider::chooseP(Side side, Prc inside, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Prc plug = static_cast<int>(lambdaT * log(dist(engine)));
	if (side == Side::BUY)
		return inside - 1 - plug;
	else
		return inside + 1 + plug;
}