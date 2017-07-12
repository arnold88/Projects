/*
Arnold Lee
CS 411 Project #2
Read Me
Date: 10/08/2010
*/

This zip file includes:

Readme.txt - this file
makefile - UNIX make file
puzzle.h - puzzle header file
puzzle.cpp - puzzle implementation
proj2.cpp - main program

How to compile:

In UNIX: copy all files including the make file, and type "make" at the prompt of the folder.

In Windows (VS 2010): Add the three source code files to the project, and build the program.

The output will be either ./proj2 (UNIX) or proj2.exe

The program will automatically look for "input.txt" from the same directory for the input file.

The program will write all directions to the file in "output.txt" from the source code directory.

The included excel file "report.xls" contains the report for the a* algotithm under two heuristics.

The first heurisitc is based on calculating the Manhanttan Distace, or city block distance.

The Second heuristic is based on calulating the diagonal / stright line distance.

Have fun!