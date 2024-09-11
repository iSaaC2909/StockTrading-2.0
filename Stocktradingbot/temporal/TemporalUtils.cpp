#include "TemporalUtils.h"

/**
 * Returns the current timestamp as a time_t object.
 */
std::time_t currentTime() {
	return std::time(NULL);
}

/**
 * Converts the given "yyyy-mm-dd" string into a time_t object.
 */
std::time_t stringToTime(const std::string date) {
	size_t dash1 = date.find("-");
	size_t dash2 = date.find("-", dash1 + 1);

	if (dash1 == std::string::npos || dash2 == std::string::npos) {
		throw std::invalid_argument(date + " is not a valid date!");
	}

	std::string year  = date.substr(0, dash1);
	std::string month = date.substr(dash1 + 1, dash2 - dash1 - 1);
	std::string day   = date.substr(dash2 + 1);

	struct tm time = {0};
	time.tm_year = std::stoi(year)  - 1900;
	time.tm_mon  = std::stoi(month) - 1;
	time.tm_mday = std::stoi(day);

	return mktime(&time);
}

/**
 * Converts the given time_t object into a "yyyy-mm-dd" string.
 */
std::string timeToString(const std::time_t date) {
	std::stringstream ss;
	ss << std::setfill('0');

	struct std::tm* ptm = std::localtime(&date);

	ss << ptm->tm_year + 1900;
	ss << "-";
	ss << std::setw(2) << ptm->tm_mon + 1;
	ss << "-";
	ss << std::setw(2) << ptm->tm_mday;

	return ss.str();
}

/**
 * Returns the time_t object representing the next in the given interval.
 */
std::time_t nextDate(const std::time_t date, Interval interval) {
	switch (interval) {
		case WEEKLY:
			return nextWeek(date);
		case MONTHLY:
			return nextMonth(date);
		default: // DAILY
			return nextDay(date);
	}
}

/**
 * Returns the time_t object representing the previous in the given interval.
 */
std::time_t previousDate(const std::time_t date, Interval interval) {
	switch (interval) {
		case WEEKLY:
			return previousWeek(date);
		case MONTHLY:
			return previousMonth(date);
		default: // DAILY
			return previousDay(date);
	}
}

/**
 * Returns the time_t object representing the day after the given date.
 */
std::time_t nextDay(const std::time_t date) {
	struct tm* ptm = localtime(&date);
	ptm->tm_mday++;
	return mktime(ptm);
}

/**
 * Returns the time_t object representing the day before the given date.
 */
std::time_t previousDay(const std::time_t date) {
	struct tm* ptm = localtime(&date);
	ptm->tm_mday--;
	return mktime(ptm);
}

/**
 * Returns the time_t object representing the Monday after the given date.
 */
std::time_t nextWeek(const std::time_t date) {
	struct tm* ptm = localtime(&date);
	// [# + ((4 - #) * 2)]
	int days = ptm->tm_wday + (4 - ptm->tm_wday) * 2;
	ptm->tm_mday += (days <= 7) ? days : days % 7;
	return mktime(ptm);
}

/**
 * Returns the time_t object representing the Monday before the given date.
 */
std::time_t previousWeek(const std::time_t date) {
	struct tm* ptm = localtime(&date);
	// [# + ((4 - #) * 2)]
	int days = (ptm->tm_wday <= 1) ?  6 : -1;
	ptm->tm_mday -= ptm->tm_wday + days;
	return mktime(ptm);
}

/**
 * Returns the time_t object representing the first of the month after the given date.
 */
std::time_t nextMonth(const std::time_t date) {
	struct tm* ptm = localtime(&date);
	ptm->tm_mon++;
	ptm->tm_mday = 1;
	return mktime(ptm);
}

/**
 * Returns the time_t object representing the first of the month before the given date.
 */
std::time_t previousMonth(const std::time_t date) {
	struct tm* ptm = localtime(&date);
	if (ptm->tm_mday <= 1) {
		ptm->tm_mon--;
	}

	ptm->tm_mday = 1;
	return mktime(ptm);
}

/**
 * Returns true if the time_t object represents a day between Monday and Friday inclusively.
 */
bool isWeekday(const std::time_t date) {
	struct tm* ptm = localtime(&date);
	return 0 < ptm->tm_wday && ptm->tm_wday < 6;
}

/**
 * Returns true if the time_t object represents a Saturday or Sunday.
 */
bool isWeekend(const std::time_t date) {
	return !isWeekday(date);
}