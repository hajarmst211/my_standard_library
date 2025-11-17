// my_printf.c

#include "../header/my_library.h"
#include <stdarg.h>

void format_specifier(va_list list, MyString* buffer_ptr, char key){

    if(key == 'd'){
        //type = int
        int element = va_arg(list, int);//we now going to read an integer
        MyString* converted_int = convert_int_to_string(element);//a pointer to the string format of the int
        concatenate_string(buffer_ptr, converted_int);//added the integer to the end of the buffer to output
        free(converted_int->data);
        free(converted_int);
    }
    if(key == 'f'){
        float element = (float)va_arg(list, double);
        MyString* converted_float = convert_float_to_string(element);
        concatenate_string(buffer_ptr, converted_float);
        free(converted_float->data);
        free(converted_float);
    }
    if(key == 'c'){
        char element = (char) va_arg(list, int);
        MyString converted_character = create_string(&element);
        concatenate_string(buffer_ptr, &converted_character);
    }
    if(key == 's'){
        char* element = va_arg(list,char*);
        MyString converted_character = create_string(element);
        concatenate_string(buffer_ptr, &converted_character);
    }

}

void my_printf(char* string, ...){
    va_list list;
    //the first argument of va_start must the name of the last fixed argument
    // wich is also the lenght of the string
    va_start(list, string);
    MyString buffer = create_string("");
    int length = length_string(string);
    for(int i = 0; i < length ; i++){
        if(string[i] == '%')
        {
            format_specifier(list, &buffer, string[i+1]);
            if(i != length-1) i++;
        }
        else{
            char single_character = string[i];
            MyString string_to_add = create_string(&single_character);
            concatenate_string(&buffer, &string_to_add);
        }
    }
    write(1, buffer.data, (size_t)length);
    va_end(list);
}