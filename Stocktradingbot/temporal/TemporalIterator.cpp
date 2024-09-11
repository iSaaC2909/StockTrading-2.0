#include "TemporalIterator.h"

TemporalIterator::TemporalIterator(std::time_t start, std::time_t end, Interval interval) {
	// Adjust the next_date to be the first date on the given interval.
	this->next_date = previousDate(nextDate(start, interval), interval);

	// If we overcorrected to outside of the range, move it forward.
	if (this->next_date < this->start) {
		this->next_date = nextDate(start, interval);
	}

	this->start = start;
	this->end = end;
	this->interval = interval;
}

TemporalIterator::TemporalIterator(std::string start, std::string end, Interval interval) : TemporalIterator(stringToTime(start), stringToTime(end), interval) {}

/**
 * Returns the next time_t object. Moves the cursor position forwards in time by the given interval.
 */
std::time_t TemporalIterator::next() {
	if (!this->hasNext()) {
		std::stringstream ss;
		ss << timeToString(this->next_date) << " is outside of the interval [" << timeToString(this->start) << " - " << timeToString(this->end) << ")!";

		throw std::out_of_range(ss.str());
	}

	// Next returns what we just walked over, store the old next_date to return.
	time_t temp = this->next_date;

	// Move the next_date forward by the given interval.
	this->next_date = nextDate(this->next_date, this->interval);

	return temp;
}

/**
 * Returns true if this iterator has more elements when traversing forward in time.
 */
bool TemporalIterator::hasNext() const {
	// The range is exclusive, we can never be at the end date.
	return this->next_date < this->end;
}

/**
 * Returns the previous time_t object. Moves the cursor position backwards in time by the given interval.
 */
std::time_t TemporalIterator::previous() {
	if (!this->hasPrevious()) {
		std::stringstream ss;
		ss << timeToString(previousDate(this->next_date, this->interval)) << " is outside of the interval [" << timeToString(this->start) << " - " << timeToString(this->end) << ")!";

		throw std::out_of_range(ss.str());
	}

	// Move the next_date backwards by the given interval.
	this->next_date = previousDate(this->next_date, this->interval);

	// Previous returns where we will go next so we do not need a temporary variable.
	return this->next_date;
}

/**
 * Returns true if this iterator has more elements when traversing backwards in time.
 */
bool TemporalIterator::hasPrevious() const {
	// Preemptively check if the next move backwards will put us too far.
	return this->start <= previousDate(this->next_date, this->interval);
}