User Manual

Shell:
    the command-line interface (CLI) program that takes human commands and parses them for the operating system to execute.

Interactive mode:
    User dynamically types in commands, and shell processes and executes them.

Batch mode:
    User passes a file that contains a set of commands to the shell.

To start using the shell:
    1. compile
    2. run in interactive mode or
    3. run in batch mode

Compile the shell
    go into Stage1 directory
    run "make".

To run the shell in interactive mode:
    run ./bin/simpleshell
    or go into bin directory and run ./simpleshell

To run the shell in batch mode:
    run ./bin/simpleshell batchFile.txt
    or go into bin directory and run ./simpleshell batchFile.txt

To delete the binary file (recommended if you want to keep your directories clean)
    make clean


Available commands:

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
    list all the environment strings
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

