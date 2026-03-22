/*
internal_commands.c
- Contains all interncal commands implemented in Stage 1
*/

// Including the header file so that this file can read it and use libraries, constants and function prototypes in it
#include "simpleshell.h"

// 1. CD
// If second argument does not exist, print the current directory
// If second argument exists, change to a directory of that name
// Included error handling
void cd(char **args){
    char cwd[MAX_INPUT]; // current directory

    // Case 1: second argument does not exist
    if (!args[1]){
        if (getcwd(cwd, sizeof(cwd))){
            printf("%s\n", cwd);
        } else {
            perror("getcwd failed");
        }
    } else { // Case 2: second argument exists
       if(chdir(args[1])){
            perror("cd failed"); // Error message printed if the directory is invalid/doesn't exist
       }
       // chdir succeeded
       // Using setenv - changing the environment variable PWD
       else if (getcwd(cwd, sizeof(cwd))){
            setenv("PWD", cwd, 1);
       }
    }
}

// 2. CLR
// Using system("clear") to clear the screen
void clr(){
    system("clear");   
}

// 3. DIR
// Using sprintf because system function on it's own takes only one argument
// snprintf - stores a string in a variable "command" that can be passed to system function
void dir(char **args){
    char command[MAX_INPUT]; // using max input to match the buffer size

    // Storing the string we want to pass to the function based on the case
    if (args[1]){ // directory given
        snprintf(command, sizeof(command), "ls -al %s", args[1]);
    }
    else{ // directory not given
        snprintf(command, sizeof(command), "ls -al");
    }

    system(command);
}

// 4. ENVIRON
// Listing all environment strings that are contained in environ array
// Just traversing the list and printing its contents
void environ_vars(){
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++){
        printf("%s\n", environ[i]);
    }
}

// 5. ECHO
// Traverse the argument list and print each word one after another with a space between them, add \n at the end
void echo(char **args){
    for(int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}

// 6. HELP
// Getting the path dynamically so help can work in batch mode and/or different systems
// Using snprintf again to pass more and the current working directory to system()
// Using more to page thorugh text one screenful at a time
void shell_help(){
    char cwd[MAX_INPUT];
    char command[MAX_INPUT + 50]; // Extra space

    // Get the path dynamically and calling system(more) function 
    if (getcwd(cwd, sizeof(cwd))){
        snprintf(command, sizeof(command), "more %s/manual/readme.txt", cwd);
        system(command);
    } else { // error handling
        perror("getcwd failed");
    }
}

// 7. PAUSE
// Print the message to indicate that the shell is paused
// Shell will not process any commands after 
// Loop until the user presses enter - \n
void pause_shell(){
    printf("Shell paused. Press Enter to continue.\n");

    int c;
    while((c = getchar()) != '\n');
}

// 8. QUIT
// Exit the shell
void quit(){
    exit(0);
}