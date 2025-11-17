SRC = src
OBJ = object_files
TESTS = tests

string_library: $(SRC)/string_library.c 
	gcc -c $(SRC)/string_library.c -o $(OBJ)/string_library.o

string_test: $(TESTS)/string_test.c $(OBJ)/*.o
	gcc $(TESTS)/string_test.c $(OBJ)/*.o -Iheader -o $(TESTS)/string_test && $(TESTS)/string_test

io_library: $(SRC)/io_library.c
	gcc -c $(SRC)/io_library.c -o $(OBJ)/io_library.o

io_test: $(TESTS)/io_test.c $(OBJ)/*.o
	gcc $(TESTS)/io_test.c $(OBJ)/*.o -Iheader -o $(TESTS)/io_test && $(TESTS)/io_test

memory_allocation_library: $(SRC)/memory_allocation_library.c
	gcc -c $(SRC)/memory_allocation_library.c -o $(OBJ)/memory_allocation_library.o

memory_test: $(TESTS)/memory_library_test.c $(OBJ)/*.o
	gcc $(TESTS)/memory_library_test.c $(OBJ)/*.o -Iheader -o $(TESTS)/memory_library_test && $(TESTS)/memory_library_test
