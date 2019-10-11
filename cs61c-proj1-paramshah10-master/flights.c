/*
 * CS61C Summer 2019
 * Name: Param Shah
 * Login: paramshah10
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "flight_structs.h"
#include "timeHM.h"

#define AIRPORTS 5
#define NUMFLIGHTS 10

 /*
  *  This should be called if memory allocation failed.
  */
static void allocation_failed(void) {
	fprintf(stderr, "Out of memory.\n");
	exit(EXIT_FAILURE);
}

/*
 *  Creates and initializes a flight system, which stores the flight schedules of several airports.
 *  Returns a pointer to the system created.
 */
flightSys_t* createSystem(void) 
{	
	flightSys_t* newSystem = (flightSys_t*)malloc(sizeof(flightSys_t));
	
	if (!newSystem)
	{
		allocation_failed();
	}
	newSystem->numAirports = 0;
	newSystem->size = AIRPORTS;

	newSystem->airports = (airport_t*)calloc(AIRPORTS, sizeof(airport_t));
	
	if (newSystem->airports == NULL)
	{
		allocation_failed();
	}
	
	for (int i = 0; i < AIRPORTS; i++)
	{
		newSystem->airports[i].flightSchedule = (flight_t*)calloc(NUMFLIGHTS, sizeof(flight_t));
		if (newSystem->airports[i].flightSchedule == NULL)
			allocation_failed();
		newSystem->airports[i].numflights = 0;
		newSystem->airports[i].size = NUMFLIGHTS;
		for (int j = 0; j < NUMFLIGHTS; j++)
		{
			newSystem->airports[i].flightSchedule[j].TOA = (timeHM_t*)calloc(1, sizeof(timeHM_t));
			newSystem->airports[i].flightSchedule[j].TOD = (timeHM_t*)calloc(1, sizeof(timeHM_t));
		}
	}

	return newSystem;
}

/*
 *   Given a destination airport, departure and arrival times, and a cost, return a pointer to new flight_t.
 *
 *   Note that this pointer must be available to use even after this function returns.
 *   (What does this mean in terms of how this pointer should be instantiated?)
 *   Additionally you CANNOT assume that the `departure` and `arrival` pointers will persist after this function completes.
 *   (What does this mean about copying dep and arr?)
 */

flight_t* createFlight(airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) 
{
	if (destination == NULL || departure == NULL || arrival == NULL || cost <= 0)
	{
		return NULL;
	}

	else if (isAfter(departure, arrival))
	{
		return NULL;
	}

	flight_t* newflight = (flight_t*)calloc(1, sizeof(flight_t));
	if (newflight == NULL)
	{
		allocation_failed();
	}

	newflight->cost = cost;
	newflight->destAirport = destination;
	
	newflight->TOA = (timeHM_t*)calloc(1, sizeof(timeHM_t));
	newflight->TOA->hours = arrival->hours;
	newflight->TOA->minutes = arrival->minutes;
	
	newflight->TOD = (timeHM_t*)calloc(1, sizeof(timeHM_t));
	newflight->TOD->hours = departure->hours;
	newflight->TOD->minutes = departure->minutes;

	return newflight;
}

/*
 *  Frees all memory associated with this system; that's all memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* system) 
{
	if (system == NULL)
	{
		return;
	}

	for (int i = 0; i < system->size; i++)
	{
		for (int j = 0; j < system->airports[i].size; j++)
		{
			free(system->airports[i].flightSchedule[j].TOA);
			free(system->airports[i].flightSchedule[j].TOD);
		}

		free(system->airports[i].flightSchedule);
	}

	free(system->airports);
	free(system);
}

/*
 *  Frees all memory allocated for a single flight. You may or may not decide
 *  to use this in delete system but you must implement it.
 */
void deleteFlight(flight_t* flight)
{
	if (flight == NULL)
	{
		return;
	}

	free(flight->TOA);
	free(flight->TOD);
	free(flight);
}


/*
 *  Adds a airport with the given name to the system. You must copy the string and store it.
 *  Do not store `name` (the pointer) as the contents it point to may change.
 */
void addAirport(flightSys_t* system, char* name) 
{
	if (system == NULL || name == NULL)
	{
		return;
	}

	if (system->numAirports == system->size)
	{
		system->airports = realloc(system->airports, system->size + 5);
		system->size += 5;
		
		for (int i = system->numAirports; i < system->size; i++)
		{
			system->airports[i].flightSchedule = (flight_t*)calloc(NUMFLIGHTS, sizeof(flight_t));
		}
	}

	strncpy(system->airports[system->numAirports].name, name, 1024);        //THIS MIGHT NEED A FIX
	system->airports[system->numAirports].numflights = 0;
	system->airports[system->numAirports].size = NUMFLIGHTS;

	system->numAirports++;
}


/*
 *  Returns a pointer to the airport with the given name.
 *  If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* system, char* name) 
{
	if (system == NULL)
	{
		return NULL;
	}

	airport_t* temp = NULL;
	
	for (int i = 0; i < system->numAirports; i++)
	{
		if (strcmp(system->airports[i].name, name) == 0)
		{
			temp = &(system->airports[i]);
			break;
		}
	}

	return temp;
}


/*
 *  Print each airport name in the order they were added through addAirport, one on each line.
 *  Make sure to end with a new line. You should compare your output with the correct output
 *  in `flights.out` to make sure your formatting is correct.
 */
void printAirports(flightSys_t* system) 
{
	if (system == NULL)
	{
		return;
	}
	for (int i = 0; i < system->numAirports; i++)
	{
		printf("%s\n", system->airports[i].name);
	}
}

/*
 *  Adds a flight to source's schedule, stating a flight will leave to destination at departure time and arrive at arrival time.
 */
void addFlight(airport_t* source, airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) 
{
	if (source == NULL || destination == NULL || departure == NULL || arrival == NULL || cost <= 0)
	{
		return;
	}

	if (source->numflights == source->size)
	{
		source->flightSchedule = realloc(source->flightSchedule, source->size + 10);
		source->size += 10;

		for (int i = source->numflights; i < source->size; i++)
		{
			source->flightSchedule[i].TOA = (timeHM_t*)calloc(1, sizeof(timeHM_t));
			source->flightSchedule[i].TOD = (timeHM_t*)calloc(1, sizeof(timeHM_t));
		}
	}

	source->flightSchedule[source->numflights].cost = cost;
	source->flightSchedule[source->numflights].destAirport = destination;
		
	source->flightSchedule[source->numflights].TOA->hours = arrival->hours;
	source->flightSchedule[source->numflights].TOA->minutes = arrival->minutes;

	source->flightSchedule[source->numflights].TOD->hours = departure->hours;
	source->flightSchedule[source->numflights].TOD->minutes = departure->minutes;

	source->numflights++;
}


/*
 *  Prints the schedule of flights of the given airport.
 *
 *  Prints the airport name on the first line, then prints a schedule entry on each
 *  line that follows, with the format: "destination_name departure_time arrival_time $cost_of_flight".
 *
 *  You should use `printTime()` (look in `timeHM.h`) to print times, and the order should be the same as
 *  the order they were added in through addFlight. Make sure to end with a new line.
 *  You should compare your output with the correct output in flights.out to make sure your formatting is correct.
 */
void printSchedule(airport_t* airport) 
{
	if (airport == NULL)
	{
		return;
	}

	printf("%s\n", airport->name);
	for (int i = 0; i < airport->numflights; i++)
	{
		printf("%s ", airport->flightSchedule[i].destAirport->name);
		printTime(airport->flightSchedule[i].TOD);
		printf(" ");
		printTime(airport->flightSchedule[i].TOA);
		printf(" ");
		printf("$%d\n", airport->flightSchedule[i].cost);
	}
}


/*
 *   Given a source and destination airport, and the time now, finds the next flight to take based on the following rules:
 *   1) Finds the earliest arriving flight from source to destination that departs after now.
 *   2) If there are multiple earliest flights, take the one that costs the least.
 *
 *   If a flight is found, you should store the flight's departure time, arrival time, and cost in the `departure`, `arrival`,
 *   and `cost` params and return true. Otherwise, return false.
 *
 *   Please use the functions `isAfter()` and `isEqual()` from `timeHM.h` when comparing two timeHM_t objects and compare
 *   the airport names to compare airports, not the pointers.
 */
bool getNextFlight(airport_t* source, airport_t* destination, timeHM_t* now, timeHM_t* departure, timeHM_t* arrival, int* cost)
{
	if (source == NULL || destination == NULL || now == NULL)
	{
		return false;
	}

	flight_t* fl = calloc(1, sizeof(flight_t));		//temp flight to store the details of the best flight found
	fl->TOD = calloc(1, sizeof(timeHM_t));
	fl->TOA = calloc(1, sizeof(timeHM_t));
	fl->TOD->hours = 25;
	fl->TOD->minutes = 61;

	for (int i = 0; i < source->numflights; i++)		//for all the flights in source airport
	{
		if (strcmp(source->flightSchedule[i].destAirport->name, destination->name) == 0)		//if found the destination airport in source's list
		{
			if (isAfter(source->flightSchedule[i].TOD, now))		//if the departure time of the current flight is after now
			{
				if (isAfter(fl->TOD, source->flightSchedule[i].TOD))		//if the current flights departure is lower than the lowest found till now
				{
					fl->TOD->hours = source->flightSchedule[i].TOD->hours;			//copy all the contents of the current flight to the temp flight
					fl->TOD->minutes = source->flightSchedule[i].TOD->minutes;
					fl->TOA->hours = source->flightSchedule[i].TOA->hours;
					fl->TOA->minutes = source->flightSchedule[i].TOA->minutes;
					fl->destAirport = source->flightSchedule[i].destAirport;
					fl->cost = source->flightSchedule[i].cost;
				}

				else if (isEqual(fl->TOD, source->flightSchedule[i].TOD))		//if current flight's departure is equal to the lowest
				{
					if (fl->cost > source->flightSchedule[i].cost)			//if the cost of the current flight is less than what's found till now
					{
						fl->TOD->hours = source->flightSchedule[i].TOD->hours;			//copy all the contents of the current flight to the temp flight
						fl->TOD->minutes = source->flightSchedule[i].TOD->minutes;
						fl->TOA->hours = source->flightSchedule[i].TOA->hours;
						fl->TOA->minutes = source->flightSchedule[i].TOA->minutes;
						fl->destAirport = source->flightSchedule[i].destAirport;
						fl->cost = source->flightSchedule[i].cost;
					}
				}
			}
		}
	}

	if (fl->TOD->hours == 25 || fl->TOD->minutes == 61)		//if hours or minutes is -1 (i.e. no flight found)
	{
		free(fl->TOA);
		free(fl->TOD);
		free(fl);
		return false;
	}

	else
	{
		departure->hours = fl->TOD->hours;			//set the parameters that need to be changed by the values in the temp flight
		departure->minutes = fl->TOD->minutes;
		
		arrival->hours = fl->TOA->hours;
		arrival->minutes = fl->TOA->minutes;

		*cost = fl->cost;

		free(fl->TOA);
		free(fl->TOD);
		free(fl);
		return true;
	}
}

/*
 *  Given a list of flight_t pointers (`flight_list`) and a list of destination airport names (`airport_name_list`),
 *  first confirm that it is indeed possible to take these sequences of flights, (i.e. be sure that the i+1th flight departs
 *  after or at the same time as the ith flight arrives) (HINT: use the `isAfter()` and `isEqual()` functions).
 *  Then confirm that the list of destination airport names match the actual destination airport names of the provided flight_t structs.
 *
 *  `size` tells you the number of flights and destination airport names to consider. Be sure to extensively test for errors.
 *  As one example, if you encounter NULL's for any values that you might expect to be non-NULL return -1, but test for other possible errors too.
 *
 *  Return from this function the total cost of taking these sequence of flights.
 *  If it is impossible to take these sequence of flights,
 *  if the list of destination airport names doesn't match the actual destination airport names provided in the flight_t struct's,
 *  or if you run into any errors mentioned previously or any other errors, return -1.
 */
int validateFlightPath(flight_t** flight_list, char** airport_name_list, int size) 
{
	if(flight_list == NULL || airport_name_list == NULL)
		return -1;
	if (size <= 0)
		return -1;

	int total = 0;

	if (size == 1)
	{
		return flight_list[0]->cost;
	}

	else
	{
		for (int i = 0; i < size - 1; i++)
		{
			if (flight_list[i] == NULL || airport_name_list[i] == NULL)		//if any of the pointers of the lists are NULL
			{
				return -1;
			}

			else if (flight_list[i]->destAirport == NULL)		//if the pointer to the destination airport is NULL
			{
				return -1;
			}

			else if (strcmp(flight_list[i]->destAirport->name, airport_name_list[i]) != 0)		//if the name of the destination airport in flight_list and the airport_name_list don't match
			{
				return -1;
			}

			else if (flight_list[i]->TOA == NULL || flight_list[i]->TOD == NULL || flight_list[i + 1]->TOA == NULL || flight_list[i + 1]->TOD == NULL)	//if the arrival and departure pointers of this or the next flight are NULL
			{
				return -1;
			}

			else if (isAfter(flight_list[i]->TOA, flight_list[i + 1]->TOD))		//if the arrival time of the current flight is after the departure time of the next flight
			{
				return -1;
			}

			else if (flight_list[i]->cost < 0)	//if the flight has a negative cost
			{
				return -1;
			}

			else		//if no errors are detected, add the cost of current flight to total cost
			{
				total += flight_list[i]->cost;
			}
		}
	}

	total += flight_list[size - 1]->cost;		//add the final flights' cost to the total cost

	return total;		//return the total cost
}
