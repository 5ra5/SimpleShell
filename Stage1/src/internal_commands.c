// this file contains all internal commands used by simpleshell

// including the header file so that this file can read it and use libraries, constants and function prototypes in it
#include "simpleshell.h"

// 1. CD
// if second argument does not exist, print the current directory
// if second argument exists, change to a directory of that name
// included error handling
void cd(char **args){
    char cwd[MAX_INPUT]; // current directory

    // case 1: second argument does not exist
    if (!args[1]){
        if (getcwd(cwd, sizeof(cwd))){
            printf("%s\n", cwd);
        } else {
            perror("getcwd failed");
        }
    } else { // case 2: second argument exists
       if(chdir(args[1])){
            perror("cd failed"); // error message printed if the directory is invalid/doesn't exist
       }
       // chdir succeeded
       // using setenv - changing the environment variable PWD
       else if (getcwd(cwd, sizeof(cwd))){
            setenv("PWD", cwd, 1);
       }
    }
}

// 2. CLR
// using system("clear") to clear the screen
void clr(){
    system("clear");   
}

// 3. DIR
// using sprintf because system function on it's own takes only one argument
// snprintf - stores a string in a variable "command" that can be passed to system function
void dir(char **args){
    char command[MAX_INPUT]; // using max input to match the buffer size

    // storing the string we want to pass to the function based on the case
    if (args[1]){ // directory given
        snprintf(command, sizeof(command), "ls -al %s", args[1]);
    }
    else{ // directory not given
        snprintf(command, sizeof(command), "ls -al");
    }

    system(command);
}

// 4. ENVIRON
// listing all environment strings that are contained in environ array
// just traversing the list and printing its contents
void environ_vars(){
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++){
        printf("%s\n", environ[i]);
    }
}

// 5. ECHO
// traverse the argument list and print each word one after another with a space between them, add \n at the end
void echo(char **args){
    for(int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

// 6. HELP
// getting the path dynamically so help can work in batch mode and/or different systems
// using snprintf again to pass more and the current working directory to system()
// using more to page thorugh text one screenful at a time
void shell_help(){
    char cwd[MAX_INPUT];
    char command[MAX_INPUT + 50]; // extra space

    // get the path dynamically and calling system(more) function 
    if (getcwd(cwd, sizeof(cwd))){
        snprintf(command, sizeof(command), "more %s/manual/readme.txt", cwd);
        system(command);
    } else { // error handling
        perror("getcwd failed");
    }
}

// 7. PAUSE
// print the message to indicate that the shell is paused
// shell will not process any commands after 
// loop until the user presses enter - \n
void pause_shell(){
    printf("Shell paused. Press Enter to continue.\n");

    int c;
    while((c = getchar()) != '\n');
}

// 8. QUIT
// exit the shell
void quit(){
    exit(0);
}

/*Name: Petra Sartori
Student ID: 23324986
I acknowledge DCU Academic Integrity Policy while working on this project. 
My work is my work only and is a result of research, practice and design which I did on my own.
This project does not contain any plagiarised content.*/