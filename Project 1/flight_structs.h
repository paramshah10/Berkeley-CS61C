/*
 * CS61C Summer 2019
 * Name: Param Shah
 * Login: paramshah10 (instructional account login: agt)
 */

#ifndef FLIGHT_STRUCTS_H
#define FLIGHT_STRUCTS_H

#include "timeHM.h"

typedef struct flightSys flightSys_t;
typedef struct airport airport_t;
typedef struct flight flight_t;

struct flightSys 
{
	// Place the members you think are necessary for the flightSys struct here.
	airport_t* airports;
	int numAirports;
	int size;
};

struct airport 
{
	// Place the members you think are necessary for the airport struct here.
	char name[1024];
	flight_t* flightSchedule;
	int numflights;
	int size;
};

struct flight 
{
	// Place the members you think are necessary for the flight struct here.
	airport_t* destAirport;
	timeHM_t* TOD;
	timeHM_t* TOA;
	int cost;
};

#endif
