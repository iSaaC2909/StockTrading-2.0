#ifndef STOCK_SIMULATION_H
#define STOCK_SIMULATION_H

#include <vector>
#include <unordered_map>

#include "Stock.h"
#include "YahooFinanceAPI.h"
#include "StockSimulationBuilder.h"

#include "../bot/Bot.h"

#include "../temporal/TemporalIterator.h"

// Forward declaration to fix cyclical dependency between StockSimulation and StockSimulationBuilder.
class StockSimulationBuilder;

class StockSimulation {
	private:
		// Makeshift bi-map
		std::unordered_map<Stock*, std::vector<Bot*>> stock_mapping;
		std::unordered_map<Bot*, std::vector<Stock*>> bot_mapping;
		std::time_t start;
		std::time_t end;
		Interval interval;

		StockSimulation(std::unordered_map<Stock*, std::vector<Bot*>> stock_mapping, std::unordered_map<Bot*, std::vector<Stock*>> bot_mapping, std::time_t start, std::time_t end, Interval interval);

	public:
		static StockSimulationBuilder builder();

		~StockSimulation();

		/**
		 * Executes the stock simulation.
		 */
		void run();

		friend class StockSimulationBuilder;
};

#endif