#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timeHM.h"
#include "flights.h"

#define MAX_NAME_LEN 128
#define MAX_LINE_LEN 256

void stripNewLine(char* line) {
  while (strlen (line) && (line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\r')) {
    line[strlen(line) - 1] = '\0';
  }
}

void printCompleteRoute(char* route, timeHM_t* end, int cost) {
  printf("Route %s will be completed by ",route);
  printTime(end);
  printf(" and costs $%d\n", cost);
}

/*
 *  Given a file with routes and a flight system, parses the file and determine (and print) the earliest time each route can be completed.
 *  Lines of bad form are skipped while new lines are ignored.
 */
void calcRouteTimes(flightSys_t* s, FILE* routes) {
  char* newRoutePrefix = "ROUTE: ";
  size_t prefixLen     = strlen(newRoutePrefix);
  char line[MAX_LINE_LEN];
  timeHM_t now;
  char route[MAX_LINE_LEN];
  char timeBuf[MAX_LINE_LEN];
  char airportBuf[MAX_LINE_LEN];
  airport_t* curAirport = NULL;
  int curCost   = 0;
  int totalCost = 0;

  /*
   *  This while loop parses the file line by line and calculate the route times as it goes.
   *  If a new route line is found, the current route (if it exists) would be done and the result is printed.
   *  A current route exists if curAirport is not null.
   *
   *  curAirport tells us where we are on the current route.
   *
   *  now tells us the current time (the earliest time we can reach the curAirport on the current route).
   */
  while (fgets(line, MAX_LINE_LEN,routes)) {
    stripNewLine(line);

    if (!strlen(line)) {
      continue;                     // ignore line if it's empty
    } else if (strncmp(line,newRoutePrefix,
                       prefixLen) == 0) {                      // if beginning of line starts with "ROUTE: ", we are calculating for a new route
      if (curAirport) {
        printCompleteRoute(route,&now, totalCost);                    // if curAirport is not NULL, we are done with the previous route so print the result

      }
      curAirport = NULL;
      totalCost  = 0;
      if (3 != sscanf(line + prefixLen,"%s %s %s",route,airportBuf,timeBuf)  // parse rest of new route line into route name, airport name, and start time
          || !stringToTime(timeBuf,&now)       // ensure time is valid
          || !(curAirport = getAirport(s,airportBuf))) {       // ensure airport exists and sets curAirport to the starting airport
        printf("Skipping line: %s\n",line);
        continue;
      }
    } else if (curAirport) {
      /*
       *  This is the case when we are in the middle of calculating for a route,
       *  and the line should just be next airport we have to get to.
       *  Here, we use getNextFlight to determine the flight to take to the next airport.
       *  If there are no possible flights, the route cannot be completed.
       */
      airport_t* next = getAirport(s,line);
      if (!next) {
        printf("Skipping line: %s\n",line);
        continue;
      }
      timeHM_t depart;
      timeHM_t arrival;
      if (!getNextFlight(curAirport,next,&now,&depart,&arrival,&curCost)) {
        curAirport = NULL;
        totalCost  = 0;
        printf("Route %s cannot be completed\n",route);
        continue;
      }
      now        = arrival;
      curAirport = next;
      totalCost += curCost;
    }
  }
  if (curAirport) {
    printCompleteRoute(route,&now,totalCost);
  }
}

/*
 *  Given a flight system and a file of airport names, each on a line,
 *  add the airports to the flight system.
 */
void parseAirports(flightSys_t* s, FILE* airportFile) {
  char name[MAX_NAME_LEN];
  while (fgets(name, MAX_NAME_LEN, airportFile)) {
    stripNewLine(name);
    addAirport(s,name);
  }
}

/*
 *  Given a flight system with airports, and a file of schedules for those airports,
 *  add flight times to the system.
 */
void parseSchedule(flightSys_t* s, FILE* schedule) {
  char* newAirportPrefix = "AIRPORT: ";
  size_t prefixLen       = strlen(newAirportPrefix);
  airport_t* curAirport  = NULL;

  /*
   *  curAirport is the airport we are currently adding a schedule for.
   *  In other words, it is the source airport.
   *
   *  The while loop parses the file line by line and sets a new curAirport when a line that starts with "STATION: " is found.
   *  It'll also echo the schedule of the previous airport.
   *  Otherwise, it treats the current line as a new entry in the schedule of the curAirport and calls addFlight.
   */
  char line[MAX_LINE_LEN];
  while (fgets(line, MAX_LINE_LEN, schedule)) {
    if (!strcmp(line,"\n") || !strcmp(line,"\r\n")) {
      continue;
    } else if (strncmp(line,newAirportPrefix,prefixLen) == 0) {
      if (curAirport) {
        printSchedule(curAirport);              // done with previous schedule so print it

      }
      stripNewLine(line);
      char* srcName = line + prefixLen;
      curAirport = getAirport(s,srcName);
      if (curAirport) {
        printf("Adding schedule for airport %s\n",srcName);
      } else {
        printf("Cannot find airport %s\n",srcName);
      }
    } else if (curAirport) {
      char dstName[MAX_LINE_LEN];
      char departureStr[MAX_LINE_LEN];
      char arrivalStr[MAX_LINE_LEN];
      char priceStr[MAX_LINE_LEN];
      if (4 != sscanf(line,"%s %s %s $%s",dstName,departureStr,arrivalStr, priceStr)) { // parses the line as destination airport name, departure time, arrival time, and price
        printf("Skipping line: %s\n",line);
        continue;
      }
      airport_t* dst = getAirport(s,dstName);
      if (dst == NULL) {
        printf("Cannot find airport %s\n",dstName);
        continue;
      }

      timeHM_t arrival;
      timeHM_t departure;
      int cost;
      char* endptr;
      cost = (int)strtol(priceStr,&endptr,10);
      if (!stringToTime(arrivalStr, &arrival) || !stringToTime(departureStr, &departure) || *endptr) {
        printf("Skipping line: %s\n",line);
        continue;
      }
      addFlight(curAirport,dst,&departure,&arrival, cost);
    }
  }
  if (curAirport) {
    printSchedule(curAirport);
  }
}

/*
 *  Calls parseAirports, parseSchedules, and calcRouteTimes if the required files exists.
 */
void timeRoutes(char* airports, char* schedules, char* routes) {
  FILE* airportFile, * scheduleFile, * routeFile;
  char* read = "r";
  airportFile = fopen(airports,read);
  if (!airportFile) {
    fprintf(stderr,"Cannot open file with list of airport names.\n");
    exit(EXIT_FAILURE);
  }
  flightSys_t* s = createSystem();
  if (s == NULL) {
    printf("createSystem unimplemented\n");
    return;
  }
  printf("***Parse and echo airports***\n");
  parseAirports(s,airportFile);
  fclose(airportFile);
  printAirports(s);

  scheduleFile = fopen(schedules,read);
  if (!scheduleFile) {
    fprintf(stderr,"Cannot open file with schedule.\n");
    exit(EXIT_FAILURE);
  }
  printf("\n***Parse and echo schedules***\n");
  parseSchedule(s,scheduleFile);
  fclose(scheduleFile);

  routeFile = fopen(routes,read);
  if (!routeFile) {
    fprintf(stderr,"Cannot open file with routes.\n");
    exit(EXIT_FAILURE);
  }
  printf("\n***Parse and calculate route times***\n");
  calcRouteTimes(s,routeFile);
  fclose(routeFile);
  deleteSystem(s);
}

void validateFlightPathTestStudent() {
  printf("validateFlightPath test\n");
  char* temp[]   = { "", "" };
  int total_cost = validateFlightPath(NULL, temp, 10);
  printf("NULL check total cost %d\n", total_cost);

  flightSys_t* fs = createSystem();
  addAirport(fs, "SFO");
  addAirport(fs, "SEA");
  airport_t* SFO = getAirport(fs, "SFO"), * SEA = getAirport(fs, "SEA");
  flight_t* f1 = createFlight(SFO, &(timeHM_t) {.hours = 12, .minutes = 0 }, &(timeHM_t) {.hours = 13,
                                                                                          .minutes = 0 }, 200),
          * f2 = createFlight(SEA, &(timeHM_t) {.hours = 13, .minutes = 0 }, &(timeHM_t) {.hours = 14,
                                                                                          .minutes = 0 }, 300);
  char* temp1[]   = { "SFO", "SEA" };
  flight_t* fl1[] = { f1, f2 };
  total_cost = validateFlightPath(fl1, temp1, 2);
  printf("ACTUAL check total cost %d\n", total_cost);

  deleteFlight(f1);
  deleteFlight(f2);
  deleteSystem(fs);
}

/*
 *   Function to assist with exit for format errors in config file.
 */
void configError(char* errorMsg) {
  fprintf (stderr, "Error in config file: %s\n", errorMsg);
  exit(EXIT_FAILURE);
}

/*
 *   Parse the config file to get the next test to run.
 *   It reads each line until it encounters a line without just whitespace.
 *   Then it stores the values for each filename in the filenames**, which
 *   is presumed to always be of size at least 4 and that entry 0 will hold
 *   the location of the originally allocated buffer so it can be freed.
 *
 *   Returns a nonzero value if a new test is found and zero if no line
 *   with content remains.
 */
int parseConfigLine(FILE* configFile, char** filenames) {
  // List of characters to split file names (aka whitespace)
  const char delimit[] = " \t\r\n\v\f";

  size_t readAmount  = 0;
  int found          = 0;
  size_t requestSize = 0;
  char* line;
  char* airports;
  char* schedules;
  char* routes;
  // Search until contents are found, a bad input line is found, or the file
  // has run out of contents. Any path that does not result in a series of
  // working filenames will need the free an allocated buffer.
  while (!found) {
    line       = NULL;
    readAmount = getline (&line, &requestSize, configFile);
    // No more lines to read from the file
    if (readAmount == -1) {
      free (line);
      return 0;
    }
    // Line needs to be parsed
    airports = strtok (line, delimit);
    // If line is null its an empty whitespace line
    if (airports == NULL) {
      free (line);
      continue;
    } else {
      schedules = strtok (NULL, delimit);
      routes    = strtok (NULL, delimit);
      // More than 3 files are specified on a line
      if (strtok (NULL, delimit) != NULL) {
        configError ("Too many files on a line");
        // Line consists of fewer than 3 lines
      } else if (schedules == NULL || routes == NULL) {
        configError ("Too few files on a line");
      } else {
        filenames[0] = line;
        filenames[1] = airports;
        filenames[2] = schedules;
        filenames[3] = routes;
        found        = 1;
      }
    }
  }
  return found;
}


int main(int argc, char* args[]) {
  FILE* configFile;
  char* read = "r";
  if (argc != 2) {
    printf("Usage: <config file>\n");
    printf(
      "Given flight schedules and a route with a starting time, this program will determine when the route will be completed.\n");
    printf("This configuration should be able to support tests with many different flight systems.\n");
    printf("Each line of the config file should be <file of airport names>, <file of schedules>, <file of routes>.\n");
    printf("\t<file of airport names> should contain a list of airport names, one on each line.\n");
    printf("\t<file of schedules> should contain a list of schedules. \n");
    printf("\t\t\"AIRPORT: <airport name>\" marks the beginning of a schedule for that airport.\n");
    printf(
      "\t\tSubsequent lines contain the destination airport, departure time, and arrival time separated by spaces\n");
    printf("\t<file of routes> should contain a list of routes. \n");
    printf(
      "\t\t\"ROUTE: <route name> <starting airport> <begin time>\" marks the beginning of a plan starting at the specified airport and time.\n");
    printf("\t\tSubsequent lines contain the airports in the route, one on each line, in order\n");
    printf(
      "Each line in the config file will create a separate flight system and will assume no dependencies with previous lines.\n");
    return 0;
  }
  configFile = fopen(args[1],read);
  if (!configFile) {
    fprintf(stderr,"Cannot open file with list of tests");
    exit(EXIT_FAILURE);
  }
  char* files[4];
  while (parseConfigLine (configFile, files)) {
    printf ("\n");
    printf ("** RUNNING NEW TEST **");
    printf ("\n");
    timeRoutes(files[1],files[2],files[3]);
    printf("\n");
    validateFlightPathTestStudent();
    printf("\n");
    free (files[0]);
  }
  fclose(configFile);
  return 0;
}

