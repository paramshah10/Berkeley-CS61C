CFLAGS?=-Wall -Wno-unused-result -march=haswell -std=c99 -fopenmp -O3

benchmark : benchmark.o network.o layers.o volume.o
	gcc $(CFLAGS) -o benchmark benchmark.o network.o layers.o volume.o -lm

baseline : benchmark.o network_baseline.o layers_baseline.o volume_baseline.o
	gcc $(CFLAGS) -o benchmark_baseline benchmark.o network_baseline.o layers_baseline.o volume_baseline.o -lm

test : benchmark
	./benchmark benchmark

compare : benchmark baseline
	./benchmark benchmark
	./benchmark_baseline benchmark

benchmark.o : benchmark.c network.h layers.h volume.h
	gcc $(CFLAGS) -c benchmark.c

network.o : network.c network.h layers.h volume.h
	gcc $(CFLAGS) -c network.c

network_baseline.o : network_baseline.c network.h layers.h volume.h
	gcc $(CFLAGS) -c network_baseline.c

layers.o : layers.c layers.h volume.h
	gcc $(CFLAGS) -c layers.c

layers_baseline.o: layers_baseline.c layers.h volume.h
	gcc $(CFLAGS) -c layers_baseline.c

volume.o : volume.c volume.h
	gcc $(CFLAGS) -c volume.c

volume_baseline.o : volume_baseline.c volume.h
	gcc $(CFLAGS) -c volume_baseline.c

clean:
	rm -f *.o
	rm -f benchmark
	rm -f benchmark_baseline

.PHONY : clean
