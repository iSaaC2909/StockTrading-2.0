#ifndef STOCK_SIMULATION_BUILDER_H
#define STOCK_SIMULATION_BUILDER_H

#include <unordered_set>

#include "StockSimulation.h"

#include "../bot/Bot.h"

// Forward declaration to fix cyclical dependency between StockSimulation and StockSimulationBuilder.
class StockSimulation;

class StockSimulationBuilder {
	private:
		std::time_t start;
		bool has_start;
		std::time_t end;
		bool has_end;
		Interval interval;
		bool has_interval;

		// Using sets to make sure there are no duplicates.
		std::unordered_set<std::string> symbols;
		std::unordered_set<Bot*> bots_subscribed_to_all;
		std::unordered_map<Bot*, std::unordered_set<std::string>> bots;

		

	public:
		StockSimulationBuilder();
		StockSimulationBuilder& withStartDate(std::time_t start);
		StockSimulationBuilder& withStartDate(std::string start);
		StockSimulationBuilder& withEndDate(std::time_t end);
		StockSimulationBuilder& withEndDate(std::string end);
		StockSimulationBuilder& withInterval(Interval interval);
		StockSimulationBuilder& withStock(std::string symbol);
		StockSimulationBuilder& withStocks(std::unordered_set<std::string> symbols);
		StockSimulationBuilder& withBot(Bot* bot);
		StockSimulationBuilder& withBotSubscribedTo(Bot* bot, std::unordered_set<std::string> symbols);

		StockSimulation* build();

		friend class StockSimulation;
};

#endif