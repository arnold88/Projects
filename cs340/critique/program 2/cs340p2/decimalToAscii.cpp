/*
This is the inverse of ascii to decimal
this converts a line by line decimal file back to a legible ascii file spacing and all
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include<iomanip>
using namespace std;

void convertDecimalToAscii();

int main()
{
    convertDecimalToAscii();
    
    cout << "Hit any key to continue";
    cin.get();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return 0;
};
/*
take a line by line decimal file
*/
void convertDecimalToAscii()
{
    cout << "Enter the name of the file you wish to convert to ascii." << endl <<
    "This file needs to be a .txt file this program just needs the name of the file." << endl <<
    "If an incorrect file name is entered the program will prompt for another one." << endl;
    
    /*
    this is a mimic of asciiToDecimal and does the same thing up until the loop to write
    */
    cout << "Input the name of the file: ";
    string extension = ".txt";
    string fileName;
    string line;
    string newName = "Decimal.txt";
    string newName1 = "Ascii.txt";
    stringstream deleteExtension(stringstream::in | stringstream::out);
    char * name;
    
    getline(cin, fileName);
        
    deleteExtension << fileName;
    getline(deleteExtension, fileName, '.');
    
    //deleteExtension.ignore(numeric_limits<streamsize>::max(), '\n' );
    deleteExtension.clear();
        
    fileName = fileName + extension;
    name = new char [fileName.size()+1];
    strcpy (name, fileName.c_str());
    
    ifstream readFile(name);
    
    while(!readFile.is_open())
    {
        readFile.close();
        readFile.clear();
        delete name;
        cout << "Input the name of the file: ";
        
        getline(cin, fileName);
        
        deleteExtension << fileName;
        getline(deleteExtension, fileName, '.');
    
        deleteExtension.ignore(numeric_limits<streamsize>::max(), '\n' );
        deleteExtension.clear();
        
        fileName = fileName + extension;
        
        name = new char [fileName.size()+1];
        strcpy (name, fileName.c_str());
        
        readFile.open(name);
    }
    
    deleteExtension << fileName;
    getline(deleteExtension, fileName, '.');
    
    deleteExtension.ignore(numeric_limits<streamsize>::max(), '\n' );
    deleteExtension.clear();
    
    fileName = fileName + newName1;
    
    name = new char [fileName.size()+1];
    strcpy (name, fileName.c_str());
    
    ofstream writeFile(name);
    
    cout << "The ascii conversion will be written to: " << name << endl;
    
    delete name;
    
    /*
    no new lines are printed just the 
    atoi value of the line is taken and inputted as a character
    */
    if(readFile.is_open())
    {
        int decimal;
        char character;
        while(!readFile.eof())
        {
            getline(readFile, line);
            name = new char [line.size()+1];
            strcpy (name, line.c_str());
            character = atoi(name);
            delete name;
            writeFile << character;
        }
        
    }
    
    
};
