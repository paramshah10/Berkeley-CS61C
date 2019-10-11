CC = gcc 
CFLAGS = -Wall -g -std=c99
DEF_ARGS = integration_config

RouteTime: timeHM.o flights.o RouteTime.o
	$(CC) -o $@ timeHM.o flights.o RouteTime.o

run:	RouteTime
	./RouteTime $(DEF_ARGS)

flights-memcheck:	RouteTime
	valgrind --tool=memcheck --leak-check=full --dsymutil=yes --track-origins=yes ./RouteTime $(DEF_ARGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf *.o RouteTime RouteTime.dSYM FlightTest
