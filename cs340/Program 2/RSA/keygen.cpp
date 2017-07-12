/*
Arnold Lee
CS 340 Program #2
UIN:665453451
Public/Private Key Pair Generation Program - Main Module
Date: 02/02/2010
*/

//note: still need to fix arguments

#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace std;

void error_message(int);
void random_gen (int &,int &);
bool prime_verify (int);
void prime_entry (int &,int &);
long long gcd (long long,long long);


int main(int argc, char *argv[])
{
    
	int p,q;
	string pub_file,pri_file,temp;
	ofstream pub,pri;
	unsigned long long n,t;
	unsigned long long e,d;
	bool file_name_given(false);
	int file_name_index(0);
	bool random(false);
	
	
	 // entering argument processing
	
	       if (argc == 1) // no argument entered, all default setting
		   {
              prime_entry(p,q);   
			  pub_file = "pubkey.txt";
			  pri_file = "prikey.txt";

		   }
		   else
		   {
				for (int i = 0; i < argc; i++)
				{
					temp = argv[i];

					if (temp == "-c")
					{
						random = true;
                        cout << "random mode" << endl;

					}

					if (temp == "-o")
					{
						file_name_given = true;
						file_name_index = i;
						cout << "file name given" << endl;
					}

				}
				
				// get the file name
				if ( (argc - file_name_index) < 3 && file_name_given)
				{
					  error_message(1);
					  return 0;
				}
				else if (file_name_given)
				{
					pub_file = argv[file_name_index+1];
					pri_file = argv[file_name_index+2];
				}
				else
				{
					pub_file = "pubkey.txt";
					pri_file = "prikey.txt";

				}


				// now get the prime number
				if (random)
				{
				   random_gen(p,q);
				}
				else
				{
                    if (file_name_given)
					{
                       if (file_name_index == 3)
					   {
                           p=atoi(argv[1]);
						   q=atoi(argv[2]);

					   }
					   else if (file_name_index == 1)
					   {
                         if (argc > 4)
						 {
                           p=atoi(argv[4]);
						   q=atoi(argv[5]);
						 }
						 else
						 {
                              prime_entry(p,q);
						 }

					   }
					}
					else 
					{
						if (argc == 3)
						 {
                           p=atoi(argv[1]);
						   q=atoi(argv[2]);
						 }
						else if (argc == 2)
						{
							error_message(2);
							return 0;
						}
						else if (argc == 1)
						{
                            prime_entry(p,q);
						}
					}
				}
				

            

		   } // end argument processing
	  
    // Enter key generation stage

   
    // calculate n,t
	n = p * q; 
    t = (p - 1) * (q - 1);

    // now find e

	for (unsigned long long x = n - 1; x > 0 ; x--)
	{    
          if (gcd(x,t) == 1) 
		  {
               e = x; // e found, break out of 'for' loop
			   break;
		  }
    }

	// now find d
    
	d = 1;
    
    while (true)
	{
        if ( ((e*d)%t) == 1) // d found
	      break;
		else
		  d++;	 
	}

	pub.open(pub_file.c_str(),ios::out);
	pri.open(pri_file.c_str(),ios::out);
    
	pub << "<rsakey>" << '\n';
	pub << "<evalue>" << e << "</evalue>" << '\n' << '\n';
	pub << "<nvalue>" << n << "</nvalue>" << '\n';
	pub << "</rsakey>";

    pri << "<rsakey>" << '\n';
	pri << "<dvalue>" << d << "</dvalue>" << '\n' << '\n';
	pri << "<nvalue>" << n << "</nvalue>" << '\n';
	pri << "</rsakey>";

	pub.close();
    pri.close();

	cout << "The Public Key XML file has succesfully written to file name '" << pub_file << "'." << endl;
	cout << "The Private Key XML file has succesfully written to file name '" << pri_file << "'." << endl;

	return 0;
}

void error_message(int level)
{
       switch (level)
	   {
	   case 1:
		   cout << "ERROR: No file name or only one file name specified." << endl;
		   cout << "       You will need to provide TWO file names after the -o flag   " << endl;
		   cout << "       The first file is for public key, the second file is for private key."<< endl;
           break;
	   case 2:
		   cout << "ERROR: You only enter one prime number." << endl;
		   cout << "       You need to enter two, or none if you want to enter it later in the prompt."<< endl;
		   cout << "       Or you can use the -c flag to let the program generate the number for you." << endl;
		   break;
	   case 3:
		   cout << "ERROR: Both prime number are the same. " <<endl;
		   cout << "       Please enter a pair of prime number that are different." << endl;
		   break;
	   case 4:
		   cout << "ERROR: The prime numbers you have supplied is not large enough." << endl;
		   cout << "       It needs to be larger than 128 and less than 500. " << endl;
		   break;
	   case 5: 
		   cout << "ERROR: You have provided the -c flag, yet you have provided a number." <<endl;
		   break;
	   case 6:
		   cout << "ERROR: You have entered a non prime number." << endl;
	   default:
		   cout << "ERROR: Invalid argument specified." << endl;
		   break;
	   }

	   cout << endl;
	   cout << "Correct Syntax: " << endl;
	   cout << "keygen ( [-c] || [(prime #1) (prime #2)] ) [-o] (filename1) (filename2)" << endl;

}

void random_gen(int &p, int &q)
{
   cout << endl;
   cout << "Generating pair of prime numbers. Please wait....." <<endl;

   int chosen;
   srand ( static_cast<unsigned int> ( time ( 0 ) ) );
   int prime_array_size(0);
   vector <int> prime_array;

   int i,j;

   //creating a prime number array, stores all primes from 128 to 10000

   for (i=128; i<10000; i++ )
   {
          for (j=2; j<= i/2; j++ )
          {
               if (!(i%j)) // i not prime
				  break;
          } 

          if (j>i/2)  // i is prime
		  {
              prime_array_size++;
              prime_array.resize(prime_array_size);
			  prime_array[ prime_array_size-1] = i;
		  }
   }

   //random selection from prime array
       chosen = (rand() / ( RAND_MAX / prime_array_size ) );
       p = prime_array[chosen];

       chosen = (rand() / ( RAND_MAX / prime_array_size ) );
       q = prime_array[chosen];
}

bool prime_verify (int num)
{
	if (num <= 128) return false;

	 for (int i = 2; i < num/2; i++)
	 {
         if ( num % i == 0)
			 return false;

	 }

	 return true;


}

inline void prime_entry (int &p , int &q)
{
       bool valid_entry = false;
		
		 do
		 {
		   cout << endl;
		   cout << "Please enter two prime numbers greater than 128, seperated by space." << endl;
		   cout << "Or alternatively you can enter '1 1' to let the program randomly generate these for you." << endl;
		   cout << "--->";
		   cin >> p >> q;
 
           if ( (p==1) && (q==1) )
		   {
			   random_gen(p,q);
			   valid_entry = true;
		   }
		   else if (p==q)
		   {
               error_message(3);
		   }
		   else if ( prime_verify(p) && prime_verify(q))
		   {
                valid_entry = true;
		   }
		   else
		   {
			   cout << "ERROR: You have either entered a non-prime number or not '1 1'. Please try again. " << endl << endl;
		   }    
		 }while (!valid_entry);


}

long long gcd(long long a,long long b)
{
   while (true)
   {
       a=a%b;

	   if (a==0) return b;

	   b=b%a;

	   if (b==0) return a;

   }

}

