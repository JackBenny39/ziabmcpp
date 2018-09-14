// Informed.cpp
// Informed class

#include "stdafx.h"

#include "Informed.h"

Informed::Informed(const traderId tnum, const Qty maxq, const Side side, const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA)
	: tId(tnum), orderSize(maxq), side(side), price(side == Side::BUY ? 2000000 : 0), quoteSequence(0)
{ 
	makeSteps(runL, numChoices, engine, distA);
}

const char Informed::traderType{ 'I' };

void Informed::makeSteps(const unsigned runL, const unsigned numChoices, std::mt19937 &engine, std::uniform_int_distribution<> &distA)
{
	unsigned count;
	Step j;
	for (auto i = 1; i != numChoices; ++i)
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
	it = steps.begin();
	arrInt = *it++;
}

Order Informed::processSignal(Step step)
{
	++quoteSequence;
	arrInt = *it++;
	return Order{ tId, quoteSequence, step, 'A', orderSize, side, price };
}