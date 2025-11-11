// string_library.c
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

int length_string(char* string){
    int lenght=0;
    while(*string != '\0'){
        lenght ++;
        string++;
    }
    return lenght;
}

typedef struct {
    char *data;        
    int length;     
    size_t capacity;   
} MyString;

MyString create_string(char* string){
    MyString new_string;
    new_string.length = length_string(string);
    new_string.capacity = new_string.length * 2 +1;
    new_string.data = (char*)malloc(new_string.capacity);
    int i = 0;
    while( i < new_string.length){
        new_string.data[i] = string[i];
        i++;
    }
    new_string.data[new_string.length] = '\0';

    return new_string;
}


void my_putchar(char single_character){
    int buffer_size= sizeof(char);
    write(1, &single_character, buffer_size);
}

void print_string(char* string){
    int lenght;
    lenght= length_string(string);
    //looping over each character of the string
    for(int i = 0 ; i < lenght ; i++){
        my_putchar(string[i]);
    }
}

void concatenate_string(MyString* string1, MyString* string2){
    int available_space = string1->capacity - string1->length;
    if(available_space < string2->length + 1){
        int size_needed = string1->length + string2->length + 1;
        char* new_data = (char*)realloc(string1->data , size_needed);
        string1->data= new_data;
        string1->capacity = size_needed;
    }

    for(int i = 0; i < string2->length; i++){
        string1->data[i + string1->length] = string2->data[i];
    }
    string1->data[string1->length + string2-> length] = '\0';
}

int insert_character(MyString* string, char character, int index){

    if(string->length < index || index < 0){
        return 1;
    }

    if(string->capacity <= string->length + 1){
        char* new_data = (char*)realloc(string->data, string->capacity*2 + 1);
        if(!new_data){
            return 1;
        }
        string->data = new_data;
        string->capacity = string->capacity*2 + 1;
    }

    for(int i = string->length - 1; i >=  index  ; i-- ){
        int len = string->length;
        string->data[i+1] = string->data[i];
    }

    string->data[index] = character;
    string->length++;
    string->data[string->length] = '\0';
    return 0;
}

int compare_strings(MyString* string1, MyString * string2){
    // returns 1 if the strings are different
    // returns 0 if the strings are equal
	if(string1->length != string2->length) {
        return 0;
    }

    for(int i = 0; i < string1->length; i++){
        if(string1->data[i] != string2->data[i]){
            return 1;
        }
    }
	return 1;
}

int replace_character(MyString* string, char character_to_replace, char character_to_add){
    int i = 0; 
    for(i ; i < string->length; i++){
        if(string->data[i] == character_to_replace)
            break;
    }
    if(i == string->length +1){
        return 1;
    }
    string->data[i] = character_to_add;
    return 0;
}

MyString *convert_int_to_string(int number){
    MyString *return_string = (MyString*)malloc(sizeof(MyString));
    char* data = (char*)malloc(32*sizeof(char));
    int sign = number;
    int i = 0;

    if (number == 0){
       data[i++] = '0';
    }
    else{
        if(number < 0){
             number = -number;
        }

        while (number > 0) {
            data[i++] = number % 10 + '0';
            number /= 10;
        }
        if(sign < 0){
            data[i++] = '-';
        }
    }
    data[i] = '\0';
        for (int j = 0; j < i / 2; j++) {
        char temp = data[j];
        data[j] = data[i - j - 1];
        data[i - j - 1] = temp;
    }

    *return_string = create_string(data);
    free(data);
    return return_string;
}

MyString copy_string(MyString string){
    MyString string_copy;
    string_copy = create_string(string.data);
    return string_copy;
}

