// Informed.cpp
// Informed class

#include "stdafx.h"


#include "Informed.h"

Informed::Informed(const int tnum, const int maxq, Side side, const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA)
	: ZITrader(tnum, maxq, side, runL, numChoices, engine, distA) 
{ 
	traderType = 'I';
	makeSteps(runL, numChoices, engine, distA);
}

void Informed::processSignal(Step step)
{
	quoteCollector.clear();
	quoteCollector.emplace_back(makeAddQuote(step, side, price));
	arrInt = *it++;
}