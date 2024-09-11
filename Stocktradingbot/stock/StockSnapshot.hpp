#ifndef STOCK_SNAPSHOT_HPP
#define STOCK_SNAPSHOT_HPP

#include <ctime>
#include <string>
#include <iomanip>

// Used by the toString to represent the date.
#include "../temporal/TemporalUtils.h"

class StockSnapshot {
	private:
		std::string symbol;
		time_t date;
		double open;
		double high;
		double low;
		double close;

		StockSnapshot(std::string symbol, time_t date, double open, double high, double low, double close)  {
			this->symbol = symbol;
			this->date = date;
			this->open = open;
			this->high = high;
			this->low = low;
			this->close = close;
		}

	public:
		inline std::string getSymbol() const {
			return this->symbol;
		}

		inline std::time_t getDate() const {
			return this->date;
		}

		inline std::string getDateString() const {
			return timeToString(this->date);
		}

		inline double getOpening() const {
			return this->open;
		}

		inline double getHigh() const {
			return this->high;
		}

		inline double getLow() const {
			return this->low;
		}

		inline double getClosing() const {
			return this->close;
		}

		std::string toString() const {
			std::ostringstream oss;
			oss << std::fixed << std::showpoint << std::setprecision(2);
			oss << "Symbol: " << this->getSymbol() << " ";
			oss << "Date: " << this->getDateString() << " ";
			oss << "Open: $" << this->getOpening() << " ";
			oss << "High: $" << this->getHigh() << " ";
			oss << "Low: $" << this->getLow() << " ";
			oss << "Close: $" << this->getClosing();

			return oss.str();
		}

		friend std::ostream& operator<<(std::ostream& out, const StockSnapshot& snapshot) {
			return out << snapshot.toString();
		}

		// Only YahooFinanceAPI can create StockSnapshots.
		friend class YahooFinanceAPI;
};

#endif
