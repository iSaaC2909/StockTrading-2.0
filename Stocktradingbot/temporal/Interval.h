#ifndef INTERVAL_H
#define INTERVAL_H

#include <string>

enum Interval {
	DAILY,
	WEEKLY,
	MONTHLY
};

static const std::string IntervalStrings[] { "1d", "1wk", "1mo" };

std::string getIntervalString(const Interval interval);

std::ostream& operator<<(std::ostream& out, const Interval& interval);

#endif