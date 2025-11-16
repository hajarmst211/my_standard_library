// header/my_library.h
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef MY_LIBRARY   
#define MY_LIBRARY

// 1: string library

void my_putchar(char single_character);

void print_string(char* string);

int length_string(char* string);

typedef struct {
    char *data;        
    int length;     
    size_t capacity;   
} MyString;

MyString create_string(char* string);

void concatenate_string(MyString* string1, MyString * string2);

int insert_character(MyString* string, char character, int index);

int compare_strings(MyString* string1, MyString * string2);

int replace_character(MyString* string, char character_to_replace, char character_to_add);

MyString *convert_int_to_string(int number);

MyString copy_string(MyString string);

// 2:files library

char* read_from_file(char *path_to_file);

int overwrite_file(char* path_to_file, char* buffer);

int does_exist(char* path_to_file);

int get_file_size(int file_descriptor);

int remove_file(char* path_to_file);

int set_permissions(char* path_to_file, int permissions);

char* read_using_fd(int file_descriptor);

char* read_at_offset(char* path_to_file, off_t offset);

int append_to_file(char* path_to_file, char* buffer);

int copy_file(char* path_to_file);

int open_file(char* path_to_file, int flags,  mode_t mode);

// 3: malloc



#include <stddef.h>

typedef struct MetaData{
    size_t size;
    int is_free;
    struct MetaData *next_chunk;
    struct MetaData *previous_chunk;
} MetaData;

extern MetaData* free_chunks_list_head;

MetaData* search_available_chunk(size_t needed_size, MetaData* free_chunks_list_head);

void* remove_allocated_chunk(MetaData** chunk_to_remove);

MetaData* new_allocated_chunk(MetaData* metadata, size_t needed_size);

void* trim_chunk(MetaData* allocated_chunk, size_t needed_size);

void* request_memory_from_os(MetaData* metadata, size_t needed_size);

void* halloc(size_t data_size);

void* free_pointer(void* chunk);

#endif
