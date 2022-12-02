**Project Berkeley** : [https://inst.eecs.berkeley.edu/~cs61c/sp19/projects/proj4/](https://inst.eecs.berkeley.edu/~cs61c/sp19/projects/proj4/)  
**Github Berkeley** :  [https://github.com/61c-teach/sp19-proj4-starter](https://github.com/61c-teach/sp19-proj4-starter)

Makefile για nvc compiler : [https://github.com/olia92/cs61c/blob/main/Makefile](https://github.com/olia92/cs61c/blob/main/Makefile)

#### Εκτέλεση με nvc
```
make clean
make benchmark
./benchmark benchmark

```
αποτέλεσμα:

```
RUNNING BENCHMARK ON 1200 PICTURES...
Making network...
Loading batches...
Loading input batch 0...
Segmentation fault (core dumped)

```


# Valgrind

```
valgrind --leak-check=full --show-leak-kinds=all ./benchmark benchmark
```

## GCC Compiler

```
$valgrind --leak-check=full --show-leak-kinds=all ./benchmark benchmark
==21962== Memcheck, a memory error detector
==21962== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==21962== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==21962== Command: ./benchmark benchmark
==21962== 
RUNNING BENCHMARK ON 1200 PICTURES...
Making network...
Loading batches...
Loading input batch 0...
Running classification...
78.250000% accuracy
659203153 microseconds
==21962== 
==21962== HEAP SUMMARY:
==21962==     in use at exit: 0 bytes in 0 blocks
==21962==   total heap usage: 21,439 allocs, 21,439 frees, 247,283,464 bytes allocated
==21962== 
==21962== All heap blocks were freed -- no leaks are possible
==21962== 
==21962== For lists of detected and suppressed errors, rerun with: -s
==21962== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
---

## NVC Compiler

```
$ valgrind --leak-check=full --show-leak-kinds=all ./benchmark benchmark
==21667== Memcheck, a memory error detector
==21667== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==21667== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==21667== Command: ./benchmark benchmark
==21667== 
RUNNING BENCHMARK ON 1200 PICTURES...
Making network...
Loading batches...
Loading input batch 0...
==21667== Invalid write of size 8
==21667==    at 0x404C52: volume_set (volume.c:23)
==21667==    by 0x401ACC: run_classification (benchmark.c:91)
==21667==    by 0x402C8C: main (benchmark.c:223)
==21667==  Address 0x62b9a30 is 0 bytes after a block of size 24,576 alloc'd
==21667==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==21667==    by 0x404CC9: make_volume (volume.c:28)
==21667==    by 0x401A67: run_classification (benchmark.c:82)
==21667==    by 0x402C8C: main (benchmark.c:223)
==21667== 
--21667-- VALGRIND INTERNAL ERROR: Valgrind received a signal 11 (SIGSEGV) - exiting
--21667-- si_code=128;  Faulting address: 0x0;  sp: 0x1002ca9e10

valgrind: the 'impossible' happened:
   Killed by fatal signal

host stacktrace:
==21667==    at 0x5804F830: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/memcheck-amd64-linux)
==21667==    by 0x58051B46: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/memcheck-amd64-linux)
==21667==    by 0x58005BF7: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/memcheck-amd64-linux)
==21667==    by 0x580A7204: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/memcheck-amd64-linux)
==21667==    by 0x580F5FD4: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/memcheck-amd64-linux)

sched status:
  running_tid=1

Thread 1: status = VgTs_Runnable (lwpid 21667)
==21667==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==21667==    by 0x404CA5: make_volume (volume.c:27)
==21667==    by 0x401A67: run_classification (benchmark.c:82)
==21667==    by 0x402C8C: main (benchmark.c:223)
client stack range: [0x1FFEFFC000 0x1FFEFFFFFF] client SP: 0x1FFEFFD610
valgrind stack range: [0x1002BAA000 0x1002CA9FFF] top usage: 18696 of 1048576
```