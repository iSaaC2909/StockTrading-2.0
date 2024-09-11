#ifndef TEMPORAL_ITERATOR_H
#define TEMPORAL_ITERATOR_H

#include <ctime>
#include <exception>

#include "TemporalUtils.h"

class TemporalIterator {
	private:
		std::time_t next_date;
		std::time_t start;
		std::time_t end;
		Interval interval;

	public:
		TemporalIterator(std::time_t start, std::time_t end, Interval interval);
		TemporalIterator(std::string start, std::string end, Interval interval);

		/**
		 * Returns the next time_t object. Moves the cursor position forwards in time by the given interval.
		 */
		std::time_t next();

		/**
		 * Returns true if this iterator has more elements when traversing forward in time.
		 */
		bool hasNext() const;

		/**
		 * Returns the previous time_t object. Moves the cursor position backwards in time by the given interval.
		 */
		std::time_t previous();

		/**
		 * Returns true if this iterator has more elements when traversing backwards in time.
		 */
		bool hasPrevious() const;
};

#endif