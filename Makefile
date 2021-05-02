CC = gcc -std=gnu99
CFLAGS = -Wall -Werror -g
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders
VALGRIND_MEM_FULL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
VALGRIND_MEM_MED = valgrind --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no
RUN_FILE = main.c  src/distance.o src/kMeans.o src/generateStartingCentroids.o src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
TESTS_FILE = tests-file/src/tests.c tests-file/src/distanceTests.o src/distance.o tests-file/src/distortionTests.o src/kMeans.o tests-file/src/kMeansTests.o tests-file/src/assignVectorTests.o tests-file/src/generateCentroidsTests.o src/readBinaryFile.o src/generateStartingCentroids.o tests-file/src/outputCsvTests.o src/writeOutputFile.o tests-file/src/readBinaryFileTests.o tests-file/src/updateCentroidsTests.o

kmeans: $(RUN_FILE)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(RUN_FILE)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	./kmeans -k 4 -p 9 -d euclidean input_binary/ex3.bin -f output_csv/ex3.csv
%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

clean:
	rm -f kmeans
	rm -f tests
	rm -f *.o
	rm -f src/*.o
	rm -f tests-file/src/*.o

tests: $(TESTS_FILE)
## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	./tests

valgrindMain : main.c  src/distance.o src/kMeans.o src/generateStartingCentroids.o src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./valgrindMain  -k 4 -p 6 -n 1 -d manhattan -f output_csv/kmeans.csv  input_binary/ex3.bin
	rm -f valgrindMain

helgrind: main.c  src/distance.o src/kMeans.o src/generateStartingCentroids.o src/readBinaryFile.o src/writeOutputFile.o src/manageArgs.o src/manageHeap.o
## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	valgrind --tool=helgrind ./helgrind -k 2 -p 3 -n 2 -d euclidean -f output_csv/kmeans.csv input_binary/ex3.bin
	rm -f helgrind




# a .PHONY target forces make to execute the command even if the target already exists
.PHONY: clean tests kmeans valgrindMain