/*
Arnold Lee
CS 340 Program #1
Card Class Implementation
Date: 01/17/2010
*/

#include "card.h"

// initialize the card with a dummy variable
Card::Card()
{
    int_rank = 1;
}

//initialize the card with a certain rank/suit
Card::Card (int num_rank)
{
	int_rank = num_rank;
}


// duplicate a card for shuffling purpose
Card::Card (const Card & rhs)
{
	int_rank = rhs.int_rank;
}

// Another form of card duplication
Card Card::operator = (const Card & rhs)
{
	int_rank = rhs.int_rank;
	return *this;
}

// The next 4 operators are for comparing each card

bool  Card::operator < (const Card & rhs)
{
	return (int_rank < rhs.int_rank);
}

bool  Card::operator > (const Card & rhs)
{
	return (int_rank > rhs.int_rank);
}

bool  Card::operator == (const Card & rhs)
{
	return (int_rank == rhs.int_rank);
}

bool  Card::operator != (const Card & rhs)
{
	return !(*this == rhs);
}


// this is to return the numerical rank of the card
// i.e. 56 = Ace of spades
// 55 = Ace of hearts
// etc.
int Card::num_rank() const
{
   return int_rank;
}

// this is to convert numerical rank into
// a string to display on screen

string Card::string_rank() const
{
    switch (int_rank)
	{
		case 53:
			return "AC";
			break;
		case 54:
			return "AD";
			break;
		case 55:
			return "AH";
			break;
		case 56:
			return "AS";
  			break;
		case 5:
			return "2C";
			break;
		case 6:
			return "2D";
			break;
		case 7:
			return "2H";
			break;
		case 8:
			return "2S";
  			break;
		case 9:
			return "3C";
			break;
		case 10:
			return "3D";
			break;
		case 11:
			return "3H";
			break;
		case 12:
			return "3S";
  			break;
		case 13:
			return "4C";
			break;
		case 14:
			return "4D";
			break;
		case 15:
			return "4H";
			break;
		case 16:
			return "4S";
  			break;
		case 17:
			return "5C";
			break;
		case 18:
			return "5D";
			break;
		case 19:
			return "5H";
			break;
		case 20:
			return "5S";
  			break;
		case 21:
			return "6C";
			break;
		case 22:
			return "6D";
			break;
		case 23:
			return "6H";
			break;
		case 24:
			return "6S";
  			break;
		case 25:
			return "7C";
			break;
		case 26:
			return "7D";
			break;
		case 27:
			return "7H";
			break;
		case 28:
			return "7S";
  			break;
		case 29:
			return "8C";
			break;
		case 30:
			return "8D";
			break;
		case 31:
			return "8H";
			break;
		case 32:
			return "8S";
  			break;
		case 33:
			return "9C";
			break;
		case 34:
			return "9D";
			break;
		case 35:
			return "9H";
			break;
		case 36:
			return "9S";
  			break;
		case 37:
			return "10C";
			break;
		case 38:
			return "10D";
			break;
		case 39:
			return "10H";
			break;
		case 40:
			return "10S";
  			break;
		case 41:
			return "JC";
			break;
		case 42:
			return "JD";
			break;
		case 43:
			return "JH";
			break;
		case 44:
			return "JS";
  			break;
		case 45:
			return "QC";
			break;
		case 46:
			return "QD";
			break;
		case 47:
			return "QH";
			break;
		case 48:
			return "QS";
  			break;
		case 49:
			return "KC";
			break;
		case 50:
			return "KD";
			break;
		case 51:
			return "KH";
			break;
		case 52:
			return "KS";
  			break;
		default:
			cout << "An unhandled exception occured in 0xDEADBEEF!" << endl;
            cout << "System Halted!" << endl;
			return "XX";
		}

}