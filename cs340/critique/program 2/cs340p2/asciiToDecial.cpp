/*
this program converts a file into from a standard text file
to a line by line representation of the ascii characters to their corresponding decimal values
the corresponding decimal values are stored line by line
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include<iomanip>
using namespace std;

void convertAsciiToDecimal();

int main()
{
    convertAsciiToDecimal();
    
    
    cout << "Hit any key to continue" << endl;
    cin.get();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return 0;
};

/*
this fucntion will promt the user for a valid file until the user gives a valid 
file if the user never does the function never ends
*/
void convertAsciiToDecimal()
{
    cout << "Enter the name of the file you wish to convert to decimal." << endl <<
    "This file needs to be a .txt file this program just needs the name of the file." << endl <<
    "If an incorrect file name is entered the program will prompt for another one." << endl;
    
    /*
    used for temporary values the cout is just a statement of course
    */
    cout << "Input the name of the file: ";
    string extension = ".txt";
    string fileName;
    string line;
    string newName = "Decimal";
    stringstream deleteExtension(stringstream::in | stringstream::out);
    char * name;
    
    /*
    get the name fo th file and unappend the extension
    this program does not care about wether or not there are spaces because the 
    file acutally needs to open otherwise nothing ever will be completed
    */
    getline(cin, fileName);
        
    deleteExtension << fileName;
    getline(deleteExtension, fileName, '.');
    
    deleteExtension.ignore(numeric_limits<streamsize>::max(), '\n' );
    deleteExtension.clear();
    
    /*
    this then appends the txt extension onto the file this is the only option for the file to be converted
    and makes it easier on the user not needing to know the extension 
    */    
    fileName = fileName + extension;
    name = new char [fileName.size()+1];
    strcpy (name, fileName.c_str());
    
    ifstream readFile(name);
    
    /*
    while the file is not open continue to ask the user for a new file
    */
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
    
    /*
    once again the extension is removed this is so the newName can be inserted
    in this case it will be (file name)Decimal.txt
    */
    cout << fileName << endl;
    deleteExtension << fileName;
    getline(deleteExtension, fileName, '.');
    
    deleteExtension.ignore(numeric_limits<streamsize>::max(), '\n' );
    deleteExtension.clear();
    
    fileName = fileName + newName + extension;
    
    name = new char [fileName.size()+1];
    strcpy (name, fileName.c_str());
    
    ofstream writeFile(name);
    
    cout << "The decimal conversion will be written to: " << name << endl;
    
    delete name;
    /*
    whlie the file to read is open and not at the end
    the writeFile is updated a 10 is inserted after every line
    the value 10 represents a new line character
    and since getline does not actually read in the new line character
    this has to be manually inserted 
    */
    if(readFile.is_open())
    {
        int decimal;
        while(!readFile.eof())
        {
            getline(readFile, line);
            for(int i = 0; i < line.length(); ++i)
            {
                decimal = line[i];
                writeFile << decimal << endl;
            }
            writeFile << "10" << endl;
        }
        
    }
    readFile.close();
    writeFile.close();
    
};
