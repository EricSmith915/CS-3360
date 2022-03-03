#include <stdio.h>

int main(){
    char* test = "hello world";
    char* test2 = test;

    test2++;
    test2++;

    printf("%c", *test);
    printf("%c", *test2);
}