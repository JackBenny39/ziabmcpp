// ziabmcpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>     // std::cout, std::endl
#include <random>		// std::random_device, std::mt19937, std::uniform_real_distribution, std::uniform_int_distribution
#include <string>		// std::string
#include <tuple>        // std::tuple, std::get
#include <vector>		// std::vector

// #include "ZITrader.h"
#include "Taker.h"

using Id = std::string;
using Qty = unsigned;
using Prc = unsigned;

enum struct Side { BUY, SELL };

struct Quote { Id id; Qty qty; };
using Quotes = std::list<Quote>;

std::random_device random_device;
std::mt19937 engine{ random_device() };
std::vector<int> defaultVec = { 1, 5, 10, 25, 50 };
std::uniform_real_distribution<> distUreal(0, 1);

int setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUint(0, actualVec.size() - 1);
	return actualVec[distUint(engine)];
}

double buySellP()
{
	return distUreal(engine);
}

int main()
{
//	engine.seed(1);
//	Taker ti1("t1", setMaxQ(50));
//	std::cout << "Trader Type: " << ti1.traderType << "\n";
//	std::cout << "Max Quantity: " << ti1.orderSize << "\n";
//	std::cout << "Quote Collector Before: " << ti1.quoteCollector.empty() << "\n";
//	std::cout << "The trader is: " << "\n";
//	std::cout << "Trader: " << ti1.traderId << std::endl;

//	auto q = std::make_tuple("t1_2", 2, 'M', 50, 'S', 1002);

//	quote_t q1("t1_3", 2, 'M', 150, 'S', 982);

//	int step = 23;
//	char side = 'S';
//	int price = 1099;
//	double qTake = 0.5;

//	quote_t q8 = ti1.makeAddQuote(step, side, price);
//	quote_t q9 = ti1.makeAddQuote(step, side, price);

//	ti1.quoteCollector.push_back(q9);
//	ti1.processSignal(step, qTake, buySellP());

//	std::cout << "Quote Collector After: " << ti1.quoteCollector.empty() << std::endl;


//	std::cout << "quote contains: \n";
//	std::cout << "Order Id8: " << std::get<0>(q8) << "\n";
//	std::cout << "Order Id9: " << std::get<0>(q9) << "\n";
//	std::cout << "Step: " << std::get<1>(q9) << "\n";
//	std::cout << "Type: " << std::get<2>(q9) << "\n";
//	std::cout << "Size: " << std::get<3>(q9) << "\n";
//	std::cout << "Side: " << std::get<4>(q9) << "\n";
//	std::cout << "Price: " << std::get<5>(q9) << std::endl;

	Side myside = Side::BUY;
	if (myside == Side::BUY)
		std::cout << "Side out: " << "BUY" << std::endl;

	Quote q1 = { "t1_1", 100 };
	Quote q2 = { "t1_2", 200 };
	Quote q3 = { "t1_3", 300 };
	Quotes quotes;
	quotes.emplace_back(q1);
	quotes.emplace_back(q2);
	quotes.emplace_back(q3);
	quotes.emplace_back(Quote { "t1_4", 400 });
	for (auto& x : quotes)
		std::cout << "Id: " << x.id << ", Qty: " << x.qty << "\n";

	std::cout << std::endl;

	return 0;
}

