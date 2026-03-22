/*
execute_commands.c
- Receives the input from main()
- Calls helper functions to process input (parsing, removing newline and extra spaces, looking for special characters etc.)
- Determines whether the command to be executed is internal or external
- If it is internal, call it right away, if it is external, call the external commands handler function (in external_commands.c)
*/

// Including the header file so that this file can read it and use libraries, constants and function prototypes in it
#include "simpleshell.h"

void execute_commands(char *input) {

    // A list of arguments
    char *args[MAX_ARGS];

    // Special conditions - I/O redirection and background execution
    int dont_wait = 0;          // Background execution flag
    char *input_file = NULL;    // Input file for '<'
    char *output_file = NULL;   // Output file for '>' or '>>'
    int append = 0;             // Flag that tracks: 0 = overwrite, 1 = append for output

    // Trim newline
    remove_newline(input);

    // Skip empty lines or comments
    if (strlen(input) == 0 || input[0] == '#' || input[0] == '/') {
        return;
    }

    // Parse input into arguments
    parse_input(input, args);

    if (!args[0]) {
        return; // Nothing to execute
    }

    // Scan for special tokens
    special_tokens(args, &input_file, &output_file, &append, &dont_wait);

    // Internal command flag
    // Keeps track whether the command is internal or external
    // 0 = false, 1 = true
    int internal = 0;

    // Internal commands
    // dir, environ, echo and help support output redirection
    // They use store and restore approach because the shell would break after I/O redirection otherwise
    // They save the current stdin and stdout using internal_redirection() function
    // Calling internal_redirection() before running the command
    // This redirects I/O to the specified files temporarily
    // restore_redirection() helper resets stdin/stdout after the command finishes
    // This is needed for the shell prompt to work correctly
    // fflush(stdout) makes sure that all output is written to the redirected file
    if (strcmp(args[0], "cd") == 0) {
        cd(args);
        internal = 1; // internal flag set to true, this is the same for every internal command
    } else if (strcmp(args[0], "clr") == 0) {
        clr();
        internal = 1;
    } else if (strcmp(args[0], "dir") == 0) {
        int saved_stdin, saved_stdout; // Used in internal_redirection which uses dup() to store current stdin/stdout to these variables
        internal_redirection(input_file, output_file, append, &saved_stdin, &saved_stdout);
        dir(args);
        fflush(stdout);
        restore_redirection(saved_stdin, saved_stdout);
        internal = 1;
    } else if (strcmp(args[0], "environ") == 0) {
        int saved_stdin, saved_stdout;
        internal_redirection(input_file, output_file, append, &saved_stdin, &saved_stdout);
        environ_vars();
        fflush(stdout);
        restore_redirection(saved_stdin, saved_stdout);
        internal = 1;
    } else if (strcmp(args[0], "echo") == 0) {
        int saved_stdin, saved_stdout;
        internal_redirection(input_file, output_file, append, &saved_stdin, &saved_stdout);
        echo(args);
        fflush(stdout);
        restore_redirection(saved_stdin, saved_stdout);
        internal = 1;
    } else if (strcmp(args[0], "help") == 0) {
        int saved_stdin, saved_stdout;
        internal_redirection(input_file, output_file, append, &saved_stdin, &saved_stdout);
        shell_help();
        fflush(stdout);
        restore_redirection(saved_stdin, saved_stdout);
        internal = 1;
    } else if (strcmp(args[0], "pause") == 0) {
        pause_shell();
        internal = 1;
    } else if (strcmp(args[0], "quit") == 0) {
        quit();
        internal = 1;
    }

    // Only run external commands if not internal
    // Prevents the shell from confusing internal commands with external programs
    // Internal commands must run in the shell itself
    // External commands run in child processes
    if (!internal) {
        run_external_command(args, input_file, output_file, append, dont_wait);
    }
}