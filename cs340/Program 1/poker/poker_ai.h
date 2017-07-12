/*
Arnold Lee
CS 340 Program #1
AI player class declaration
Date: 01/17/2010
*/

#ifndef POKERAI_H
#define POKERAI_H

#include "cardpile.h"
#include "poker_user.h"

class pokerai
{
public:
	pokerai();
	void start(cardpile &,int);
    void display_card(); // showing 'AH','KH' etc. given card position
	int display_rank(); // showing your current combo
	// i.e. You have Royal Flush, etc.
	// return the rank number of the hand for comparison later
	int high_card(); // check rank of high card (1st card), use as tiebreaker
	int high_card2(); // check rank of 2nd card
	int high_card3(); // check rank of 3rd card
	int high_card4(); // check rank of 4th card
	int high_card5(); // check rank of 5th card
	int suit_card(); // check suit of the 1st card, use as tie breaker
	int suit_card2(); // check suit of 2nd card
	int suit_card3(); // check suit of 3rd card
	int suit_card4(); // check suit of 4th card
	int suit_card5(); // check suit of 5th card

	int process(cardpile &,int); // start the AI discard process
	// return the number of cards discarded

private:
	vector <Card> ai_hand; 
	// array of computer user hands
	// size = number of computer users

    void sort(); 
    // sort the hand from highest to lowest (Extra credit)
	int display_rank_supress();
    // display_rank function but all output message supressed
	
	

};

#endif