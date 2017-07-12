Name: Arnold Lee
CS Account ID: temp109
    


STATSH V1.1 DOCUMENTATION

To compile type:

g++ statsh.cpp -Wno-deprecated -o statsh

To execute the shell type:

./statsh




The shell will accept any standard UNIX command that has external executeables (i.e. "cd" command are NOT supported).

Type EXIT (in all CAPS) to exit the shell at when at prompt, or press CTRL + Z to exit the shell at any process.

Type "stats" to see the time that were used by last process in seconds (if any).

**********************************************
KNOWN ISSUES
**********************************************

You will have only one directory to work with. You cannot change the directory.

Multiple commands in a single line are supported with the pipe symbol "|", but communication between those commands/processes are NOT supported.

File I/O are not supported.

Backspace button are not supported.

You are only allow to use 1001 commands in a single line ( 1000 pipe symbol allowed in a single command).

You are only allow to use 1000 spaces in a single line.

When reading manuals or large texts, use only the arrow key to scroll up or down. DO NOT USE THE 'ENTER' KEY TO SCROLL DOWN. It may cause unnecessary newline characters and interfere with future prompts.

Failure to adhere the above constraints may result in segmentation fault at any time.

This product are given "as-is", without any warranty. The author is not responsible for any misuse of this product.

 
