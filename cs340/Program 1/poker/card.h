/*
Arnold Lee
CS 340 Program #1
Card Class Header
Date: 01/17/2010
*/

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card
{

public:
	
	Card(); 
	// default constructor

	Card(int);
    // constructor with integer argument
	// to assign a card directly

	Card (const Card &);
    // copy constructor

    Card  operator = (const Card &);
	// copy constructor

	// comparsion operators 
	bool  operator < (const Card &);
	bool  operator > (const Card &);
	bool  operator == (const Card &);
	bool  operator != (const Card &);


    
    int num_rank() const ;
    // output numerical rank
	// 5 = 2 of clubs
	// 6 = 2 of diamonds 
	// 55 = ace of hearts
	// 56 = ace of spades

	string string_rank() const ;
    // output string of card rank 
	// 'AH' , '10S' etc. 


private:
	int int_rank;
    // store the numerical rank
};

#endif