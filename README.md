# basic_c_scheduler
Initial attempt at a simple C scheduler that allows task creation and context shifting.

Note - currently, this repo builds the scheduler (OS) and then a main.c project that calls/tests it.
It will be updated to build the OS as a static library (libos.a) and will not include the main.c file.

## building

Create the output directory:
```
$ mkdir build
```

Run the Makefile:
```
$ make
```

Output files (.o, etc., are moved to the previously created "output" directory.

## running

To execute the test application:
```
./output/os.out
```

