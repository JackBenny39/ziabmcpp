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

void Informed::makeSteps(const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA)
{
	unsigned count;
	Step j;
	for (int i = 1; i != numChoices; ++i)
	{
		j = distA(engine);
		count = 0;
		while (count < runL)
		{
			while (steps.count(j) > 0)
				j++;
			steps.insert(j);
			count++;
		}
	}
}

void Informed::processSignal(Step step)
{
	quoteCollector.emplace_back(makeAddQuote(step, side, price));
}