#include "../header/my_library.h"
#include <stdio.h>


int main(){
    char *data="hajar";
    char *data2 = "hajar";
    MyString string = create_string(data);
    MyString string2 = create_string(data2);
    int indice = 4;
    char character = 'b';
    float number = 4.00557;

    MyString *result = convert_float_to_string(number);
/*
    printf("the comparason is between %s. and %s. \n  ", data, data2);
    printf("this is the replace char results %d\n", result);
    printf("the first string is : %s\n the copy is:%s\n",string.data, result.data);
*/  
  printf("the number is: %f \n the return of the fucntion is:\n the data %s\nthe lenght: %d \n the capacity: %lu\n", number, result->data,result->length,result->capacity);
    return 0;
}
