CFLAGS?=-Wall -march=haswell -std=c99 -fopenmp -Minfo=all -O3

benchmark : benchmark.o network.o layers.o volume.o
	nvc $(CFLAGS) -o benchmark benchmark.o network.o layers.o volume.o -lm

baseline : benchmark.o network_baseline.o layers_baseline.o volume_baseline.o
	nvc $(CFLAGS) -o benchmark_baseline benchmark.o network_baseline.o layers_baseline.o volume_baseline.o -lm

compare : benchmark baseline
	./benchmark benchmark
	./benchmark_baseline benchmark

benchmark.o : benchmark.c network.h layers.h volume.h
	nvc $(CFLAGS) -c benchmark.c

network.o : network.c network.h layers.h volume.h
	nvc $(CFLAGS) -c network.c

network_baseline.o : network_baseline.c network.h layers.h volume.h
	nvc $(CFLAGS) -c network_baseline.c

layers.o : layers.c layers.h volume.h
	nvc $(CFLAGS) -c layers.c

layers_baseline.o: layers_baseline.c layers.h volume.h
	nvc $(CFLAGS) -c layers_baseline.c

volume.o : volume.c volume.h
	nvc $(CFLAGS) -c volume.c

volume_baseline.o : volume_baseline.c volume.h
	nvc $(CFLAGS) -c volume_baseline.c

clean:
	rm -f *.o
	rm -f benchmark
	rm -f benchmark_baseline

.PHONY : clean
