$ make benchmark 
nvc -Wall -Minfo=opt -mp -march=native -g -O0  -c benchmark.c
nvc -Wall -Minfo=opt -mp -march=native -g -O0  -c network.c
nvc -Wall -Minfo=opt -mp -march=native -g -O0  -c layers.c
conv_forward:
    109, FMA (fused multiply-add) instruction(s) generated
fc_forward:
    283, FMA (fused multiply-add) instruction(s) generated
nvc -Wall -Minfo=opt -mp -march=native -g -O0  -c volume.c
nvc -Wall -Minfo=opt -mp -march=native -g -O0  -o benchmark benchmark.o network.o layers.o volume.o -lm
olia@asus:~/Documents/Programming_2021/Berckeley/sp19-proj4-starter-nvc0$ valgrind --leak-check=full --show-leak-kinds=all ./benchmark benchmark
```

```
==13030== Memcheck, a memory error detector
==13030== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==13030== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==13030== Command: ./benchmark benchmark
==13030== 
RUNNING BENCHMARK ON 1200 PICTURES...
Making network...
Loading batches...
Loading input batch 0...
Running classification...
78.250000% accuracy
1624405582 microseconds
==13030== 
==13030== HEAP SUMMARY:
==13030==     in use at exit: 0 bytes in 0 blocks
==13030==   total heap usage: 21,439 allocs, 21,439 frees, 247,283,464 bytes allocated
==13030== 
==13030== All heap blocks were freed -- no leaks are possible
==13030== 
==13030== For lists of detected and suppressed errors, rerun with: -s
==13030== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```