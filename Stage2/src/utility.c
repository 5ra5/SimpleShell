/*
utility.c
- Contains small helper functions for:
- Input processing, parsing and I/O redirection
- Context and functionality descriptions included below
*/

// Including the header file so that this file can read it and use libraries, constants and function prototypes in it
# include "simpleshell.h"

// 1. INPUT PROCESSING
// show_prompt() - Displays the current working directory as a prompt for input in interactive mode
// Variable cwd stores the current working directory
// getcwd() - gets the current working directory
// Print the current directory
// In Stage 2 I had to use dprintf instead of printf because it prints to a file descriptor
// Using dprintf and STDOUT_FILENO to make sure that the prompt goes straight to the terminal
// Otherwise the prompt would not show when I was testing I/O redirection
// It works alongside fflush(stdout) that is used before and after we invoke this function in main()
void show_prompt(){
    char cwd[MAX_INPUT];
    getcwd(cwd, sizeof(cwd));
    dprintf(STDOUT_FILENO, "%s> ", cwd);
}

// Read input with fgets(), store in input, allow max input size and get it from stdin
// Error handling if input fails
void read_input(char *input){
    if(fgets(input, MAX_INPUT, stdin) == NULL) {
        perror("fgets fail");
    }
}

// Remove the newline character from input
// Using strcspn - finds the index of the first newline and replaces it with null terminator 
void remove_newline(char *input) {
    input[strcspn(input, "\n")] = '\0';
}

// Parsing input using strtok()
// strtok() finds the first word before a space
// We loop through other tokens
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

// Safely scan args for special tokens and remove them from args array (args[i] = NULL)
void special_tokens(char **args, char **input_file, char **output_file, int *append, int *dont_wait) {
    for (int i = 0; args[i] != NULL; i++) {

        // & = background execution
        if (strcmp(args[i], "&") == 0) {
            *dont_wait = 1;       // Set background execution flag to true, passed to the parent process in external_commands.c
            args[i] = NULL;       // Remove from args array
            continue;             // Continue scanning in case multiple special tokens exist
        }

        // < = input redirection
        if (strcmp(args[i], "<") == 0) {
            // Check if there is a token after <
            if (args[i+1] != NULL) {
                *input_file = args[i+1]; // Store token after < as the input file
                args[i] = NULL;          // Remove '<' from args
                i++;  // Skip over the filename (otherwise the filename would be processed again)
            } else {
                // No token after <
                // Using fprintf to stderr because this is not the system-level error
                fprintf(stderr, "error: no input file specified\n");
                return;
            }
            continue;
        }

        // > = output redirection (overwrite)
        if (strcmp(args[i], ">") == 0) {
            if (args[i+1] != NULL) {
                *output_file = args[i+1]; // Token after > is the output file
                *append = 0;              // Set append flag to 0 = overwrite
                args[i] = NULL;
                i++;
            } else {
                fprintf(stderr, "error: no output file specified\n");
                return;
            }
            continue;
        }

        // >> = output redirection (append)
        if (strcmp(args[i], ">>") == 0) {
            if (args[i+1] != NULL) {
                *output_file = args[i+1]; // Token after >> is the output file
                *append = 1;              // Set append flag to 1 = append
                args[i] = NULL;
                i++;
            } else {
                fprintf(stderr, "error: no output file specified\n");
                return;
            }
            continue;
        }
    }
}

// 2. I/O REDIRECTION (INTERNAL AND EXTERNAL)
// Since internal commands run inside the shell process, I separated the redirection functionality based on internal vs external
// internal_redirection() and restore_redirection() temporarily redirect I/O using dup() and dup2()
// Otherwise shell's stdin/stdout would get inconsistent and the prompt would not show
// External commands run in child processes (fork() + execvp())
// I redirected their I/O normally without affecting stdin/stdout

// Apply I/O redirection for internal commands
void internal_redirection(char *input_file, char *output_file, int append, int *saved_stdin, int *saved_stdout) {
    // Save original stdin/stdout
    // dup() - system call which creates a copy of a file desciptor
    // Stored in *saved_stdin, *saved_stdout
    *saved_stdin = dup(STDIN_FILENO);
    *saved_stdout = dup(STDOUT_FILENO);

    // Redirect input only if input_file provided
    // freopen() - makes all input from stdin come from input_file
    // This lets us temporarily redirect the shell standard I/O to files for internal commands
    if (input_file) {
        if (!freopen(input_file, "r", stdin)) {
            perror("input redirection failed");
        }
    }

    // Redirect output only if output_file provided
    // freopen() - makes all writes to stdout go to output_file
    // Mode depends on append or write
    // ? syntax: condition ? value_if_true : value_if_false
    // That is based on the append flag that was set earlier
    // mode is const because it shouldn't be modified
    // mode is a pointer because freopen expects string literals for file mode
    if (output_file) {
        const char *mode = append ? "a" : "w";
        if (!freopen(output_file, mode, stdout)) {
            perror("output redirection failed");
        }
    }
}

// Restore stdin/stdout after internal command
void restore_redirection(int saved_stdin, int saved_stdout) {
    // dup2(old_fd, new_fd) - makes new_fd and old_fd refer to the same file
    // Used to restore stdin and stdout to their original state before redirection
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);

    // close(fd) - closes the file descriptor to release system resources
    // The memory was borrowed with freopen() in internal_redirection()
    close(saved_stdin);
    close(saved_stdout);
}

// I/O redirection for external commands
// Handling input redirection - for external commands
// The process is the same as for internal redirection, but now dup() and dup2() are not necessary
// This is because the redirection happens inside of a child process and it does not disrupt original shell functionality
void input_redirection(char *input_file){
    if (input_file) {
        if (!freopen(input_file, "r", stdin)) {
            perror("input redirection failed");
            exit(1);
        }
    }
}

// Handling output redirection - for external commands
void output_redirection(char *output_file, int append) {
    if (output_file) {
        const char *mode = append ? "a" : "w";
        if (!freopen(output_file, mode, stdout)) {
            perror("output redirection failed");
            exit(1);
        }
    }
}

/*Name: Petra Sartori
Student ID: 23324986
I acknowledge DCU Academic Integrity Policy while working on this project.
My work is my work only and is a result of research, practice and design which I did on my own.
This project does not contain any plagiarised content.*/