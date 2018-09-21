// Runner.cpp
// Runner class

#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <numeric>

#include "Runner.h"


Runner::Runner(Prc mpi, Step prime1, Step runSteps, Step writeInterval,
	bool provider, unsigned numProviders, Qty providerMaxQ, double pAlpha, double pDelta, double qProvide,
	bool taker, unsigned numTakers, Qty takerMaxQ, double tMu,
	bool informed, Step informedRun, Qty informedQ, double iMu, Side informedSide,
	bool jumper, double jAlpha,
	bool maker, unsigned numMMs, Qty mmMaxQ, unsigned mmQuotes, unsigned mmRange, double mmDelta,
	bool qTake, double lambda0, double whiteNoise, double cLambda, std::mt19937 &eng, unsigned seed) :
	mpi(mpi), prime1(prime1), runSteps(runSteps), writeInterval(writeInterval),
	provider(provider), numProviders(numProviders), providerMaxQ(providerMaxQ), pAlpha(pAlpha), pDelta(pDelta), qProvide(qProvide),
	taker(taker), numTakers(numTakers), takerMaxQ(takerMaxQ), tMu(tMu),
	informed(informed), informedRun(informedRun), informedQ(informedQ), iMu(iMu), informedSide(informedSide),
	jumper(jumper), jAlpha(jAlpha),
	maker(maker), numMMs(numMMs), mmMaxQ(mmMaxQ), mmQuotes(mmQuotes), mmRange(mmRange), mmDelta(mmDelta),
	qTake(qTake), lambda0(lambda0), whiteNoise(whiteNoise), cLambda(cLambda), engine(eng), seed(seed)
{
	defaultVec = { 1, 5, 10, 25, 50 };
	engine.seed(seed);
}

int Runner::setMaxQ(int maxq)
{
	std::vector<int> actualVec(0);
	std::copy_if(defaultVec.begin(), defaultVec.end(), std::back_inserter(actualVec), [&maxq](int i) { return i <= maxq; });
	std::uniform_int_distribution<int> distUintV(0, actualVec.size() - 1);
	return actualVec[distUintV(engine)];
}

void Runner::buildProviders()
{
	std::exponential_distribution<double> distExpP(pAlpha);
	traderId tId;
	if (mpi == 1)
	{
		for (auto i = 1; i != numProviders; ++i)
		{
			auto size = setMaxQ(providerMaxQ);
			tId = 1000 + i;
			allTraderIds.push_back(tId);
			providerIds.push_back(tId);
			providers.emplace(tId, std::make_shared<Provider>(static_cast<int>(floor(distExpP(engine) + 1)) * size, tId, size, pDelta));
		}
	}
	else
	{
		for (auto i = 0; i != numProviders; ++i)
		{
			auto size = setMaxQ(providerMaxQ);
			tId = 1000 + i;
			allTraderIds.push_back(tId);
			providerIds.push_back(tId);
			providers5.emplace(tId, std::make_shared <Provider5>(static_cast<int>(floor(distExpP(engine) + 1)) * size, tId, size, pDelta));
		}
	}
}

void Runner::buildTakers()
{
	std::exponential_distribution<double> distExpT(tMu);
	traderId tId;
	for (auto i = 0; i != numTakers; ++i)
	{
		auto size = setMaxQ(takerMaxQ);
		tId = 2000 + i;
		allTraderIds.push_back(tId);
		takers.emplace(tId, std::make_shared<Taker>(static_cast<int>(floor(distExpT(engine) + 1)) * size, 2000 + i, size));
	}
}

void Runner::buildInformed()
{
	int takerTrades = 0;
	int informedTrades;
	if (taker)
	{
		for (auto &x : takers)
			takerTrades += x.second->orderSize * runSteps / x.second->arrInt;
		informedTrades = static_cast<int>(floor(takerTrades * iMu));
	}
	else
		informedTrades = static_cast<int>(1 / iMu);
	unsigned numChoices = static_cast<unsigned>(1 + informedTrades / (informedRun*informedQ));

	std::uniform_int_distribution<int> distUintI(prime1, runSteps);
	informed1 = std::make_unique<Informed>(5000, informedQ, informedSide, informedRun, numChoices, engine, distUintI);
	allTraderIds.push_back(5000);
}

void Runner::buildMarketMakers()
{
	auto size = setMaxQ(mmMaxQ);
	traderId tId;

	if (mpi == 1)
	{
		for (auto i = 0; i != numMMs; ++i)
		{
			tId = 3000 + i;
			allTraderIds.push_back(tId);
			makers.emplace(tId, std::make_shared<MarketMaker>(size, tId, size, mmDelta, mmRange, mmQuotes));
		}
	}
	else
	{
		for (auto i = 0; i != numMMs; ++i)
		{
			tId = 3000 + i;
			allTraderIds.push_back(tId);
			makers5.emplace(tId, std::make_shared<MarketMaker5>(size, tId, size, mmDelta, mmRange, mmQuotes));
		}
	}
}

void Runner::buildPennyJumper()
{
	jumper1 = std::make_unique<PennyJumper>(4000, 1, mpi);
}

std::pair<std::vector<double>, std::vector<double>> Runner::buildLambda()
{
	double denom = 0.0, qt9 = 0.5, qt1 = 0.5;
	double qt10, qt2, x, lambdaDenom, lambda;
	std::vector<double> qTake;
	std::vector<double> lambdaT;
	std::uniform_real_distribution<> distUreal(0, 1);
	auto noise = std::bind(distUreal, engine);
	for (auto i = 1; i != runSteps; ++i)
	{
		x = noise();
		qt10 = (x > qt9) ? qt9 + whiteNoise : qt9 - whiteNoise;
		qt9 = qt10;
		denom += (qt10 - 0.5) * (qt10 - 0.5);
	}
	lambdaDenom = std::sqrt(denom / runSteps);
	
	qTake.emplace_back(qt1);
	lambdaT.emplace_back(-lambda0);
	for (auto i = 1; i != runSteps; ++i)
	{
		x = noise();
		qt2 = (x > qt1) ? qt1 + whiteNoise : qt1 - whiteNoise;
		qt1 = qt2;
		qTake.emplace_back(qt2);
		lambda = -lambda0 * (1 + (abs(qt2 - 0.5) / lambdaDenom) * cLambda);
		lambdaT.emplace_back(lambda);
	}
	return std::make_pair(qTake, lambdaT);
}

void Runner::qTakeToCsv(std::string &filename)
{
	std::ofstream csvfile;
	csvfile.open(filename);
	csvfile << "QTake,LambdaT\n";
	for (auto i = 0; i != runSteps; ++i)
		csvfile << i << "," << QL.first[i] << "," << QL.second[i] << "\n";
	csvfile.close();
}

void Runner::mmProfitsToCsv(std::string &filename)
{
	std::ofstream csvfile;
	csvfile.open(filename);
	csvfile << "TraderID,Step,CashFlow,Position\n";
	if (mpi == 1)
	{
		for (auto i = 0; i != numMMs; ++i)
		{
			for (auto& f : makers[3000 + i]->cashFlowCollector)
				csvfile << f.id << "," << f.step << "," << f.cf << "," << f.position << "\n";
		}
	}
	else
	{
		for (auto i = 0; i != numMMs; ++i)
		{
			for (auto& f : makers5[3000 + i]->cashFlowCollector)
				csvfile << f.id << "," << f.step << "," << f.cf << "," << f.position << "\n";
		}
	}
	csvfile.close();
}

void Runner::seedBook()
{
	traderId tId = 1000;
	allTraderIds.push_back(numProviders);
	providers.emplace(tId, std::make_shared<Provider>(1, tId, 1, pDelta));
	std::uniform_int_distribution<int> distUintBid(997995, 999996);
	std::uniform_int_distribution<int> distUintAsk(1000005, 1002001);
	auto b = providers[tId]->localBook.emplace(1, Order{ tId, 1, 0, 'A', 1, Side::BUY, static_cast<unsigned>(5 * (distUintBid(engine) / 5)) }).first->second;
	auto a = providers[tId]->localBook.emplace(2, Order{ tId, 2, 0, 'A', 1, Side::SELL, static_cast<unsigned>(5 * (distUintAsk(engine) / 5)) }).first->second;
	exchange.addHistory(b);
	exchange.addHistory(a);
	exchange.addBook(b.id, b.oid, b.side, b.price, b.qty, b.step);
	exchange.addBook(a.id, a.oid, a.side, a.price, a.qty, a.step);
}

void Runner::makeSetup()
{
	std::uniform_real_distribution<> distUreal(0, 1);
	exchange.bookTop2(0);
	for (auto i = 1; i != prime1; ++i)
	{
		shuffle(providerIds.begin(), providerIds.end(), engine);
		for (auto x : providerIds)
		{
			if (!(i % providers[x]->arrInt))
			{
				auto o = providers[x]->processSignal(exchange.tob.back(), i, qProvide, -lambda0, engine, distUreal);
				exchange.process(o);
				exchange.bookTop2(i);
			}
		}
	}
}

void Runner::runMCS1()
{
	int tRoot;
	std::uniform_real_distribution<> distUreal(0, 1);
	for (auto i = prime1; i != runSteps; ++i)
	{
		shuffle(allTraderIds.begin(), allTraderIds.end(), engine);
		for (auto t : allTraderIds)
		{
			tRoot = t / 1000;
			switch (tRoot)// make shared pointers to map values?
			{
			case 1:
				if (!(i % providers[t]->arrInt))
				{
					auto o = providers[t]->processSignal(exchange.tob.back(), i, qProvide, QL.second[i], engine, distUreal);
					exchange.process(o);
					exchange.bookTop2(i);
				}
				providers[t]->bulkCancel(i, engine, distUreal);
				if (!(providers[t]->cancelCollector.empty()))
				{
					for (auto& c : providers[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 3:
				if (!(i % makers[t]->arrInt))
				{
					makers[t]->processSignal(exchange.tob.back(), i, qProvide, engine, distUreal);
					for (auto& o : makers[t]->quoteCollector)
						exchange.process(o);
					exchange.bookTop2(i);
				}
				makers[t]->bulkCancel(i, engine, distUreal);
				if (!(makers[t]->cancelCollector.empty()))
				{
					for (auto& c : makers[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 2:
				if (!(i % takers[t]->arrInt))
				{
					auto o = takers[t]->processSignal(i, QL.first[i], engine, distUreal);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers[c.restid]->confirmTrade(c);
						else
							providers[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			default:
				if (i == informed1->arrInt)
				{
					auto o = informed1->processSignal(i);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers[c.restid]->confirmTrade(c);
						else
							providers[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			}
		}
	}
}

void Runner::runMCS5()
{
	int tRoot;
	std::uniform_real_distribution<> distUreal(0, 1);
	for (auto i = prime1; i != runSteps; ++i)
	{
		shuffle(allTraderIds.begin(), allTraderIds.end(), engine);
		for (auto t : allTraderIds)
		{
			tRoot = t / 1000;
			switch (tRoot)// make shared pointers to map values?
			{
			case 1:
				if (!(i % providers5[t]->arrInt))
				{
					auto o = providers5[t]->processSignal(exchange.tob.back(), i, qProvide, QL.second[i], engine, distUreal);
					exchange.process(o);
					exchange.bookTop2(i);
				}
				providers5[t]->bulkCancel(i, engine, distUreal);
				if (!(providers5[t]->cancelCollector.empty()))
				{
					for (auto& c : providers5[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 3:
				if (!(i % makers5[t]->arrInt))
				{
					makers5[t]->processSignal(exchange.tob.back(), i, qProvide, engine, distUreal);
					for (auto& o : makers5[t]->quoteCollector)
						exchange.process(o);
					exchange.bookTop2(i);
				}
				makers5[t]->bulkCancel(i, engine, distUreal);
				if (!(makers5[t]->cancelCollector.empty()))
				{
					for (auto& c : makers5[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 2:
				if (!(i % takers[t]->arrInt))
				{
					auto o = takers[t]->processSignal(i, QL.first[i], engine, distUreal);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers5[c.restid]->confirmTrade(c);
						else
							providers5[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			default:
				if (i == informed1->arrInt)
				{
					auto o = informed1->processSignal(i);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers5[c.restid]->confirmTrade(c);
						else
							providers5[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			}
		}
	}
}

void Runner::runMCSPJ1()
{
	int tRoot;
	std::uniform_real_distribution<> distUreal(0, 1);
	for (auto i = prime1; i != runSteps; ++i)
	{
		shuffle(allTraderIds.begin(), allTraderIds.end(), engine);
		for (auto t : allTraderIds)
		{
			tRoot = t / 1000;
			switch (tRoot)// make shared pointers to map values?
			{
			case 1:
				if (!(i % providers[t]->arrInt))
				{
					auto o = providers[t]->processSignal(exchange.tob.back(), i, qProvide, QL.second[i], engine, distUreal);
					exchange.process(o);
					exchange.bookTop2(i);
				}
				providers[t]->bulkCancel(i, engine, distUreal);
				if (!(providers[t]->cancelCollector.empty()))
				{
					for (auto& c : providers[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 3:
				if (!(i % makers[t]->arrInt))
				{
					makers[t]->processSignal(exchange.tob.back(), i, qProvide, engine, distUreal);
					for (auto& o : makers[t]->quoteCollector)
						exchange.process(o);
					exchange.bookTop2(i);
				}
				makers[t]->bulkCancel(i, engine, distUreal);
				if (!(makers[t]->cancelCollector.empty()))
				{
					for (auto& c : makers[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 2:
				if (!(i % takers[t]->arrInt))
				{
					auto o = takers[t]->processSignal(i, QL.first[i], engine, distUreal);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers[c.restid]->confirmTrade(c);
						else if (pRoot == 4)
							jumper1->confirmTrade(c);
						else
							providers[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			default:
				if (i == informed1->arrInt)
				{
					auto o = informed1->processSignal(i);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers[c.restid]->confirmTrade(c);
						else if (pRoot == 4)
							jumper1->confirmTrade(c);
						else
							providers[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			}
			if (distUreal(engine) < jAlpha)
			{
				jumper1->processSignal(exchange.tob.back(), i, QL.first[i], engine, distUreal);
				if (!(jumper1->cancelCollector.empty())) // don't need to check this?
				{
					for (auto& c : jumper1->cancelCollector)
						exchange.process(c);
				}
				if (!(jumper1->quoteCollector.empty())) // don't need to check this?
				{
					for (auto& o : jumper1->quoteCollector)
						exchange.process(o);
				}
				exchange.bookTop2(i);
			}
		}
	}
}

void Runner::runMCSPJ5()
{
	int tRoot;
	std::uniform_real_distribution<> distUreal(0, 1);
	for (auto i = prime1; i != runSteps; ++i)
	{
		shuffle(allTraderIds.begin(), allTraderIds.end(), engine);
		for (auto t : allTraderIds)
		{
			tRoot = t / 1000;
			switch (tRoot) // make shared pointers to map values?
			{
			case 1:
				if (!(i % providers5[t]->arrInt))
				{
					auto o = providers5[t]->processSignal(exchange.tob.back(), i, qProvide, QL.second[i], engine, distUreal);
					exchange.process(o);
					exchange.bookTop2(i);
				}
				providers5[t]->bulkCancel(i, engine, distUreal);
				if (!(providers5[t]->cancelCollector.empty()))
				{
					for (auto& c : providers5[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 3:
				if (!(i % makers5[t]->arrInt))
				{
					makers5[t]->processSignal(exchange.tob.back(), i, qProvide, engine, distUreal);
					for (auto& o : makers5[t]->quoteCollector)
						exchange.process(o);
					exchange.bookTop2(i);
				}
				makers5[t]->bulkCancel(i, engine, distUreal);
				if (!(makers5[t]->cancelCollector.empty()))
				{
					for (auto& c : makers5[t]->cancelCollector)
						exchange.process(c);
					exchange.bookTop2(i);
				}
				break;
			case 2:
				if (!(i % takers[t]->arrInt))
				{
					auto o = takers[t]->processSignal(i, QL.first[i], engine, distUreal);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers5[c.restid]->confirmTrade(c);
						else if (pRoot == 4)
							jumper1->confirmTrade(c);
						else
							providers5[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			default:
				if (i == informed1->arrInt)
				{
					auto o = informed1->processSignal(i);
					exchange.process(o);
					for (auto& c : exchange.tradeconfirms)
					{
						auto pRoot = c.restid / 1000;
						if (pRoot == 3)
							makers5[c.restid]->confirmTrade(c);
						else if (pRoot == 4)
							jumper1->confirmTrade(c);
						else
							providers5[c.restid]->confirmTrade(c);
					}
					exchange.bookTop2(i);
				}
				break;
			}
			if (distUreal(engine) < jAlpha)
			{
				jumper1->processSignal(exchange.tob.back(), i, QL.first[i], engine, distUreal);
				if (!(jumper1->cancelCollector.empty())) // don't need to check this?
				{
					for (auto& c : jumper1->cancelCollector)
						exchange.process(c);
				}
				if (!(jumper1->quoteCollector.empty())) // don't need to check this?
				{
					for (auto& o : jumper1->quoteCollector)
						exchange.process(o);
				}
				exchange.bookTop2(i);
			}
		}
	}
}
/*
void Runner::run()
{
	exchange = Orderbook();
	QL = buildLambda();
	if (provider) { buildProviders(); }
	if (taker) { buildTakers(); }
	if (informed) { buildInformed(); }
	if (jumper) { buildPennyJumper(); }
	if (maker) { buildMarketMakers(); }
//	seedBook();
//	if (provider) { makeSetup(); }
//	if (mpi == 1)
//	{
//		if (jumper)
//			runMCSPJ1();
//		else
//			runMCS1();
//	}
//	else
//	{
//		if (jumper)
//			runMCSPJ5();
//		else
//			runMCS5();
//	}
//	std::string tcsv = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\trades_1.csv";
//	exchange.tradesToCsv(tcsv);
//	std::string qtcsv = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\qtake_1.csv";
//	qTakeToCsv(qtcsv);
//	std::string mmcsv = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\mm_1.csv";
//	mmProfitsToCsv(mmcsv);
}
*/