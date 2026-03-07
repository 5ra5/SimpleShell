// header file that contains header guards, libraries, constants and function prototypes used in both simpleshell.c and utility.c
// acts like a shared interface between the two .c files

// header guards - preventing duplicate definitions that cause compilation errors
// "if simple shell is not defined, define it"
# ifndef SIMPLESHELL_H
# define SIMPLESHELL_H

// libraries needed for implementation in all c files
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// constants - variables that always stay the same
# define MAX_INPUT 1024
# define MAX_ARGS 64

// function prototypes
// used in utility.c
void show_prompt();
void read_input(char *input);
void remove_newline(char *input);
void parse_input(char *input, char **args);

// used in internal_commands.c
void cd(char **args);
void clr();
void dir(char **args);
void environ_vars();
void echo(char **args);
void shell_help();
void pause_shell();
void quit();
void execute_commands(char *input);

# endif