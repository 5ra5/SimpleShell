/*
simpleshell.c
- Entry point for simpleshell - main() function
- Sets up shell environment
- Determines interactive vs batch mode, reads input, sends it to a handler (execute_commands())
*/

// Including the header file so that this file can read it and use libraries, constants and function prototypes in it
# include "simpleshell.h"

int main(int argc, char *argv[]){

    // Dynamic memory allocation for input using malloc
    char *input = malloc(MAX_INPUT);

    // Error handling for malloc
    if(input == NULL) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }

    // SHELL ENVIRONMENT
    // Using realpath() to get full absolute path of the shell
    // realpath(const char *restrict path, char *restrict resolved_path)
    // If no error, it returns a pointer to the resolved_path
    // Otherwise returns NULL
    // Avoiding hardcoded path, ensuring environment variable is accurate
    char *shell_path = realpath(argv[0], NULL);

    // Error handling for realpath
    if (!shell_path){
        perror("Realpath failed");
        exit(1);
    }

    // getcwd() - get current working directory
    // setenv() - change or add an environment variable
    // int setenv(const char *name, const char *value, int overwrite);
    // PWD - holds the current directory
    // SHELL - holds the full path of the shell executable
    char cwd[MAX_INPUT];
    if(getcwd(cwd, sizeof(cwd))){
        setenv("PWD", cwd, 1);
        setenv("SHELL", shell_path, 1);

        // free the memory used with realpath
        free(shell_path);
    }

    // Check which mode to run the shell in
    // FILE* - where the shell should read input
    // Default = standard input
    FILE *input_stream = stdin;

    // If there is more than 1 argument when we run the shell, go into batch mode
    // Batch mode - reading commands from a file instead of stdin
    if (argc > 1){
        input_stream = fopen(argv[1], "r");

        // error handling
        if (!input_stream) {
            perror("failed to open batch file");
            free(input);
            exit(1);
        }
    }

    // Main loop
    // Works for both interactive and batch mode
    // Sends input to a handler until the shell is terminated
    while (1) {
        // Interactive mode - show the prompt, read the input
        // Had to add fflush(stdout) before and after showing the prompt, otherwise the prompt and previous output would not always show
        // This is because stdout was buffered, so I had to force it to always be written immediately to the terminal
        if (input_stream == stdin){
            fflush(stdout); // Restore stdout to terminal before printing prompt
            show_prompt();
            fflush(stdout); // Ensure it actually prints
            read_input(input);
        } else {
            // Batch mode - fgets() reads input one line at a time
            // fgets() returns NULL when it gets to EOF or error
            // Breaking the loop stops the shell when the batch file is finished
            if (fgets(input, MAX_INPUT, input_stream) == NULL){
                break; // End of batch file, stop the shell
            }
        }

        // Pass the input to execute_commands() function which calls either internal or external commands
        execute_commands(input);
    }

    // At the end - if input came from a file, close the file
    if (input_stream != stdin){
        fclose(input_stream);
        return 0;
    }

    // Free memory used for input
    free(input);
    return 0;
}