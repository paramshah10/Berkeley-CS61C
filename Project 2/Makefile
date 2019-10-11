CC=gcc
FLAGS=-Wall -g -std=c99
LinkingInfo=-L/home/ff/cs61c/bin/static -l61Ccc-notcgen
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
DEPS=$(wildcard *.h)

61ccc : $(OBJS)
	$(CC) $(FLAGS) -o 61ccc $(OBJS) $(LinkingInfo)

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c $<

part1: 61ccc
	python3 run-tests.py --section=1

part2: 61ccc
	python3 run-tests.py --section=2

part3: 61ccc
	python3 run-tests.py --section=3

part4: 61ccc
	python3 run-tests.py --section=4

part5: 61ccc
	python3 run-tests.py --section=5

part6: 61ccc
	python3 run-tests.py --section=6

integration: 61ccc
	python3 run-tests.py --section=7

run-student-tests: 61ccc
	python3 run-tests.py --section=0

run-all-tests: part1 part2 part3 part4 part5 part6 integration run-student-tests

clean:
	rm $(OBJS) 61ccc

.PHONY: clean part1 part2 part3 part4 part5 part6 run-student-tests run-all-tests
