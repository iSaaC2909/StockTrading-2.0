#include "Stock.h"

Stock::Stock(std::string symbol) {
	this->symbol = symbol;
}

Stock::~Stock() {
	for (auto pair : this->snapshots) {
		delete pair.second;
	}
}

std::string Stock::getSymbol() const {
	return this->symbol;
}

const StockSnapshot Stock::getSnapshot(std::time_t date) const {
	std::stringstream ss;

	if (isWeekend(date)) {
		ss << "The Stock market is only opened during buisness days! " << timeToString(date) << " is on the weekend!";
		throw std::out_of_range(ss.str());
	}

	try {
		return *this->snapshots.at(date);
	} catch (std::out_of_range e) {
		ss << "No information for the date " << timeToString(date) << " could be found!";
		throw std::out_of_range(ss.str());
	}
}

const StockSnapshot Stock::getSnapshot(std::string date) const {
	return this->getSnapshot(stringToTime(date));
}

std::ostream& operator<<(std::ostream& out, const Stock& stock) {
	return out << stock.getSymbol();
}