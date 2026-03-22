/*
external_commands.c
- Functionality for executing external commands
- fork() used to create a new child process to run the command (copy of the parent shell)
- execvp() used to execute the external command in the child process
- Calls I/O redirection handlers
- Handles background execution
*/

// Including the header file so that this file can read it and use libraries, constants and function prototypes in it
#include "simpleshell.h"

// Main external command function
// fork -> handle I/O -> exec -> wait
void run_external_command(char **args, char *input_file, char *output_file, int append, int dont_wait) {

    pid_t pid = fork();  // Create a new process
    if (pid < 0) {
        perror("fork failed"); // Error handling
    }
    else if (pid == 0) { // Child process - always has pid 0
        
        // Call I/O redirection for external commands
        input_redirection(input_file);
        output_redirection(output_file, append);

        // Execute the external command
        // execvp() - replaces current process image with a new program
        // Also searches the PATH environment variable to locate the executable
        // args[0] = new program
        execvp(args[0], args);

        // Error handling
        perror("exec failed");
        exit(1);
    }
    else { // Parent process
        // If the background execution flag is false
        // Wait for the child to finish execution
        // Ensures foreground commands complete before showing the prompt
        if (!dont_wait)
            waitpid(pid, NULL, 0);
        else
            // Background execution - parent does not wait
            // All commands with & at the end run concurrently without blocking the shell
            // Prompt is shown right away
            // I printed the child PID to show that background execution was successful
            printf("Background process PID: %d\n", pid);
    }
}

/*Name: Petra Sartori
Student ID: 23324986
I acknowledge DCU Academic Integrity Policy while working on this project.
My work is my work only and is a result of research, practice and design which I did on my own.
This project does not contain any plagiarised content.*/