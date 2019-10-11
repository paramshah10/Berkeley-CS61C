#ifndef TIMEHM_H
#define TIMEHM_H

#include <stdbool.h>

/*
 *  Simple struct representing time consisting of only hours and minutes.
 *  It can be used to represent both a time of the day, or a duration.
 */
typedef struct {
  int hours;
  int minutes;
} timeHM_t;

/*
 *  Given t1 and t2, determines whether t1 is after t2.
 */
bool isAfter(timeHM_t* t1, timeHM_t* t2);

/*
 *  Given t1 and t2, determines whether t1 and t2 are the same time.
 */
bool isEqual(timeHM_t* t1, timeHM_t* t2);

/*
 *  Given a string in the format of hh:mm, stores the corresponding time struct to where result points.
 *  Returns success.
 */
bool stringToTime(char* str, timeHM_t* result);

/*
 *  Prints the time in hh:mm format.
 */
void printTime(timeHM_t* t);

#endif

