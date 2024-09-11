#include "StockSimulationBuilder.h"

StockSimulationBuilder::StockSimulationBuilder() {
	this->has_start = false;
	this->has_end = false;
	this->has_interval = false;
}

StockSimulationBuilder& StockSimulationBuilder::withStartDate(std::time_t start) {
	this->start = start;
	this->has_start = true;
	return *this;
}

StockSimulationBuilder& StockSimulationBuilder::withStartDate(std::string start) {
	return this->withStartDate(stringToTime(start));
}

StockSimulationBuilder& StockSimulationBuilder::withEndDate(std::time_t end) {
	this->end = end;
	this->has_end = true;
	return *this;
}

StockSimulationBuilder& StockSimulationBuilder::withEndDate(std::string end) {
	return this->withEndDate(stringToTime(end));
}

StockSimulationBuilder& StockSimulationBuilder::withInterval(Interval interval) {
	this->interval = interval;
	this->has_interval = true;
	return *this;
}

StockSimulationBuilder& StockSimulationBuilder::withStock(std::string symbol) {
	this->symbols.insert(symbol);
	return *this;
}

StockSimulationBuilder& StockSimulationBuilder::withStocks(std::unordered_set<std::string> symbols) {
	this->symbols.insert(symbols.begin(), symbols.end());
	return *this;
}

StockSimulationBuilder& StockSimulationBuilder::withBot(Bot* bot) {
	this->bots_subscribed_to_all.insert(bot);
	return *this;
}

StockSimulationBuilder& StockSimulationBuilder::withBotSubscribedTo(Bot* bot, std::unordered_set<std::string> symbols) {
	this->bots[bot] = symbols;
	return *this;
}

StockSimulation* StockSimulationBuilder::build() {
	if (!this->has_start) {
		throw std::logic_error("StockSimulations need a start date!");
	} else if (!this->has_end) {
		throw std::logic_error("StockSimulations need an end date!");
	} else if (!this->has_interval) {
		throw std::logic_error("StockSimulations need an interval!");
	}

	std::unordered_map<Stock*, std::vector<Bot*>> stock_mapping;
	std::unordered_map<Bot*, std::vector<Stock*>> bot_mapping;

	// Create all the Stock objects with the known Bots subscribed to everything.
	for (auto symbol : this->symbols) {
		Stock* stock = new Stock(symbol);

		for (auto bot : this->bots_subscribed_to_all) {
			// Create bi-directional relationship.
			stock_mapping[stock].push_back(bot);
			bot_mapping[bot].push_back(stock);
		}
	}

	// Add each limited Bot to the Stocks it subscribed to.
	for (auto bot_pair : this->bots) {
		for (auto symbol : bot_pair.second) {
			for (auto stock_pair : stock_mapping) {
				if (stock_pair.first->getSymbol() == symbol) {
					// Create bi-directional relationship.
					stock_mapping[stock_pair.first].push_back(bot_pair.first);
					bot_mapping[bot_pair.first].push_back(stock_pair.first);
				}
			}
		}
	}

	return new StockSimulation(stock_mapping, bot_mapping, this->start, this->end, this->interval);
}