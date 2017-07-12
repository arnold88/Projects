/*
this program relies on the BigInteger class and this program takes a line by line decimal representation
of a txt file and either encrypts/decrypts the ascii values
whether or not it is encryption or decryption is unknown 
all that is known is the key it is up to the user to supply the right key
if the same key is accepted twice it will encrypt the values twice or decrypt the values twice
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "BigIntegerLibrary.hh"
#include <math.h>
using namespace std;

/*
declarations of the functions that are going to be used in this progarm
*/
void parseComandLine(int & argc, char * argv[]);
void takeFileName(string & file);
void encryptDecrypt(string & readFile, string & key, string & writeFile);

/*
only need the comand lines from argv and the ammount of comands in argc
*/
int main(int argc, char * argv[])
{	
    parseComandLine(argc, argv);

    
    cout << "Hit any key to continue";
    cin.get();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

/*
This function is essentially the parse comand line from program 1 the inital program that created the keys
this function needs the comand line arguments
*/
void parseComandLine(int & argc, char * argv[])
{
    /*
    need these three strings as they will eventually be passed by reference to another function 
    the readFile is the file that needs to be encrypted/decrypted 
    the key is either the private or public key
    writeFile is where the encrypted/decrypted integer values will be written to
    */
    string readFile;
    string key;
    string writeFile;
    
    /*
    postfixed to the above strings in order to open the files using fstream
    txt is used for read and write files
    xml is used for key
    */
    string txtExtension = ".txt";
    string xmlExtension = ".xml";
    
    /*
    these three strings are used for comparison purposes they are the flags that are passed
    via the comand line
    */
    string oComand = "-o";
    string kComand = "-k";
    string fComand = "-f";
    
    /*
    these three are the flags if a comand line flag was passed
    if f and k comand are not found the program cannot complete
    o comand has a defualt case
    */
    bool oComandFound = false;
    bool kComandFound = false;
    bool fComandFound = false;
    
    /*
    used to get a yes or no option from the user
    */
    char yOrN;
    
    /*
    just temporary holders used for extraction their real purposes will be explained
    once they are reached in the code
    */
    stringstream temp;
    string temp1;
    string input;
    
    /*
    this for loop itterates thoughout the tokenized comandline
    remember argc is the value of how many tokens are in the comand line
    */
    for(int i = 0; i < argc; ++i)
    {
        /*
        string::compare(string) can not be used unless a string is given
        and an array of characters is not a string 
        so input is a temp position for argv[i] and this value input is used in the compare function
        compare if the strings are equal returns a 0 
        */
        input = argv[i];
        
        /*
        if the string "-o" is found
        */
        if(input.compare(oComand) == 0)
        {
            oComandFound = true;
            
            /*
            this means that there is another token after the -o flag and
            this token will be read in as the file to write to 
            */
            if(i+1 < argc)
            {
                /*
                take in the token as a stringstream and get the line with the delimeter
                being '.' this means if a user has already specified an
                extension this extension will be ignored and a new extension will be 
                appended in the end
                */
                temp << argv[i+1];
                getline(temp, temp1, '.');
                /*
                this clears temp for another use and makes sure the stream is empty
                */
                temp.clear();
                cout << "The file name choosen for the write file is: " << temp1 << endl << "Is this correct (y/n):";
                /*
                take a user input it either has to be y or n
                use the same idea as the stringstream and clear the cin stream 
                as well as the cin buffer 
                */
                yOrN = cin.get();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                /*
                if the value of the character is not 110 or 121 
                meaning a y or n this loop will ask until one of those is inputted
                */
                while(yOrN != 110 && yOrN != 121)
                {
                    cout << "The file name choosen is: " << temp1 << endl << "Is this correct (y/n):";
                    yOrN = cin.get();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                /*
                if the answer is no that means the input was wrong on the comand line
                takeFileName occurs and the use is allowed to enter in a new name for the -o comand
                */
                if(yOrN == 110)
                {
                    takeFileName(writeFile);
                    writeFile = writeFile + txtExtension;
                }
                
                /*
                if the answer is yes the name is posfixed with the proper extension and 
                writeFile is named 
                */
                if(yOrN == 121)
                {
                    temp1 = temp1 + txtExtension;
                    writeFile = temp1;
                    temp1.clear();
                    
                }
                
                /*
                since this value has already been taken care of input is incremented to the next value
                and so is i to make up for input being incremented
                */
                input = argv[i+1];
                ++i;
                
                /*
                if -o -k file1 was given the name of the file would have been -k
                this makes sure that a file name can't be a comand argument
                in reality there is no reason you can't name your file 
                -k.txt but not in this case
                */
                if(input.compare(kComand) == 0 || input.compare(fComand) == 0)
                {
                    cout << "The name taken was the same as a comand line flag." << endl;
                    takeFileName(writeFile);
                    writeFile = writeFile + txtExtension;
                }
                temp1.clear();
            }
        }
        
        /*
        f and k follow the exact same coding as the oComand literally the only changes are to the variables that are changed
        */
        if(input.compare(fComand) == 0)
        {
            fComandFound = true;
            if(i+1 < argc)
            {
                cout << argv[i+1]<< endl;
                
                temp << argv[i+1];
                cout << temp << endl;
                getline(temp, temp1, '.');
                temp.clear();
                cout << "The name for the file to be encrypted/decrypted is: " << temp1 << endl << "Is this correct (y/n):";
                yOrN = cin.get();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while(yOrN != 110 && yOrN != 121)
                {
                    cout << "The name for the file to be encrypted/decrypted is: " << temp1 << endl << "Is this correct (y/n):";
                    yOrN = cin.get();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                if(yOrN == 110)
                {
                    takeFileName(readFile);
                    readFile = readFile + txtExtension;
                }
                
                if(yOrN == 121)
                {
                    temp1 = temp1 + txtExtension;
                    readFile = temp1;
                }
                
                input = argv[i+1];
                ++i;
                
                if(input.compare(fComand) == 0 || input.compare(oComand) == 0)
                {
                    cout << "The name taken was the same as a comand line flag." << endl;
                    takeFileName(readFile);
                    readFile = readFile + txtExtension;
                }
            }
            temp1.clear();
        }
        
        /*
        for reference look at the block for the o comand flag
        */
        if(input.compare(kComand) == 0)
        {   
            kComandFound = true;
            if(i+1 < argc)
            {
                temp << argv[i+1];
                getline(temp, temp1, '.');
                temp.clear();
                cout << "The file name for the key is: " << temp1 << endl << "Is this correct (y/n):";
                yOrN = cin.get();
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while(yOrN != 110 && yOrN != 121)
                {
                    cout << "The file name for the key is: " << temp1 << endl << "Is this correct (y/n):";
                    yOrN = cin.get();
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                
                if(yOrN == 110)
                {
                    takeFileName(key);
                    key = key + xmlExtension;
                }
                
                if(yOrN == 121)
                {
                    temp1 = temp1 + xmlExtension;
                    key = temp1;
                    temp1.clear();
                }
                
                input = argv[i+1];
                ++i;
                
                if(input.compare(kComand) == 0 || input.compare(oComand) == 0)
                {
                    cout << "The name taken was the same as a comand line flag." << endl;
                    takeFileName(key);
                    key = key + xmlExtension;
                }
            }
            temp1.clear();
        }
    }
	
	/*
	if there was no k comand given the file names need to be asked for
	in order for the program to advance
	*/
	if(!kComandFound)
	{
		cout << "No key was given for encryption/decryption." << endl;
		takeFileName(key);
		key = key + xmlExtension;
	}
	
	/*
	as with the k comand the f comand is a requirment to continue the encryption/decryption
	process so this manually asks for the readFile name
	*/
	if(!fComandFound)
	{
		cout << "No file was given to be encrypted/decrypted." << endl;
		takeFileName(readFile);
		readFile = readFile + txtExtension;
	}
	
	/*
	if no o flag was given the file is automatically named 
	(readFile name)NEW.txt
	so it depends on the name that was given to readFile
	*/
	if(!oComandFound)
	{
		writeFile = readFile.substr(0, readFile.length()-4) + "NEW" + txtExtension;
		
	}
	
    encryptDecrypt(readFile, key, writeFile);
};


/*
this just asks the user for a string that will correspond to the file in question
the files are denoted by a statement given before this function is called
*/
void takeFileName(string & file)
{
    /*
    all temporary place holders
    need two stringstreams and 2 inputs to store
    */
    string input0;
    string input1;
    stringstream fileName;
    stringstream fileName1;
    char answer;
    
    
    while(answer != 121)
    {
        cout << "Please give the name for the file:" << endl;
    
        getline(cin, input0);
        
        /*
        the first block breaks apart the stream in order to get a string that has no spaces
        */
        fileName << input0;
        getline(fileName, input0, ' ');
        cin.clear();
        fileName.clear();
        fileName.ignore(numeric_limits<streamsize>::max(), '\n' );
        
        /*
        the second block breaks apart the stream and removes any extensions
        this results in just the name
        */
        fileName1 << input0;
        getline(fileName1, input0, '.');
        fileName1.clear();
        fileName1.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "You inputed the file name: " << input0 << endl << " Is this correct (y/n):";
        cin.get(answer);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        while(answer != 110 && answer != 121)
        {
            cout << "You inputed the file name: " << input0 << endl << " Is this correct (y/n):";
            cin.get(answer);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    /*
    set the file to input0 and clear everything 
    */
    file = input0;
    input0.clear();
    input1.clear();
    fileName.clear();
    fileName1.clear();
    cin.clear();
};

/*
after all the files have been accounted for this function actually does the encryption/decryption
*/
void encryptDecrypt(string & readFile, string & key, string & writeFile)
{   
    /*
    all temp values that are used for comparison
    temp is set to hold the cstr that is key once it is converted
    */
    char * temp;
    temp = new char [key.size() + 1];
    strcpy (temp, key.c_str()); 
    string tempHolder;
    string tempCompare;
    
    /*
    m is the value to encrypt e d and n are the key values
    */
    BigInteger m = 0;
    BigUnsigned e = 0;
    BigUnsigned d = 0;
    BigUnsigned n = 0;
    
    /*
    e or d number is the value in either e or d only one can be true at a time
    */
    char * edNumber;
    
    /*
    open up a ifstream with the name temp
    then delete the pointer because it will not be needed anymore
    */
    ifstream fileToRead(temp);
    delete [] temp;
    
    /*
    make sure the file is open
    */
    if (fileToRead.is_open())
    {
        /*
        while this is not the end of the file read in lines of the 
        xml key file
        */
        while (!fileToRead.eof())
        {
            getline(fileToRead, tempHolder);
            /*
            if the key is not in the specified xml format for the project no values will be returned and the function will end with
            out anything being encrypted/decrypted
            */
            for (int i = 0; i < tempHolder.length(); ++i)
            {
                /*
                if a '<' is found then there is a chance it is one of the tags the function needs 
                all the tags have length of 8 so once a < is found the function takes the substring 
                starting at that index and looks to see if it is the proper tag 
                and then sets teh BigInteger or BigUnsigned to the proper variable
                */
                if(tempHolder[i] == '<')
                {
                    tempCompare = tempHolder;
                    tempCompare = tempCompare.substr(i, 8);
                    if(tempCompare.compare("<dvalue>") == 0)
                    {
                        tempHolder = tempHolder.substr(i+8, tempHolder.length());
                        edNumber = new char [tempHolder.size()+1];
                        strcpy (edNumber, tempHolder.c_str());
                        d = atoi(edNumber);
                        delete [] edNumber;
                    }
                
                    if(tempCompare.compare("<evalue>") == 0)
                    {
                        tempHolder = tempHolder.substr(i+8, tempHolder.length());
                        edNumber = new char [tempHolder.size()+1];
                        strcpy (edNumber, tempHolder.c_str());
                        e = atoi(edNumber);
                        delete [] edNumber;
                    }
                
                    if(tempCompare.compare("<nvalue>") == 0)
                    {
                        tempHolder = tempHolder.substr(i+8, tempHolder.length());
                        edNumber = new char [tempHolder.size()+1];
                        strcpy (edNumber, tempHolder.c_str());
                        n = atoi(edNumber);
                        delete [] edNumber;
                    }
                }
            }
        }
        
	}
	else
	{
		cout << "The key file was not correct." << endl;
	}
        
	/*
	close and clear the file
	*/
	fileToRead.close();
	fileToRead.clear();
	
	/*
	the function now needs the file to encrypt/decrypt once again temp is used
	once the file is ifstream is set the pointer temp is deleted
	*/
	temp = new char [readFile.size() + 1];
	strcpy (temp, readFile.c_str()); 
	fileToRead.open(temp);
	delete [] temp;
	
	/*
	this block of code opens the write file and this is where the encrypted/decrypted int values will be stored
	*/
	temp = new char [writeFile.size() + 1];
	strcpy (temp, writeFile.c_str()); 
	ofstream fileToWrite(temp);
	delete [] temp;
	
	/*
	both files need to be opened in order for this to work and this if statment makes sure this is the case
	*/
	if(fileToRead.is_open() && fileToWrite.is_open())
	{
		/*
		pow is the value to which m is going to be raised
		as stated it is only possible to have either e or d as the value
		and if it is the case that both e and d are 0 meaning not a valid key was
		given the program will end without working encrypting or decrypting
		*/
		BigUnsigned pow;
		if(e > 0)
		{
			pow = e;
		}
		
		if(d > 0)
		{
			pow = d;
		}
		
		/*
		while not the end of the read file the integer is extracted
		into ednumber then the atoi function is used to set m = to its proper value
		edNumber is just reused from the key code so a new pointer would not have to be initilized
		the the files are written with the use of the modexp() function for big int 
		this function can be found in the big int readme
		*/
		while(!fileToRead.eof())
		{
			getline(fileToRead, tempHolder);
			edNumber = new char [tempHolder.size()+1];
			strcpy (edNumber, tempHolder.c_str());
			m = atoi(edNumber);
			delete [] edNumber;
			
			fileToWrite << modexp(m, pow, n) << endl;
		}
		
		cout << "The values were written to the txt file " << writeFile << "." << endl;
		
	}
	/*
	the function ends and the user has to restart the program
	*/
	else
	{
		cout << "A file was inputted incorrectly for reading." << endl;
	}
	
	fileToRead.close();
	fileToWrite.close();
        
};
