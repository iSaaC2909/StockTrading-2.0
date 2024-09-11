#include "YahooFinanceAPI.h"

YahooFinanceAPI* YahooFinanceAPI::instance = nullptr;

YahooFinanceAPI::YahooFinanceAPI() {}

/**
 * Returns the Singleton YahooFinanceAPI instance.
 */
YahooFinanceAPI* YahooFinanceAPI::getInstance() {
	if (YahooFinanceAPI::instance == nullptr) {
		YahooFinanceAPI::instance = new YahooFinanceAPI();
	}

	return YahooFinanceAPI::instance;
}

/**
 * Populates the given Stock object with historical YahooFinance data. The data covers the range [start, end) retrieving daily information at the given interval.
 */
void YahooFinanceAPI::populateHistoricalStockData(Stock& stock, time_t start, time_t end, Interval interval) {
	std::string csv = this->downloadYahooFinanceCSV(stock.getSymbol(), start, end, interval);
	std::istringstream csv_iss(csv);
	std::string line;

	// Remove the header line
	std::getline(csv_iss, line);

	std::string date_string;
	double open;
	double high;
	double low;
	double close;
	char comma;

	while (std::getline(csv_iss, line)) {
		std::istringstream iss(line);

		getline(iss, date_string, ',');

		if (date_string != "null") {
			time_t date = stringToTime(date_string);
			// Ignores Adjusted close and volume but they are available as well.
			iss >> open >> comma >> high >> comma >> low >> comma >> close;

			stock.snapshots[date] = new StockSnapshot(stock.getSymbol(), date, open, high, low, close);

		}
	}
}

/**
 * Populates the given Stock object with historical YahooFinance data. The data covers the range [start, end) retrieving daily information at the given interval.
 */
void YahooFinanceAPI::populateHistoricalStockData(Stock& stock, std::string start, std::string end, Interval interval) {
	populateHistoricalStockData(stock, stringToTime(start), stringToTime(end), interval);
}

/**
 * Internal helper callback for downloading Yahoo CSV data.
 */
size_t YahooFinanceAPI::writeCallback(char *content, size_t size, size_t nmemb, void *userdata) {
	// Append the content to user data
	((std::string*) userdata)->append(content, size * nmemb);

	// Return the real content size
	return size * nmemb;
}

/**
 * Internal helper downloading Yahoo CSV data.
 */
std::string YahooFinanceAPI::downloadYahooFinanceCSV(const std::string symbol, const std::time_t start, const std::time_t end, const Interval interval) {
	std::stringstream url_ss;
	url_ss << "https://query1.finance.yahoo.com/v7/finance/download/";
	url_ss << symbol;
	url_ss << "?period1=" << start;
	url_ss << "&period2=" << end;
	url_ss << "&interval=" << interval;
	url_ss << "&events=history";

	CURL* curl = curl_easy_init();
	std::string responseBuffer;

	if (curl) {
		std::string url = url_ss.str().c_str();

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Write result into the buffer
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, YahooFinanceAPI::writeCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBuffer);

		// Perform the request
		CURLcode res = curl_easy_perform(curl);

		// Cleanup
		curl_easy_cleanup(curl);
	}

	return responseBuffer;
}