// ZITrader.cpp
// ZITrader class

#include "stdafx.h"

#include <random>
#include <string>
#include <vector>

#include "ZITrader.h"

ZITrader::ZITrader(const std::string &name, const int maxq) : eng(random_device()), defaultVec({ 1, 5, 10, 25, 50 })
{
	traderId = name;
	setQuantity(maxq);
	quoteSequence = 0;
	traderType = "ZITrader";
}

//std::string ZITrader::getTraderType() const
//{
//	return traderType;
//}

//std::string ZITrader::getTraderId() const
//{
//	return traderId;
//}

void ZITrader::setQuantity(const int maxq)
{
	//	std::vector<int> defaultVec = { 1, 5, 10, 25, 50 };
	std::vector<int> actualVec(0);

	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });

	//	std::random_device random_device;
	//	std::mt19937 engine{ random_device() };
	std::uniform_int_distribution<int> dist(0, actualVec.size() - 1);
	orderSize = actualVec[dist(eng)];
}

int ZITrader::getQuantity() const
{
	return orderSize;
}

quote_t ZITrader::makeAddQuote(int timestamp, char side, int price)
{
	//	std::string orderId = getTraderId() + "_" + std::to_string(++quoteSequence);
	std::string orderId = traderId + "_" + std::to_string(++quoteSequence);
	//	return std::make_tuple(orderId, timestamp, 'A', getQuantity(), side, price);
	return std::make_tuple(orderId, timestamp, 'A', orderSize, side, price);

}