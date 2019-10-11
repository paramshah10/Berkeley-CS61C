#ifndef FLIGHTS_H
#define FLIGHTS_H

#include <stdbool.h>
#include "flight_structs.h"
#include "timeHM.h"

flightSys_t* createSystem(void);
flight_t* createFlight(airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost);
void deleteSystem(flightSys_t* system);
void deleteFlight(flight_t* flight);
void addAirport(flightSys_t* system, char* name);
airport_t* getAirport(flightSys_t* system, char* name);
void printAirports(flightSys_t* system);
void addFlight(airport_t* source, airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost);
void printSchedule(airport_t* system);
bool getNextFlight(airport_t* source, airport_t* destination, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival,
                   int* cost);
int validateFlightPath(flight_t** flight_list, char** airport_name_list, int size);

#endif

