// include/my_library.h
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef MY_PUTCHAR_H   // "If not defined yet..."
#define MY_PUTCHAR_H

void my_putchar(char single_character);

void print_string(char* string);


int length_string(char* string);

typedef struct {
    char *data;        
    int length;     
    size_t capacity;   
} MyString;

MyString create_string(char* string);


void my_putchar(char single_character);

void print_string(char* string);

void concatenate_string(MyString* string1, MyString * string2);

int insert_character(MyString* string, char character, int index);

int compare_strings(MyString* string1, MyString * string2);

int replace_character(MyString* string, char character_to_replace, char character_to_add);

MyString *convert_int_to_string(int number);

MyString copy_string(MyString string);

#endif
