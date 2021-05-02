CC = gcc -std=gnu99
CFLAGS = -Wall -Werror -g
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders
VALGRIND_MEM_FULL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
VALGRIND_MEM_MED = valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no

# add your other object files needed to compile your program here. !! The ordering is important !!
# if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
kmeans: main.c  \
		src/distance.o src/kMeans.o src/generateStartingCentroids.o \
		src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
		$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

clean:
	rm -f kmeans
	rm -f tests
	rm -f *.o
	rm -f src/*.o
	rm -f tests_files/src/*.o

tests: tests_files/src/tests.c \
	   src/distance.o src/kMeans.o src/generateStartingCentroids.o src/readBinaryFile.o \
	   src/writeOutputFile.o src/manageArgs.o src/manageHeap.o \
	   tests_files/src/distanceTests.o tests_files/src/assignVectorTests.o \
	   tests_files/src/distortionTests.o tests_files/src/generateCentroidsTests.o \
	   tests_files/src/kMeansTests.o tests_files/src/writeOutputFileTests.o \
	   tests_files/src/readBinaryFileTests.o tests_files/src/updateCentroidsTests.o
## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	./tests

valgrind : main.c  src/distance.o src/kMeans.o src/generateStartingCentroids.o src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./valgrind  -k 4 -p 6 -n 1 -d manhattan -f output_csv/kmeans.csv  input_binary/ex3.bin
	rm -f valgrindMain

helgrind: main.c  src/distance.o src/kMeans.o src/generateStartingCentroids.o src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	valgrind --tool=helgrind ./helgrind -k 2 -p 3 -n 2 -d euclidean -f output_csv/kmeans.csv input_binary/ex3.bin
	rm -f helgrind

.PHONY: clean tests kmeans valgrind