- The heap is where `malloc()` and `new` get their memory from. Initially, it's just a large empty space that the allocator manages.

# Malloc
##### Allocation size:
- When we request a certain space in the memory, our programme doesn't reserve just that.
- It needs space for a hidden header where it stores metadata such as the block size, the status of the block (free or allocated) and optionally a pointer for the next/previous block in a list.
- Also, there's a padding. The padding is some unused bits that the alocator inserts to ensure that certain types of data be aligned in memory for efficient access. 
   **Example**:
	- A `int` (4 bytes) should ideally start at an address divisible by 4.
	- A `double` (8 bytes) should ideally start at an address divisible by 8.
   **Why?** Misaligned accesses can cause:
	- Extra CPU cycles (slower access)
	- Hardware exceptions on some architectures
---
## Structure padding
- the processor doesn't read one byte at a time. It reads one word at a time. If it is a 32 bit processor it reads 4 bytes (the word) at a time. and a 64 bits processor reads 8 bytes(the word) at a time. 
- From here comes the padding concept: Each element must me read through a certain number of CPU cycles.
- An int or a float are supposed to take one CPU cycle since they are saved on 4 bytes. And char elements on one CPU cycle.
- An int or a float cannot be divided on two memory blocks. It must be stored on a multiple of 4 offset.

## Structure Packing
- if we want to avoid wasting CPU cycles, we need to respect the padding. But that is gonna waste a lot of memory spaces.
- If, we care more about the waste of memory, we can prevent it by use the packing technique.
	That by adding this line in the top of your code:
	`#pragma pack(1)`
- but real allocators almost never use “packed” structures.

## Difference between them
- The difference is that the padding optimizes CPU cycles and the packing cares more about the waste of free memory. 
- According to the priority, one must choose between these two techniques. 
- I will look for a middle ground way to try to optimize the maximum of each feature.
---
## Programme break modifications
- The programme break is where the last element of the heap lives.
- By incrementing it (moving upwards) we allocate more space. And by decrementing it(downwards) we free space.
![[Pasted image 20251115002854.png|400]]
### System calls:
##### sbrk (alignement)
- It increments the programme break by "alignement"
- alignement is of type: `uintptr_t `
- If increment is negative, the amount of allocated space is decreased by increment bytes.
- it returns the adresse of the previous programme break value
- the return's type is void*
- If it fails to find your requested size it returns `(void*) -1`
- `sbrk(0)` is used to find the end of the heap which is also  the start of the new allocated memory.

##### brk(void* add)
- The _brk()_ function sets the break value to _addr_ and changes the allocated space accordingly.
- Upon successful completion, _brk()_ returns 0. Otherwise, it returns -1 and sets _errno_ to indicate the error.
##### mmap 
- For modern allocators
- maybe that would be an extension or a version 2 of this library
