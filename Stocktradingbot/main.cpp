#include <iostream>

#include "stock/StockSimulation.h"
#include "bot/Bot.h"
#include "analytics.h"

int main() {

	std::cout << "Stock Simulator" << std::endl;
	std::cout << "Enter number of bots: ";
	int numBots;
	std::cin >> numBots;
	
	std::vector<Bot *> bots;

	
	for(int i = 0; i<numBots; ++i)
	{

		int type;
		std::string name;
		double startingBalance;
		int depositPeriod;
		double depositAmount;

		std::cout << "Enter Bot Type: (0 - Conservative, 1 - Aggressive, 2- Passive) " << std::endl;
		std::cin >> type;
		BotType bot_type = (BotType) type;

		std::cout << "Enter Bot Name: " << std::endl;
		std::cin >> name;

		std::cout << "Enter Bot Starting Balance: " << std::endl;
		std::cin >> startingBalance;

		std::cout << "Enter Bot Deposit Period: " << std::endl;
		std::cin >> depositPeriod;

		std::cout << "Enter Bot Deposit Amount: " << std::endl;
		std::cin >> depositAmount;

		Bot* bot = new Bot();
		bot->setBotType(name,bot_type, startingBalance,depositPeriod,depositAmount);
		bots.push_back(bot);
	}

	std::string start;
	std::string end;

	std::cout<< "Enter Start Date (YYYY-MM-DD): ";
	std::cin >> start;

	std::cout<< "Enter End Date (YYYY-MM-DD): ";
	std::cin >> end;

	int interval;
	std::cout << "Enter interval (Daily = 0, Weekly = 1, Monthly = 2): ";
	std::cin >> interval;
	Interval interval_ = (Interval) interval;

	int numStocks;
	std::unordered_set<std::string> symbols;
	std::cout << "Enter number of stocks to input: ";
	std::cin >> numStocks;

	for(int i = 0; i<numStocks; ++i)
	{
		std::string symbol;
		std::cout << "Enter stock symbol: ";
		std::cin >> symbol;
		symbols.insert(symbol);
	}	

	StockSimulationBuilder builder = StockSimulationBuilder();
	builder .withStartDate(start)
			.withEndDate(end)
			.withInterval(interval_)
			.withStocks(symbols);

	for(auto bot :bots)
	{
		builder.withBot(bot);
	}		

	

	StockSimulation* simulation = builder.build();

	simulation->run();

	delete simulation;
	for(auto bot :bots)
	{
		delete bot;
	}	

	// Bot* bot1 = new Bot();
	// bot1->setBotType("Conservative Bot",CONSERVATIVE, 1000, 14, 100);

	// Bot* bot2 = new Bot();
	// bot2->setBotType("Aggressive Bot",AGGRESSIVE, 1000, 14, 100);

	// Bot* bot3 = new Bot();
	// bot3->setBotType("Passive Bot",PASSIVE, 1000, 14, 100);

	//                                 // .withStartDate("2021-01-01")
	//                                 // .withEndDate("2021-011-30")
	//                                 // .withInterval(DAILY)
	//                                 // // Add Google, Tesla, and Amazon to the simulation.
	//                                 // .withStocks({"GOOGL", "TSLA", "AMZN","AAPL"})
	//                                 // // Bot 1 will watch all stocks.
	//                                 // .withBot(bot1)
	// 								// .withBot(bot2)
	// 								// .withBot(bot3)
	//                                 // Bot 2 will only watch Google stock.
	//                                 // .withBotSubscribedTo(bot2, {"GOOGL"})
	//                                 // Bot 3 will watch Google and Tesla stock.
	//                                 // .withBotSubscribedTo(bot3, {"GOOGL", "TSLA"})
	//                                 // .build();

}
