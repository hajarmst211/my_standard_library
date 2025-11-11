SRC="src"
OBJ="object_files"
TESTS="tests"

string_library: $(SRC)/string_library.c 
	gcc -c $(SRC)/string_library.c -o $(OBJ)/string_library.o

string_test: test/test.c $(OBJ)/*.o
	gcc $(TESTS)/string_test.c $(OBJ)/*.o -Iheader -o $(TESTS)/string_test && $(TESTS)/string_test
