#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "timeHM.h"

bool isAfter(timeHM_t* t1, timeHM_t* t2) {
  if (t1->hours == t2->hours) {
    return t1->minutes > t2->minutes;
  }
  return t1->hours > t2->hours;

}

bool isEqual(timeHM_t* t1, timeHM_t* t2) {
  return t1->hours == t2->hours && t1->minutes == t2->minutes;
}

bool stringToTime(char* str, timeHM_t* result) {
  return 2 == sscanf(str,"%d:%d",&(result->hours),&(result->minutes));
}

void printTime(timeHM_t* t) {
  printf("%02i:%02i",t->hours,t->minutes);
}

