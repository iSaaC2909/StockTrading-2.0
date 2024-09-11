#ifndef STOCK_H
#define STOCK_H

#include <unordered_map>

#include "StockSnapshot.hpp"

class Stock {
	private:
		std::string symbol;
		std::unordered_map<std::time_t, const StockSnapshot*> snapshots;

	public:
		Stock(std::string symbol);
		~Stock();

		std::string getSymbol() const;
		const StockSnapshot getSnapshot(std::time_t date) const;
		const StockSnapshot getSnapshot(std::string date) const;

		friend std::ostream& operator<<(std::ostream& out, const Stock& stock);

		// Only YahooFinanceAPI should be able to access snapshots to populate it with StockSnapshots.
		friend class YahooFinanceAPI;
};

#endif
