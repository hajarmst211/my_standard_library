****## Definition
- They are the way a user can use the kernel mode. Aka, the mode where a computer program requests a service from the kernel of the operating system.

#### File descriptor
- A **file descriptor** is an integer that uniquely identifies an opened file of the process
- FD points to a **file table entry**, which contains the real state of the open file.
- The OS allocates for each process  a unique file descriptors table
- File table entry is the **kernel’s** representation of the open file/resource.
- The system-wide file table entry contains details about the file and points to the **inode table**(contains: pointers to the data blocks, file size, permissions, owner info ...)
##### fd for Input/output :
- Unix treats everything as a file including the input and output channels
- Having a **file descriptor** allows programs to read from `stdin` or write to `stdout` **using the same system calls** (`read()`, `write()`, `close()`) that work for regular files.
- By using a **file descriptor**, the program doesn’t need to know what the underlying device is. The kernel handles the actual I/O

##### example: `stdin` (keyboard) has FD 0.
- FD 0 points to a **file table entry**.
- That file table entry points not to an inode, but to a **terminal driver buffer** in the kernel.
- When you call `read(0, buf, n)`, the kernel looks at the file table entry, then fetches data from the keyboard buffer.
---
## Standard stdin/stdout

| Stream | File Descriptor (FD) | Common System Calls | Description                                                       |
| ------ | -------------------- | ------------------- | ----------------------------------------------------------------- |
| stdin  | 0                    | `read()`            | Reads input from the standard input (keyboard by default)         |
| stdout | 1                    | `write()`           | Writes output to the standard output (terminal by default)        |
| stderr | 2                    | `write()`           | Writes error messages to the standard error (terminal by default) |

##### Read
```c
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
```
Parameters:
- fd – File descriptor (e.g., 0 for stdin, or any file opened via open())
- buf – Pointer to a buffer where the data will be stored
- count – Number of bytes to read

##### Write
```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```
Parameters:
- fd – File descriptor (e.g., 1 for stdout, or any file opened via open())
- buf – Pointer to the data to write
- count – Number of bytes to write
- Use **`ssize_t` for read/write results**.
---
### Open flags
- Each flag corresponds to a specific bit pattern that the kernel interprets as a configuration for file access behavior.
- you can combine them using the bitwise operator `|`
##### Basic flags:
|Flag|Meaning|
|---|---|
|`O_RDONLY`|Open for **read only**|
|`O_WRONLY`|Open for **write only**|
|`O_RDWR`|Open for **read and write**|
##### Additional flags:
| Flag                       | Meaning                                                                                     |
| -------------------------- | ------------------------------------------------------------------------------------------- |
| `O_CREAT`                  | Create the file if it doesn’t exist. Requires a third argument `mode_t mode` (permissions). |
| `O_EXCL`                   | Use with `O_CREAT`: fail if the file already exists.                                        |
| `O_TRUNC`                  | If the file exists, removes everything in it.                                               |
| `O_APPEND`                 | Move the file offset to the end before every write (used for appending data).               |
| `O_NONBLOCK` or `O_NDELAY` | Open in non-blocking mode (don’t wait for I/O readiness).                                   |
| `O_SYNC`                   | Write operations are synchronized to disk before returning.                                 |
| `O_DSYNC`                  | Similar to `O_SYNC` but only syncs data (not metadata).                                     |
| `O_RSYNC`                  | Synchronize read operations as well.                                                        |
| `O_NOFOLLOW`               | Don’t follow symbolic links.                                                                |
| `O_CLOEXEC`                | Automatically close file descriptor on `exec()` calls.                                      |
