/*
The job of this program is to read in the comand line and parse it then act accordingly
The comand line in this program needs at least one flag that is the -c flag this will generate two 
random prime numbers that are not equal in value yet the program is able to handle up to 5 flags
2 ints -o (2 names for the files)
This program is part of a set of programs that operate in conjuction in order to encrypt and decrypt a text file 
using an rsa algorithim
this is the first of four programs and its job is to generate the prime numbers that will be used for encryption
and decryption and then write them to a file for the next program to use
if the comand line is illegible or nothing is present the files have a defualt position to be written to 
but prompts for the user appear in order to generate the prime numbers needed for the program to finish
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

/*
this block of code just declares the prototypes for the functions in the program
this is done so that a function will have the ability to call another function regardless
of its position in the code 
All four functions will be explained once reached.
*/
void parseComandLine(int argc, char * argv[]);
bool checkForPrime(int x);
void createRandomPrime(int & prime1, int & prime2);
void takeUserInput(int & prime1, int & prime2);
void takeFileNames(string & file1, string & file2);
void writeToFile(int & prime1, int & prime2, string & file1, string & file2);
int findGCD(int x, int y);

/*
main takes in two arguments these arguments come from the command line initially and are altered as
needed if the origional inputs on the comand line were wrong
one int and one char* [] is needed in order for the program to take inputs off the comand line
the pointer to the arrays is a pointer to a pointer or can be thought of as a 2d array 
argv is a tokenized list of strings with the delimeter between each token being a space
i.e. -c asdf 1234 4321 ;was entered on the the comand line there would be a total of 5 tokens
space 0 is reserved for the address of the program so "-c" is stored as token 1
argc is default 1 to hold the defualt position and tells how many objectes the pointer points to
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
This function takes the input off of the command line and passes it by reference
pass by refernce is done because if the input on the command line is incorrect the function needs to
redefine the inputs this could be done with a return statement but this allows for only 
one return at a time whereas by passing by reference the function is able to change both inputs in one shot
*/
void parseComandLine(int argc, char * argv[])
{
    /*
    the fisrt strings are created in ordrer to use the .compare function of the string library
    
    string input and string input1 are used for typecasting purposes
    a string is an arrray of characters but the .compare function does not work with an array of characters
    if an array of characters is typecasted into a string all the functions can be used
    
    then the three bool values are used as flags to tell whether or not a value has been found
    */
    string createRandom = "-c";
    string createFileName = "-o";
    string input;
    string input1;
    char input3 = 'n';
    stringstream fileName2(stringstream::in | stringstream::out);
    stringstream fileName3(stringstream::in | stringstream::out);
    bool cComandFound = false;
    bool oComandFound = false;
    bool primeFound = false;
    bool filesNamed = false;
    
    int prime1;
    int prime2;
    string file1 = "pubkey";
    string file2 = "prikey";
    
    /*
    starting at position 0 of argv every subString is read in substring's are denoted by the ' ' between a string
    */
    for(int i = 0; i < argc; i++)
    {
        /*
        as stated argv is a double pointer or an array or arrays yet since it is an array of characters
        the array of characters can be stored in a string and then the .compare can be used upon the substring
        */
        input = argv[i];
        
        /*
        if the -c flag iz found (.compare(string) returns 0) then set the cComandFound flag to true
        and increment the for loop as this substring is -c and can be nothing else
        */
        if(input.compare(createRandom) == 0 && i < argc)
        {
            cComandFound = true;
        }
        
        /*
        since the loop is incremented inside of these if statements each statement has to make sure that i is
        not out of bounds as there is the possibility that i is outOf bounds for argv
        */
        if(input.compare(createFileName) == 0 && i < argc)
        {
            oComandFound = true;
            if(i < argc - 2)
            {
                
                file1 = argv[i+1];
                
                fileName2 << file1;
                getline(fileName2, file1, '.');
                fileName2.clear();
                fileName2.ignore(numeric_limits<streamsize>::max(), '\n' );
                
                file2 = argv[i+2];
                
                fileName3 << file2;
                getline(fileName3, file2, '.');
                fileName3.clear();
                fileName3.ignore(numeric_limits<streamsize>::max(), '\n' );
				
		        cout << "You entered " << file1 << " for the public key." << endl << file2 << " for the private key."
		        << endl << "Is this correct (y/n):";
		        
		        cin >> input3;
		        while(input3 != 110 && input3 != 121)
		        {
                    cout << "(y/n):";
                    cin >> input3;
                }
                
                if(input3 == 110)
                {
                    cin.get();
                    takeFileNames(file1, file2);
                }
				
                filesNamed = true;
                
                if(file1.compare(file2) == 0)
                {
                    cout << "The parameters for -o had the same name" << endl;
                    cin.get();
                    takeFileNames(file1, file2);
                    filesNamed = true;
                }
            }
            
            else
            {
                cout << "-o flag was found missing parameters." << endl;
                takeFileNames(file1, file2);
                filesNamed = true;
            }
        }
    }
    
    /*
    following the checks for -o and -c the this function starts a new loop that looks for 
    manual user input of prime numbers if both -c and prime numbers are found an error is reported
    and the program promts the user for new inputs as the values can not be both known and random
    */
	int numbersToCheck[2];
	int counter = 0;
	for(int i = 0; i < argc; ++i)
	{
        /*
        while looking for numbers if the -o flag is found the next two positions after wards are skipped
        as these are the names of files not valid for the atoi conversion the file 1key.txt atoi would give 1 
        and this would not be the expected value so if this is the case two values are skipped
        the -o flag was already checked for proper use
        */
        
        input = argv[i];
        if(input.compare(createFileName) == 0)
        {
            i = i+3;
        }
        
        /*
        if i find something that is greater than 0 after using atoi it is then checked
        character by character to make sure there are no anomalys in the number such as 1234a whilch
        atoi(1234a) would result in the number 1234 
        the prefix of characters to a number results in an atoi of zero
        */
		if(i < argc && atoi(argv[i]) > 128)
		{   
            string test;
            test = argv[i];
            for(int j = 0; j < test.length(); ++j)
            {
                if(argv[i][j] > 57 || argv[i][j] < 48)
                {
                    cout << "An unexpected character was appended to a number." << endl;
                    i = argc;
                    j = test.length();
                    cComandFound = false;
                    counter = 0;
                }
            }
            
			if(i < argc && counter < 3)
			{
				numbersToCheck[counter] = atoi(argv[i]);
			}
			
			if(i < argc)
			{
                ++counter;
            }
		}
	}
	
	/*
	the c comand was found and there were no numbers inputted
	so random numbers will be generated
	*/
	if(cComandFound && counter == 0)
    {   
        cout << "The -c flag was found and random numbers will be generated." << endl;
        createRandomPrime(prime1, prime2); 
    }
	
	if(!cComandFound && counter ==0)
	{
        cout << "Not enough prime numbers over 128 were found." << endl;
        takeUserInput(prime1, prime2);
    }
	
	/*
	two entries were found and they were numbers and there was no c comand 
	therefore the numbers have to be checked to make sure they are greater than 128
	they are not equal in value and that they are prime
	if they both turn ut to be prime then the numbers are stored into the parameters passed origionally
	into the function which would be prime1 and prime2 if an unprime number is found the function 
	then calles another function to ask the user for new numbers
	*/
	if(counter == 2 && !cComandFound)
	{
		counter = 0;
		int number = 0;
		for(int i = 0; i < 2; ++i)
		{
			number = numbersToCheck[i];
			if(!checkForPrime(number))
			{
				cout << "A number inputted was not prime." << endl;
				takeUserInput(prime1, prime2);
				primeFound = true;
			}
			
		}
		
		if(!primeFound)
		{
			prime1 = numbersToCheck[0];
			prime2 = numbersToCheck[1];
        }
	}
	
	
	/*
	if there was a maulual input and the c comand then run takeUserInput
	*/
	else if(counter > 0 && cComandFound)
	{
		cout << "The -c flag and integer values were found." << endl;
		takeUserInput(prime1, prime2);
	}
	
	writeToFile(prime1, prime2, file1, file2);
};



/*
check for prime returns false is a number is not prime and true is a number is prime
simply enough a loop is done that makes sure a number is not divisible by anything other than 1 and itself
*/
bool checkForPrime(int x)
{
    int counter = 0;
	
	if(x < 128)
	{
		return false;
	}
	
	for(int i = x; i > 0; --i)
	{
		if(x%i == 0)
		{
			++counter;
		}
		
		if(counter > 1 && i != 1)
		{
			return false;
		}
	}
	
	return true;
};

void takeFileNames(string & file1, string & file2)
{
    
    string input0;
    string input1;
    stringstream fileName(stringstream::in | stringstream::out);
    stringstream fileName1(stringstream::in | stringstream::out);
    char answer;
    while(answer != 121)
    {
        cout << "Please enter the file name for the public key." << endl;
        
        getline(cin, input0);
        
        fileName << input0;
        
        getline(fileName, input0, ' ');
        
        cin.clear();
        fileName.clear();
        fileName.ignore(numeric_limits<streamsize>::max(), '\n' );
        
        fileName1 << input0;
        
        getline(fileName1, input0, '.');
        
        fileName1.clear();
        fileName1.ignore(numeric_limits<streamsize>::max(), '\n' );
        
        cout << "You inputed the file name: " << input0 << endl << " Is this correct (y/n):";
        cin.get(answer);
        
        while(answer != 110 && answer != 121)
        {
            cout << "You inputed the file name: " << input0 << endl << " Is this correct (y/n):";
            cin >> answer;
        }
        
        if(answer == 110)
        {
            input0.clear();
            input1.clear();
            fileName.clear();
            cin.clear();
            fileName1.clear();
        }
        cin.get();
    }
    
    file1 = input0;
    answer = 'n';
    input0.clear();
    input1.clear();
    fileName.clear();
    fileName1.clear();
    cin.clear();
    
    while(answer != 121)
    {
        cout << "Please enter the file name for the private key." << endl;
        
        getline(cin, input0);
        
        fileName << input0;
        
        getline(fileName, input0, ' ');
        
        cin.clear();
        fileName.clear();
        fileName.ignore(numeric_limits<streamsize>::max(), '\n' );  
        
        fileName1 << input0;
        
        getline(fileName1, input0, '.');
        
        fileName1.clear();
        fileName1.ignore(numeric_limits<streamsize>::max(), '\n' );
        
        cout << "You inputed the file name: " << input0 << endl << " Is this correct (y/n):";
        cin >> answer;
        
        while(answer != 110 && answer != 121)
        {
            cout << "You inputed the file name: " << input0 << endl << " Is this correct (y/n):";
            cin >> answer;
        }
        
        if(file1.compare(input0) == 0)
        {
            cout << "The file name for the private key is the same as the public key." << endl;
            answer = 'n';
        }
        
        if(answer == 110)
        {
            input0.clear();
            input1.clear();
            fileName.clear();
            fileName1.clear();
            cin.clear();
        }
        cin.get();
    }
    
    file2 = input0;
}

/*
using an array of prime numbers that are greater than 128 and less than 500
two numbers are choosen out of the list at random and are stored into prime1 and prime2
*/
void createRandomPrime(int & prime1, int & prime2)
{
    int randomPrime[] = {131, 137, 139, 149, 151, 157, 163, 167, 173, 
                         179, 181, 191, 193, 197, 199, 211, 223, 227, 
                         229, 233, 239, 241, 251, 257, 263, 269, 271, 
                         277, 281, 283, 293, 307, 311, 313, 317, 331, 
                         337, 347, 349, 353, 359, 367, 373, 379, 383, 
                         389, 397, 401, 409, 419, 421, 431, 433, 439, 
                         443, 449, 457, 461, 463, 467, 479, 487, 491, 499};
                        
    int primeNumbers[2];
    srand(time(NULL));
    for(int i = 0; i < 2; i++)
    {
        int random = rand()%64;
        primeNumbers[i] = randomPrime[random];
        if(i == 1)
        {
            while(primeNumbers[0] == primeNumbers[1])
            {
                random = rand()%64;
                primeNumbers[1] = randomPrime[random];
            }
        }
    }
    
    prime1 = primeNumbers[0];
    prime2 = primeNumbers[1];
};

/*
easy enough this is just the euclidian method to calculating the gcd
the gcd does not change if two numbers are subtracted from one another
as long as the small is subtracted from the larger when the value of one number
reaches 0 the remaing value in the other number is the gcd
*/
int findGCD(int x, int y)
{
    while(x != 0 && y != 0)
    {
        if(x > y)
        {
            x = x-y;
        }
        
        if(y > x)
        {
            y = y-x;
        }
        
        if(y == x)
        {
            y = y - x;
        }
    }
    
    if(y == 0)
    {
        return x;
    }
    
    if(x == 0)
    {
        return y;
    }
};

/*
all the values have been taken prime1 prime2 file1 and file2
file1 corresponds to the pubkey
and file2 corresponds to the prikey
essentially either can be a pubkey or pri key but this is just the setup
if the user wishes to keep the pubkey and give out the prikey then so be it
the names are just names 
*/
void writeToFile(int & prime1, int & prime2, string & file1, string & file2)
{
	unsigned long n = prime1 * prime2;
	unsigned long theta = (prime1 - 1) * (prime2 -1);
	unsigned long e;
    unsigned long d = 1;
    string extension = ".xml";
    file1 = file1 + extension;
    file2 = file2 + extension;
	
	e = 2;
	
	/*
	need to find a value e so that it is relativly prime to theta
	this is for rsa encryption if the gcd is 1 a value has been found
	*/
	while(findGCD(e, theta) != 1 && e < n)
	{
        ++e;
    }
    
    /*
    d occurs when this function is met
    */
    while((e*d)%theta != 1)
    {
        ++d;
    }
    
    /*
    just temp pointers for openeing the files
    */
    char * temp, * temp1;
    temp = new char [file1.size() + 1];
    strcpy (temp, file1.c_str()); 
    
    ofstream pubKey (temp);
    delete [] temp;
    /*
    once the file is open the key is printed out in xml format and given an xml
    extension
    */
    if (pubKey.is_open())
    {
        pubKey << "<rsakey>" << endl <<
                  "     <evalue>" << e << "</evalue>" << endl << endl <<

                  "     <nvalue>" << n << "</nvalue>" << endl <<
                  "</rsakey>" << endl;
        pubKey.close();
    }
    /*
    if the file can not be opened the file is not written to and the program ends without doing this
    */
    else
    { 
        cout << "Unable to open file 1";
    }
    
    /*
    same as above just done so ofstream can be initilized
    same print function as well
    */
    temp1 = new char [file2.size() + 1];
    strcpy (temp1, file2.c_str());
    
    ofstream priKey (temp1);
    delete [] temp1;
    if (priKey.is_open())
    {
        priKey << "<rsakey>" << endl <<
                    "     <dvalue>" << d << "</dvalue>" << endl << endl <<

                    "     <nvalue>" << n << "</nvalue>" << endl <<
                 "</rsakey>" << endl;
        priKey.close();
    }
    else
    { 
        cout << "Unable to open file 2";
    }
    
};

/*
take user input manually handles the user and gets two prime numbers by force 
an infinite loop of questions will occur if a prime number is never entered 
at first the function gives the option of manual entering if that is choosen
the createRandom function is called if the user want to enter numbers manually
the function asks the user for one number at a time and checks to see whether or not
the number is prime as it is entered if the number is not prime the function asks the user
for a new prime number as the old one was not prime
once one number is entered the 2nd number is asked for
the 2nd number goes through the same process as the first number and is checked on the spot 
as to whether or not it is prime if it is not once again the prompt will come up but this time
for the 2nd number
once again if a number 1234a is entered an invalid statement will appear because the number is posfixed with a
*/
void takeUserInput(int & prime1, int & prime2)
{
    cout << "Do you wish to have two prime numbers generated for the key?" << endl;
    char input;
    prime1 = 0;
    prime2 = 0;
    string primeInput;
    while(input != 110 && input != 121)
    {
        cout << "(y/n):";
        cin >> input;
        if(input == 110)
        {
            cout << "Input one prime number at a time." << endl;
            while(prime1 < 1)
            {
                cout << "Input 1: ";
                cin >> primeInput;
                string temp1;
                getline(cin, temp1);
                primeInput = primeInput + temp1;
                char temp[primeInput.length()];
                for(int i = 0; i < primeInput.length(); ++i)
                {
                    temp[i] = primeInput[i];
                    
                    if(i == primeInput.length()-1)
                    {
                        prime1 = atoi(temp);
                    }
                    
                    if(primeInput[i] > 57 || primeInput[i] < 48)
                    {
                        cout << "There was an unexpected character in the input." << endl;
                        i = primeInput.length();
                        prime1 = 0;
                    }
                }
				
				if(!checkForPrime(prime1))
				{
                    cout << "The number choosen was not prime."  << endl;
					prime1 = 0;
				}
            }
            
            while(prime2 < 1)
            {
                cout << "Input 2: ";
                cin >> primeInput;
                string temp1;
                getline(cin, temp1);
                primeInput = primeInput + temp1;
                char temp[primeInput.length()];
                for(int i = 0; i < primeInput.length(); ++i)
                {
                    temp[i] = primeInput[i];
                    
                    if(i == primeInput.length()-1)
                    {
                        prime2 = atoi(temp);
                    }
                    
                    if(primeInput[i] > 57 || primeInput[i] < 48)
                    {
                        cout << "There was an unexpected character in the input." << endl;
                        i = primeInput.length();
                        prime2 = 0;
                    }
                }
				
				if(!checkForPrime(prime2))
				{
                    cout << "The number choosen was not prime." << endl;
					prime2 = 0;
				}
            } 
		}
		
        if(input == 121)
        {
            cout << "The prime numbers have been generated." << endl;
            createRandomPrime(prime1, prime2);
        }
    }
    
};




