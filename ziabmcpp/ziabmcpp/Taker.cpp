// Taker.cpp
// Taker class

#include "stdafx.h"

#include <random>

#include "Taker.h"

Taker::Taker(const std::string &name, const int maxq)
	: ZITrader(name, maxq)
{
	traderType = "Taker";
}

void Taker::processSignal(int step, float qTake)
{
	int price;
	char side;

	std::random_device random_device;
	std::mt19937 engine{ random_device() };
	std::uniform_real_distribution<> dist(0, 1);

	if (dist(engine) < qTake)
	{
		price = 2000000;
		side = 'B';
	}
	else
	{
		price = 0;
		side = 'S';
	}
	quote_t q = makeAddQuote(step, side, price);
}