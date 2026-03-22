User Manual

Shell:
    the command-line interface (CLI) program that takes human commands and parses them for the operating system to execute.

Program environment:
    Collection of environment variables that store information about your system and the shell.
    Use the command environ to see all environment variables the shell knows about.

Environment variables:
    This shell has two environment variables:
    PWD = current directory (updates every time you switch directories)
    SHELL = path to the shell executable (identifies the current shell being used)

Interactive mode:
    User dynamically types in commands, and shell processes and executes them.

Batch mode:
    User passes a file that contains a set of commands to the shell.


To start using the shell:
    1. compile
    2. run in interactive mode or
    3. run in batch mode

Compile the shell
    go into Stage2 directory
    run "make".

To run the shell in interactive mode:
    run ./bin/simpleshell
    or go into bin directory and run ./simpleshell

To run the shell in batch mode:
    run ./bin/simpleshell batchFile.txt
    or go into bin directory and run ./simpleshell batchFile.txt

To delete the binary file (recommended if you want to keep your directories clean)
    make clean

I/O redirection:
    Use files to read and write information instead of the keyboard.

Output redirection:
    command > file.txt (overwrite file - if the file exists, delete the content and print command output)
    command >> file.txt (append - command output is added to the old content of a file)
    Save the output of a command into a file instead of displaying it in the terminal.
    Use commands like echo, dir, environ, help
    Or external commands like ls
    File is created unless it exists already.

Input redirection:
    command < file.txt
    Take input from a file instead of the keyboard.

Background execution:
    command &
    Add & at the end of the command line for it to be executed in the background.
    Continue using the shell normally while the process executes.

Foreground execution:
    Keyboard input without & at the end will prevent you from using the shell until the current process
    is finished executing.
    Consider using background execution for processes that take a long time to complete.


Available internal commands:

cd directoryName
    Change the current default directory.
    If you run cd on its own, the current directory will be reported.

clr
    Clear the screen.
    All interactions with the shell except for the current prompt will be deleted.

dir
    List the detailed contents of a directory (including hidden files).
    Following details of each file are shown:
        file type + permissions
        link count (number of hard links leading to the specific file)
        owner
        group
        file size
        last modification time
        file name

environ
    List all the environment strings
    Programs read these values to determine how they should behave.

echo sampleArgument
    Print (echo) the sampleArgument (it can be anything you like).
    Multiple spaces/tabs are formatted and reduced to a single space.

help
    Display this user manual.

pause
    Pause the shell operation.
    Press the Enter key to continue operation.

quit
    Quit the shell.

External commands:
    The shell now supports any external programs execution (given they are available on the system).
    Any program in the system PATH (ls, cat, grep) can be used.