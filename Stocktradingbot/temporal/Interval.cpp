#include "Interval.h"

std::string getIntervalString(const Interval interval) {
	return IntervalStrings[interval];
}

std::ostream& operator<<(std::ostream& out, const Interval& interval) {
	return out << getIntervalString(interval);
}