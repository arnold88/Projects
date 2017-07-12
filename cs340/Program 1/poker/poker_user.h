/*
Arnold Lee
CS 340 Program #1
User hand class Declaration
Date: 01/17/2010
*/

#ifndef POKERUSER_H
#define POKERUSER_H

#include "cardpile.h"

class pokeruser
{
public:
	pokeruser(); // player initialization
    void start(cardpile &,int);
	void discard(int ,int ,int ,cardpile &,int);
	void display_card(); // showing 'AH','KH' etc. given card position
	int display_rank(); // showing your current combo
	// i.e. You have Royal Flush, etc.
	// return the rank number of the hand for comparison later
	int high_card(); // check rank of high card (1st card), use as tiebreaker
	int high_card2(); // check rank of 2nd card
	int high_card3(); // check rank of 3rd card
	int high_card4(); // check rank of 4th card
	int high_card5(); // check rank of 5th card
	int suit_card(); // check suit of 1st card, use as tie breaker
	int suit_card2(); // check suit of 2nd card
	int suit_card3(); // check suit of 3rd card
	int suit_card4(); // check suit of 4th card
	int suit_card5(); // check suit of 5th card

	
private:
	vector <Card> user_hand; 
    // a 5-slot vector holding user's 5 cards

    void sort();
	// sort the hand from highest to lowest (extra credit)

};


#endif