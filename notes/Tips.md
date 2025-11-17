# system files
- Always **close file descriptors** to avoid leaks
- Use **`ssize_t` for read/write results**.
- Return **error codes**, not strings.
- Provide both **text and binary modes**.
- Add **utility functions**: check existence, copy, move, delete.
- Add **documentation/comments** for every function.
- Optionally, implement a **buffered read/write** to handle large files efficiently.

# Interesting Discoveries
1. `Assert(condition)`: 
	- makes sure the condition is always verified
	-  If it is not, the program stops immediately and prints a message showing:
		• the failed expression  
		• the file  
		• the line number
	