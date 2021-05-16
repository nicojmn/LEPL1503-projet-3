CC = gcc
CFLAGS = -Wall -Werror -g -std=gnu99
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders


# kmeans command link all source files and headers with main.c file
# and compile them in a file named kmeans
kmeans: main.c  \
		src/distance.o src/kMeans.o src/generateStartingCentroids.o src/buffer.o\
		src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
		$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

# This command take a C source file and compile it to return a .o file
%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

# This command clean the project by deleting output file
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

# Run benchmark test and create a matplotlib graph with execution time
performances: clean kmeans
	/bin/sh ./tests_files/test_performances/testPerformances.sh

# Run unittests and compare solution with python code
tests: clean kmeans test
	./test


## Performs valgrind (memory check) test with -q and without -q
valgrind : clean kmeans
	/bin/sh ./tests_files/bash/valgrindTests.sh


## Performs helgrind (safe threads check) test with -q and without -q
helgrind: clean kmeans
	/bin/sh ./tests_files/bash/helgrindTests.sh

# Performs a valgrind check on the unit tests
valgrindForTests : clean kmeans test
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./test -v

.PHONY: kmeans clean tests valgrind helgrind performances valgrindForTests
