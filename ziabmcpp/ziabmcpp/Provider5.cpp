// Provider5.cpp
// Provider5 class

#include "stdafx.h"

#include "Provider5.h"

Provider5::Provider5(const int tnum, const int maxq, const double delta)
	: Provider(tnum, maxq, delta) {}

void Provider5::processSignal(TopOfBook &tob, Step step, double qProvide, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Order q;
	if (dist(engine) < qProvide)
		q = makeAddQuote(step, Side::BUY, chooseP(Side::BUY, tob.bestask, lambdaT, engine, dist));
	else
		q = makeAddQuote(step, Side::SELL, chooseP(Side::SELL, tob.bestbid, lambdaT, engine, dist));
	quoteCollector.push_back(q);
	localBook[q.oid] = q;
}

Prc Provider5::chooseP(Side side, Prc inside, double lambdaT, std::mt19937 &engine, std::uniform_real_distribution<> &dist)
{
	Prc plug = (int)(lambdaT * log(dist(engine)));
	if (side == Side::BUY)
		return 5*((inside - 1 - plug)/5);
	else
		return 5*(((inside + 1 + plug)/5)+1);
}