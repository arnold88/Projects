Arnold Lee
CS 340 Program #3
read me

List of files:
Readme.txt (This read me file)
makefile (make file, if you compile under Linux environment)
block.cpp (block class implementation)
block.h  (block class declaration)
puzzle.cpp (puzzle class implementation)
puzzle.h (puzzle class declaration)
snapshot.cpp (snapshot class implementation)
snapshot.h (snapshot class declaration)
main.cpp  (main program)

How to compile:

In Linux: 

To compile, make sure all files in the same directory, and just run "make". the result file will be named puzzle.out
To run, enter "./puzzle.out" in command prompt.

In Windows: (MS Visual Studio 2008)

Create a solution and project object, and add all .h/.cpp files into the project, and then build the solution (F7 button). The result will be named after whatever name you give when you created the solution object at the beginning, plus a ".exe" extension. The executable will be located under the "debug" folder in your solution directory.

****************************************************************

How to use:

command:

./puzzle.out (-h)    <--- Linux

or

puzzle.exe (-h)   <---- Windows (depend on the name given to the Visual Studio project)

The optional -h flag indicates that you want an HTML output of the puzzle solution (in addition to on screen display). If some other characters or symbols are entered, the program will produce an error and it will not run.

You will be prompted to enter the file name of the input file. It is best to put the input files into same directory as the executable, then you don't have to put the full path name.

Note that for your convenience, the input data file is also included in the same zip file.
