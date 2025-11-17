# To do 
- \_Generate for printf
- learn to use errno
---
# To do in file library:
- **Check if a file exists** – A function to verify whether a file is present before reading or writing.
- **Get file size** – Retrieve the size of a file in bytes without reading its contents.
- **Delete a file** – Remove a file from the filesystem.
- **Copy a file** – Duplicate the contents of one file into another.
- **Read file line by line** – Useful for processing logs, CSVs, or text files incrementally.
- **Modify file permissions** – Change the read/write/execute permissions of a file.
- **Read/write binary files** – Functions to handle raw bytes or serialized data safely.
- **Move/rename a file** – Change the location or name of a file in the filesystem.
- **Check if a path is a directory or a file** – Useful for differentiating files from directories.
- **Append with newline automatically** – A convenience function to append text with proper line separation.
- write at a certain offset
---
# To do in data structure
- Linked list are very simple, not optimal for big projects. They are easy to implement and good start to understand the basics. The search for a suitable free space can take a long time. Thus, later on try to implement the other data structures such as segregated lists(buckets) or Trees.
- The segregated lists principle: Free blocks are divided into **size classes** (buckets), e.g., 16 bytes, 32 bytes, 64 bytes… So when we want to allocate space, we just look for a suitable block. But it is bad if bucket sizes don’t match request patterns well.
- IN the trees, the blocks are organized from the largest free block till the smallest. Here the search is much 
- Alignment can be handled dynamically using pointer arithmetic.
---

# Tips
- Always **close file descriptors** to avoid leaks
- Use **`ssize_t` for read/write results**.
- Return **error codes**, not strings.
- Provide both **text and binary modes**.
- Add **utility functions**: check existence, copy, move, delete.
- Add **documentation/comments** for every function.
- Optionally, implement a **buffered read/write** to handle large files efficiently.