// this file contains general helper functions for the simpleshell

// including the header file so that this file can read it and use libraries, constants and function prototypes in it
# include "simpleshell.h"

// variable cwd stores the current working directory
// getcwd() - gets the current working directory
// print the current directory
void show_prompt(){
    char cwd[MAX_INPUT];
    getcwd(cwd, sizeof(cwd));
    printf("%s> ", cwd);
}

// read input with fgets(), store in input, allow max input size and get it from stdin
// error handling if input fails
void read_input(char *input){
    if(fgets(input, MAX_INPUT, stdin) == NULL) {
        perror("fgets fail");
    }
}

// remove the newline character from input
// using strcspn - finds the index of the first newline and replaces it with null terminator 
void remove_newline(char *input) {
    input[strcspn(input, "\n")] = '\0';
}

// parsing input using strtok()
// strtok() finds the first word before a space
// we loop through other tokens
void parse_input(char *input, char **args) {
    char* token = strtok(input, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARGS) {
        args[i] = token; // store a token in args array
        token = strtok(NULL, " "); // continue splitting the same string
        i++;
    }

    args[i] = NULL; // end of arg list
}