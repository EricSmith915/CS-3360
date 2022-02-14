//Eric Smith
//2/13/2021
//CS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim) {
    //checks if character is deliminator and returns false if it is not
    if (c == delim) {
        return 1;
    } else {
        return 0;
    }
}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim) {
    //checks if character is deliminator and returns true if it is not
    if (c != delim) {
        return 1;
    } else {
        return 0;
    }
}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words.*/
char *word_start(char *str, char delim) {
    //Variable that checks if deliminator is found
    bool delimFound = 0;
    //Iterates through the array until deliminator is found, and then
    //returns first non deliminator character
    while (*str != '\0') {
        if (*str == delim && delimFound == 0) {
            delimFound = 1;
        }
        else if (delimFound == 1 && *str != delim){
            return str;
        }
        str++;
    }
    return NULL;
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char *str, char delim) {
    //iterates until a deliminator is found, then returns that
    while (*str != '\0') {
        if (*str == delim) {
            return str;
        }
        str++;
    }
    return NULL;
}

//method which will help keep track of size of strings
int end_word_len(char *str, char delim){
    int counter = 0;

    //Iterates until deliminator is found, adding 1 each iteration.
    while (*str != '\0') {
        if (*str == delim) {
            return counter;
        }
        str++;
        counter++;
    }
    return counter;
}
/* ("Hello,world,the,,,,,,a,hello") */



/* Counts the number of words or tokens*/
int count_tokens(char *str, char delim) {
    int counter = 0;
    //Counts the number of deliminators and adds one to the total.
    while(*str != '\0'){
        if(*str == delim){
            counter++;
        }
        str++;
    }
    return ++counter;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim) {
    //Uses string copy method to copy infividual string
    char *copied = malloc(len+1);

    strncpy(copied, inStr, len);

    return copied;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   delimiter-separated tokens from zero-terminated str.
   For example, tokenize("hello world string"), with a character delimiter
   of a space " " would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char **tokenize(char *str, char delim) {
    char **tokens = malloc(200);
    char **iterate = tokens;
    int i = 0;


    int len = 0;
    char *temp = malloc(500);
    strncpy(temp, str, 500);

    //counts length of original string
    while(*temp != '\0'){
        len++;
        temp++;
    }

    len -= count_tokens(str, delim);

    //Creates temporary pointers, and then adds them to the double pointer.
    //This happens for each word in the string.
    while(len >= 0){
        int increment = end_word_len(str, delim);
        char *token = copy_str(str, increment, delim);

        *iterate = token;
        iterate++;

        str += (increment + 1);
        len -= (increment);
    }
    return tokens;
}

//prints all tokens
void print_all_tokens(char **tokens) {
    int i = 0;


    //iterates through the first pointer to the char pointer
    while(*tokens){
        char *temp = *tokens;
        printf("tokens[%d]: ", i);
        //checks if the char pointer is empty string and iterates though if not while printing
        while(*temp != '\0'){
            printf("%c", *temp++);
        }
        printf("\n");
        i++;
        *tokens++;
    }


}

int main() {
    char input[200];
    char deli;


    printf("Enter the deliminator character:\n");
    scanf("%c", &deli);

    printf("Enter the input string:\n");
    scanf("%s", input);

    char *pinput = input;

    print_all_tokens(tokenize(pinput, deli));

}
//This is a change
