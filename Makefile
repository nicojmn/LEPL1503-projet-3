CC = gcc
CFLAGS = -Wall -Werror -g -std=gnu99
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders

kmeans: main.c  \
		src/distance.o src/kMeans.o src/generateStartingCentroids.o src/buffer.o\
		src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
		$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

clean:
	rm -f kmeans
	rm -f test
	rm -f *.o
	rm -f src/*.o
	rm -f tests_files/src/*.o

## /! WARNING : this command can't be used alone !\ ##
test: tests_files/src/tests.c \
	   src/distance.o src/kMeans.o src/generateStartingCentroids.o src/readBinaryFile.o \
       src/writeOutputFile.o src/manageArgs.o src/manageHeap.o src/buffer.o\
	   tests_files/src/distanceTests.o tests_files/src/assignVectorTests.o \
	   tests_files/src/distortionTests.o tests_files/src/generateCentroidsTests.o \
	   tests_files/src/kMeansTests.o tests_files/src/writeOutputFileTests.o \
	   tests_files/src/readBinaryFileTests.o tests_files/src/updateCentroidsTests.o \
	   tests_files/src/compareWithPythonTests.o
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

performances: clean kmeans
	/bin/sh ./tests_files/test_performances/testPerformances.sh

## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
tests: clean kmeans test
	./test

## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
## Performs valgrind (memory check) test with -q and without -q
valgrind : clean kmeans
	/bin/sh ./tests_files/bash/valgrindTests.sh

## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
## Performs helgrind (safe threads check) test with -q and without -q
helgrind: clean kmeans
	/bin/sh ./tests_files/bash/helgrindTests.sh

valgrindForTests : clean kmeans test
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./test -v

.PHONY: clean tests kmeans valgrind performances valgrindTests
