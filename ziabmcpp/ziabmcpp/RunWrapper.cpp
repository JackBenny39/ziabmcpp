// RunWrapper.cpp

#include "stdafx.h"

#include <chrono>
#include <iostream>

#include "Runner.h"
#include "Sharedstx.h"

using namespace std::chrono;

Prc mpi = 1;
Step prime1 = 20;
Step runSteps = 100001;
Step writeInterval = 5000;
Step informedRun = 3;
bool provider = true;
bool taker = true;
bool informed = false;
bool jumper = false;
bool maker = true;
unsigned numProviders = 38;
unsigned numTakers = 50;
unsigned numMMs = 1;
unsigned mmQuotes = 12;
unsigned mmRange = 60;
Qty providerMaxQ = 1;
Qty takerMaxQ = 1;
Qty informedQ = 1;
Qty mmMaxQ = 1;
double pAlpha = 0.0375;
double pDelta = 0.025;
double qProvide = 0.5;
double tMu = 0.001;
double iMu = 0.01;
double jAlpha = 0.05;
double mmDelta = 0.025;
bool qTake = true;
double lambda0 = 100.0;
double whiteNoise = 0.001;
double cLambda = 5.0;
std::random_device random_device;
std::mt19937 engine{ random_device() };
Side informedSide = Side::BUY;
unsigned seed = 39;

std::string dir = "C:\\Users\\user\\Documents\\Agent-Based Models\\csv files\\";
std::string historyf = dir + "history_1.csv";
std::string sipf = dir + "sip_1.csv";
std::string tradesf = dir + "trades_1.csv";
std::string qtf = dir + "qtake_1.csv";
std::string mmf = dir + "mm_1.csv";

int main()
{
	auto t0 = high_resolution_clock::now();
	Runner market1 = Runner(mpi, prime1, runSteps, writeInterval,
		provider, numProviders, providerMaxQ, pAlpha, pDelta, qProvide,
		taker, numTakers, takerMaxQ, tMu,
		informed, informedRun, informedQ, iMu, informedSide,
		jumper, jAlpha,
		maker, numMMs, mmMaxQ, mmQuotes, mmRange, mmDelta,
		qTake, lambda0, whiteNoise, cLambda, engine, seed);

	market1.run();

	market1.exchange.ordersToCsv(historyf);
	market1.exchange.sipToCsv(sipf);
//	market1.exchange.tradesToCsv(tradesf);
	market1.qTakeToCsv(qtf);
//	market1.mmProfitsToCsv(mmf);

	auto t1 = high_resolution_clock::now();
	std::cout << duration_cast<seconds>(t1 - t0).count() << " s\n";

	return 0;
}