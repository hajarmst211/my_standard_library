SRC = src
OBJ = object_files
TESTS = tests

string_library: $(SRC)/string_library.c 
	gcc -c $(SRC)/string_library.c -o $(OBJ)/string_library.o

string_test: $(TESTS)/test.c $(OBJ)/*.o
	gcc $(TESTS)/string_test.c $(OBJ)/*.o -Iheader -o $(TESTS)/string_test && $(TESTS)/string_test

io_library: $(SRC)/io_library.c
	gcc -c $(SRC)/io_library.c -o $(OBJ)/io_library.o

io_test: $(TESTS)/io_test.c $(OBJ)/*.o
	gcc $(TESTS)/io_test.c $(OBJ)/*.o -Iheader -o $(TESTS)/io_test && $(TESTS)/io_test