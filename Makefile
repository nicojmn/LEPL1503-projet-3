CC = gcc
CFLAGS = -Wall -Werror -g
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders
VALGRIND_MEM = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

kmeans: main.c src/distance.o     # add your other object files needed to compile your program here. !! The ordering is important !! if file_a.o depends on file_b.o, file_a.o must be placed BEFORE file_b.o in the list !
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)    # this will run the following command: gcc -Wall -Werror -g -o kmeans src/distance.o other_object_filespresent_above.o ... -lcunit -lpthread

%.o: %.c                  # if for example you want to compute example.c this will create an object file called example.o in the same directory as example.c. Don't forget to clean it in your "make clean"
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

clean:
	rm -f src/*.o
	rm -f kmeans
	rm -f *.o
	rm -f tests/*.o

tests: tests/tests.c
	$(CC) tests/tests.c -o tests/tests.o $(LIBS) $(CFLAGS)
	./tests/tests.o

valgrind-mem: tests/tests.c # add ALL files which use malloc
	make tests
	$(VALGRIND_MEM) ./tests/tests.o

valgrind-mem-out: tests/tests.c # same as valgrind-mem but write log in tests/valgrind-log
	make tests
	$(VALGRIND_MEM) --log-file=./tests/valgrind-log/tests.txt ./tests/tests.o



# a .PHONY target forces make to execute the command even if the target already exists
.PHONY: clean tests