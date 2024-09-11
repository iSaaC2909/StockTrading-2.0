#ifndef YAHOO_FINANCE_API_H
#define YAHOO_FINANCE_API_H

#include <curl/curl.h>

#include "Stock.h"

#include "../temporal/Interval.h"

class YahooFinanceAPI {
	private:
		static YahooFinanceAPI* instance;
		YahooFinanceAPI();

		/**
		 * Internal helper callback for downloading Yahoo CSV data.
		 */
		static size_t writeCallback(char* content,
							 size_t size,
							 size_t nmemb,
							 void* userdata);

		/**
		 * Internal helper downloading Yahoo CSV data.
		 */
		static std::string downloadYahooFinanceCSV(const std::string symbol,
									 const time_t start,
									 const time_t end,
									 const Interval interval);

	public:

		/**
		 * Returns the Singleton YahooFinanceAPI instance.
		 */
		static YahooFinanceAPI* getInstance();

		/**
		 * Populates the given Stock object with historical YahooFinance data. The data covers the range [start, end) retrieving daily information at the given interval.
		 */
		void populateHistoricalStockData(Stock& stock, std::time_t start, std::time_t end, Interval interval);

		/**
		 * Populates the given Stock object with historical YahooFinance data. The data covers the range [start, end) retrieving daily information at the given interval.
		 */
		void populateHistoricalStockData(Stock& stock, std::string start, std::string end, Interval interval);
};

#endif
