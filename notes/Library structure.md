### Levels of compilation

| extentsion | who does it  | compilation flag | function                                                                                                           |
| ---------- | ------------ | ---------------- | ------------------------------------------------------------------------------------------------------------------ |
| .c         | preprocessor | -E               | - handles the `#include ` `#include`....<br>(their code is imported at the top of your code)<br>- removes comments |
| .s         | compiler     | -S               | translates c to assembly                                                                                           |
| .o         | assmbler     | -c               | trnaslates assembly to object file                                                                                 |
| executable | linker       |                  | brings together object files to create executable                                                                  |

##### header files and use:
- In the .h file we only write the name of the functions, the includes, the definitions....No actual code
- In the files where we want to use the function/definitions/includes that we mentioned in the .h file, we should put at the top of that c file: `#include "header_name.h"` or `#include "path/to/header_name.h"`


---

# Makefile Basics

A Makefile automates compiling and linking your code. It has **targets**, **dependencies**, and **commands**.

```makefile
target: dependencies
[TAB] command
```

- **target**: what you want to build (object file or executable)
- **dependencies**: files that trigger a rebuild if changed
- **command**: shell command to make the target (TAB required)

---

##  Example

```makefile
SRC="src"
OBJ="object_files"
TESTS="tests"

string_library: $(SRC)/string_library.c 
	gcc -c $(SRC)/string_library.c -o $(OBJ)/string_library.o

string_test: test/test.c $(OBJ)/*.o
	gcc $(TESTS)/string_test.c $(OBJ)/*.o -Iheader -o $(TESTS)/string_test && $(TESTS)/string_test
```

- `string_library` → compiles `string_library.c` into an object file.
- `string_test` → links object files with `string_test.c` and runs the test.
- Variables (`SRC`, `OBJ`, `TESTS`) make paths easier to manage.
    
---
## Key Tips

- Use **object files** (`.o`) to avoid recompiling everything.
- Always use a **TAB** before commands.
- `make target` builds that target; `make` alone builds the first target.
