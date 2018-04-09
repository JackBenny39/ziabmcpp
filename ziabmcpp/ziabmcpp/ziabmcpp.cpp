// ziabmcpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>     // std::cout, std::endl
#include <string>		// std::string
#include <tuple>        // std::tuple, std::get

// #include "ZITrader.h"
#include "Taker.h"

int main()
{
	Taker ti1("t1", 50);
	//	std::cout << "Trader Type: " << ti1.getTraderType() << "\n";
	std::cout << "Trader Type: " << ti1.traderType << "\n";
	std::cout << "Quote Collector Before: " << ti1.quoteCollector.empty() << "\n";
	std::cout << "The trader is: " << "\n";
	//	std::cout << "Trader: " << ti1.getTraderId() << std::endl;
	std::cout << "Trader: " << ti1.traderId << std::endl;

	auto q = std::make_tuple("t1_2", 2, 'M', 50, 'S', 1002);

	quote_t q1("t1_3", 2, 'M', 150, 'S', 982);

	int step = 23;
	char side = 'S';
	int price = 1099;

	quote_t q8 = ti1.makeAddQuote(step, side, price);
	quote_t q9 = ti1.makeAddQuote(step, side, price);

	ti1.quoteCollector.push_back(q9);

	std::cout << "Quote Collector After: " << ti1.quoteCollector.empty() << std::endl;


	std::cout << "quote contains: \n";
	std::cout << "Order Id8: " << std::get<0>(q8) << "\n";
	std::cout << "Order Id9: " << std::get<0>(q9) << "\n";
	std::cout << "Step: " << std::get<1>(q9) << "\n";
	std::cout << "Type: " << std::get<2>(q9) << "\n";
	std::cout << "Size: " << std::get<3>(q9) << "\n";
	std::cout << "Side: " << std::get<4>(q9) << "\n";
	std::cout << "Price: " << std::get<5>(q9) << std::endl;

	return 0;
}

