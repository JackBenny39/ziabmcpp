// BucketTests.cpp
// BucketTests class

#include "stdafx.h"

#include <iostream>

#include "BucketTests.h"


BucketTests::BucketTests(std::vector<int> &dVec, std::uniform_int_distribution<> &dUint, std::mt19937 &eng) :
	defaultVec(dVec), distUint(dUint), engine(eng)
{
	engine.seed(44);
	bucket.push_back(std::make_shared<PennyJumper>(1, 4001, setMaxQ(50), 1));
	engine.seed(39);
	bucket.push_back(std::make_shared<ZITrader>(7, 1, setMaxQ(50), 1));
	bucket.push_back(std::make_shared<Taker>(11, 1001, setMaxQ(50), 1));
	bucket.push_back(std::make_shared<Informed>(2001, 1, Side::SELL, 1, 100, engine, distUint));
	bucket.push_back(std::make_shared<Provider>(17, 3001, setMaxQ(50), 0.85, 1));
	bucket.push_back(std::make_shared<Provider5>(22, 3005, setMaxQ(50), 0.05, 5));
	bucket.push_back(std::make_shared<MarketMaker>(1, 7001, setMaxQ(50), 0.05, 60, 12));
	bucket.push_back(std::make_shared<MarketMaker5>(1, 7005, setMaxQ(50), 0.05, 60, 12));
}

int BucketTests::setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUintV(0, actualVec.size() - 1);
	return actualVec[distUintV(engine)];
}

void BucketTests::testInstances()
{
	cSide cSide1;

	std::cout << "Trader Type: " << bucket[0]->traderType << "; Max Quantity: " << bucket[0]->orderSize << "; Trader ID: " << bucket[0]->tId << "; MPI: "
		<< bucket[0]->mpi << "\n";
	std::cout << "Trader Type: " << bucket[1]->traderType << "; Max Quantity: " << bucket[1]->orderSize << "; Trader ID: " << bucket[1]->tId << "; MPI: "
		<< bucket[1]->mpi << "\n";
	std::cout << "Trader Type: " << bucket[2]->traderType << "; Max Quantity: " << bucket[2]->orderSize << "; Trader ID: " << bucket[2]->tId << "; MPI: "
		<< bucket[2]->mpi << "\n";
	cSide1 = bucket[3]->side == Side::BUY ? 'B' : 'S';
	std::cout << "Trader Type: " << bucket[3]->traderType << "; Max Quantity: " << bucket[3]->orderSize << "; Trader ID: " << bucket[3]->tId << "; Price:"
		<< bucket[3]->price << "; Side:" << cSide1 << "\n";
	std::cout << "Trader Type: " << bucket[4]->traderType << "; Max Quantity: " << bucket[4]->orderSize << "; Trader ID: " << bucket[4]->tId << "; MPI: "
		<< bucket[4]->mpi << "; Delta: " << bucket[4]->delta << "\n";
	std::cout << "Trader Type: " << bucket[5]->traderType << "; Max Quantity: " << bucket[5]->orderSize << "; Trader ID: " << bucket[5]->tId << "; MPI: "
		<< bucket[5]->mpi << "; Delta: " << bucket[5]->delta << "\n";
	std::cout << "Trader Type: " << bucket[6]->traderType << "; Max Quantity: " << bucket[6]->orderSize << "; Trader ID: " << bucket[6]->tId << "; NumQuotes: "
		<< bucket[6]->numQuotes << "; Quote Range: " << bucket[6]->quoteRange << "; Position: " << bucket[6]->position << "; Cash Flow: "
		<< bucket[6]->cashFlow << "\n";
	std::cout << "Trader Type: " << bucket[7]->traderType << "; Max Quantity: " << bucket[7]->orderSize << "; Trader ID: " << bucket[7]->tId << "; NumQuotes: "
		<< bucket[7]->numQuotes << "; Quote Range: " << bucket[7]->quoteRange << "; Position: " << bucket[7]->position << "; Cash Flow: "
		<< bucket[7]->cashFlow << "\n";

	std::cout << std::endl;
}