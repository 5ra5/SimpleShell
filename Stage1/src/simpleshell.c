// this file contains the main function which brings all of the implementation together

// including the header file so that this file can read it and use libraries, constants and function prototypes in it
# include "simpleshell.h"

int main(int argc, char *argv[]){

    // dynamic memory allocation for input using malloc
    char *input = malloc(MAX_INPUT);

    // error handling for malloc
    if(input == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    // SHELL ENVIRONMENT
    // using realpath to get full absolute path of the shell
    // avoiding hardcoded path
    char *shell_path = realpath(argv[0], NULL);

    // error handling
    if (!shell_path){
        perror("realpath failed");
        exit(1);
    }

    // setenv - change or add a environment variable
    // PWD - holds the current directory
    // SHELL - environment variable
    char cwd[MAX_INPUT];
    if(getcwd(cwd, sizeof(cwd))){
        setenv("PWD", cwd, 1);
        setenv("SHELL", shell_path, 1);

        // free the memory used with realpath
        free(shell_path);
    }

    // check which mode to run the shell in
    // default = standard input
    FILE *input_stream = stdin;

    // if there is more than 1 argument when we run the shell, go into batch mode
    // batch mode - reading commands from a file instead of stdin
    if (argc > 1){
        input_stream = fopen(argv[1], "r");

        // error handling
        if (!input_stream) {
            perror("failed to open batch file");
            free(input);
            exit(1);
        }
    }

    // main loop (works for both interactive and batch mode)
    while (1) {
        // interactive mode - show the prompt, read the input
        if (input_stream == stdin){
            show_prompt();
            read_input(input);
        } else {
            // batch mode
            if (fgets(input, MAX_INPUT, input_stream) == NULL){
                break; // end of batch file
            }
        }

        // pass the input to execute_commands function which handles input and calls internal commands
        execute_commands(input);
    }

    // if input came from a file, close the file
    if (input_stream != stdin){
        fclose(input_stream);
        return 0;
    }

    // free memory used for input
    free(input);
    return 0;
}

/*Name: Petra Sartori
Student ID: 23324986
I acknowledge DCU Academic Integrity Policy while working on this project. 
My work is my work only and is a result of research, practice and design which I did on my own.
This project does not contain any plagiarised content.*/