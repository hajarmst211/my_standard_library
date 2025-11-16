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

// 3: Data structure

typedef struct Metadata{
    size_t size;
    int free;// 1 : free , 0 : allocated
    struct Metadata *next;
}Metadata;


#endif
