#ifndef TEMPORAL_UTILS_H
#define TEMPORAL_UTILS_H

#include <iomanip>
#include <string>
#include <ctime>
#include <sstream>

#include "Interval.h"

/**
 * Returns the current timestamp as a time_t object.
 */
std::time_t currentTime();

/**
 * Converts the given "yyyy-mm-dd" string into a time_t object.
 */
std::time_t stringToTime(const std::string date);

/**
 * Converts the given time_t object into a "yyyy-mm-dd" string.
 */
std::string timeToString(const std::time_t date);

/**
 * Returns the time_t object representing the next in the given interval.
 */
std::time_t nextDate(const std::time_t date, Interval interval);

/**
 * Returns the time_t object representing the previous in the given interval.
 */
std::time_t previousDate(const std::time_t date, Interval interval);

/**
 * Returns the time_t object representing the day after the given date.
 */
std::time_t nextDay(const std::time_t date);

/**
 * Returns the time_t object representing the day after the given date.
 */
std::time_t previousDay(const std::time_t date);

/**
 * Returns the time_t object representing the Monday after the given date.
 */
std::time_t nextWeek(const std::time_t date);

/**
 * Returns the time_t object representing the Monday before the given date.
 */
std::time_t previousWeek(const std::time_t date);

/**
 * Returns the time_t object representing the first of the month after the given date.
 */
std::time_t nextMonth(const std::time_t date);

/**
 * Returns the time_t object representing the first of the month before the given date.
 */
std::time_t previousMonth(const std::time_t date);

/**
 * Returns true if the time_t object represents a day between Monday and Friday inclusively.
 */
bool isWeekday(const std::time_t date);

/**
 * Returns true if the time_t object represents a Saturday or Sunday.
 */
bool isWeekend(const std::time_t date);

#endif
