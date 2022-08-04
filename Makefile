CC=nvc
CFLAGS?=-Wall -tp=native -c99 -mp -Minfo=all -acc -g #-O3 -Mnovect
#-Wno-unused-result  

benchmark : benchmark.o network.o layers.o volume.o
	$(CC) $(CFLAGS) -o benchmark benchmark.o network.o layers.o volume.o -lm

baseline : benchmark.o network_baseline.o layers_baseline.o volume_baseline.o
	$(CC) $(CFLAGS) -o benchmark_baseline benchmark.o network_baseline.o layers_baseline.o volume_baseline.o -lm

compare : benchmark baseline
	./benchmark benchmark
	./benchmark_baseline benchmark

benchmark.o : benchmark.c network.h layers.h volume.h
	$(CC) $(CFLAGS) -c benchmark.c

network.o : network.c network.h layers.h volume.h
	$(CC) $(CFLAGS) -c network.c

network_baseline.o : network_baseline.c network.h layers.h volume.h
	$(CC) $(CFLAGS) -c network_baseline.c

layers.o : layers.c layers.h volume.h
	$(CC) $(CFLAGS) -c layers.c

layers_baseline.o: layers_baseline.c layers.h volume.h
	$(CC) $(CFLAGS) -c layers_baseline.c

volume.o : volume.c volume.h
	$(CC) $(CFLAGS) -c volume.c

volume_baseline.o : volume_baseline.c volume.h
	$(CC) $(CFLAGS) -c volume_baseline.c

clean:
	rm -f *.o
	rm -f benchmark
	rm -f benchmark_baseline

.PHONY : clean
