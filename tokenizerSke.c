#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim) {
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
    while (&str != '\0') {
        if (&str == delim) {
            return str;
        }
        str++;
    }
    return NULL;
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char *str, char delim) {

}

/* Counts the number of words or tokens*/
int count_tokens(char *str, char delim) {

}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim) {

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

}

void print_all_tokens(char **tokens) {

}

int main() {
    printf("Hello, World!\n");
    return 0;
}
