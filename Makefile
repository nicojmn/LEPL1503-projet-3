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
		# this will run the following command: gcc -Wall -Werror -g -o kmeans other_object_filespresent_above.o ... -lcunit -lpthread
		$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c                  # if for example you want to compute example.c this will create an object file called example.o in the same directory as example.c. Don't forget to clean it in your "make clean"
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
	   tests_files/src/kMeansTests.o tests_files/src/outputCsvTests.o \
	   tests_files/src/readBinaryFileTests.o tests_files/src/updateCentroidsTests.o
## -----------------------------------/!\--------------------------------
## WARNING : this command is used by Jenkins
## -----------------------------------/!\--------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)
	./tests

valgrind:
## ----------------------------------------------------------------------
## Perform a valgrind test on a selected file
## level : med or full (the level of inspection, medium or full)
## log : yes or no (if the result should be logged in tests_files/valgrind-log)
## filePath : the .c path to file to perform test
## example : make valgrind level=full log=yes file=tests_files/tests_files.c
## ----------------------------------------------------------------------
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) $(filePath) -o tests/$(notdir $(basename $(filePath))).o $(LIBS)
	chmod 777 ./tests/$(notdir $(basename $(filePath))).o
ifeq ($(level), full)
ifeq ($(log), yes)
	$(VALGRIND_MEM_FULL) --log-file=tests/valgrind-log/$(notdir $(basename $(filePath))).txt tests/$(notdir $(basename $(filePath))).o $(LIBS)
else
	$(VALGRIND_MEM_FULL) tests/$(notdir $(basename $(filePath))).o $(LIBS)
endif
endif
ifeq ($(level), med)
ifeq ($(log),yes)
	$(VALGRIND_MEM_MED) --log-file=tests/valgrind-log/$(notdir $(basename $(filePath))).txt tests/$(notdir $(basename $(filePath))).o $(LIBS)
else
	$(VALGRIND_MEM_MED) tests/$(notdir $(basename $(filePath))).o $(LIBS)
endif
endif
	rm -f tests/$(notdir $(basename $(filePath))).o

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