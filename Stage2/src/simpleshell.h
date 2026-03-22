// header file that contains header guards, libraries, constants and function prototypes used in .c files
// acts like a shared interface between the .c files

// header guards - preventing duplicate definitions that cause compilation errors
// "if simple shell is not defined, define it"
# ifndef SIMPLESHELL_H
# define SIMPLESHELL_H

// libraries needed for implementation in all c files
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

// constants - variables that always stay the same
# define MAX_INPUT 1024
# define MAX_ARGS 64

// function prototypes
void show_prompt();
void read_input(char *input);
void remove_newline(char *input);
void parse_input(char *input, char **args);
void cd(char **args);
void clr();
void dir(char **args);
void environ_vars();
void echo(char **args);
void shell_help();
void pause_shell();
void quit();
void execute_commands(char *input);
void input_redirection(char *input_file);
void output_redirection(char *output_file, int append);
void internal_redirection(char *input_file, char *output_file, int append, int *saved_stdin, int *saved_stdout);
void restore_redirection(int saved_stdin, int saved_stdout);
void special_tokens(char **args, char **input_file, char **output_file, int *append, int *dont_wait);
void run_external_command(char **args, char *input_file, char *output_file, int append, int dont_wait);

# endif

/*Name: Petra Sartori
Student ID: 23324986
I acknowledge DCU Academic Integrity Policy while working on this project.
My work is my work only and is a result of research, practice and design which I did on my own.
This project does not contain any plagiarised content.*/