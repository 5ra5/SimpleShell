// this file contains a function which handles input and calls all functions based on the first argument
// it is used in both batch mode and interactive mode to avoid repetition in simpleshell.c

// including the header file so that this file can read it and use libraries, constants and function prototypes in it
# include "simpleshell.h"

void execute_commands(char *input) {

    // a list of arguments
    char *args[MAX_ARGS];

    // trim newline from input
    remove_newline(input);

    // skipping empty lines
    if(strlen(input) == 0){
        return;
    }

    // skipping comment lines in batch mode in case there is any
    if(input[0] == '#' || input[0] == '/'){
        return;
    }

    // input = command + argument
    parse_input(input, args);

    // error handling
    if (!args[0]){
        return;
    }

    // calling internal commands based on the first argument
    if (strcmp(args[0], "cd") == 0){
        cd(args);
    }
    else if(strcmp(args[0], "clr") == 0){
        clr();
    }
    else if(strcmp(args[0], "dir") == 0){
        dir(args);
    }
    else if(strcmp(args[0], "environ") == 0){
        environ_vars();
    }
    else if(strcmp(args[0], "echo") == 0){
        echo(args);
    }
    else if(strcmp(args[0], "help") == 0){
        shell_help();
    }
    else if(strcmp(args[0], "pause") == 0){
        pause_shell();
    }
    else if(strcmp(args[0], "quit") == 0){
        quit();
    }
    else{
        printf("command '%s' not found \n", args[0]);
    }
}

/*Name: Petra Sartori
Student ID: 23324986
I acknowledge DCU Academic Integrity Policy while working on this project. 
My work is my work only and is a result of research, practice and design which I did on my own.
This project does not contain any plagiarised content.*/