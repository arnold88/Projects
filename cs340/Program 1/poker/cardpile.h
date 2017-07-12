/*
Arnold Lee
CS 340 Program #1
Card Pile Class Declaration
Date: 01/17/2010
*/


#ifndef CARDPILE_H
#define CARDPILE_H

#include "card.h"
#include <stack>
#include <cstdlib>
#include <vector>

class cardpile
{

public:  
	
	  cardpile(int deck = 1);
      // initialize a pile
	  // default # of deck is 1
	  // specify a number if multiple decks

      void shuffle();  
	  // shuffle function,
	  // optional: specify # of random swaps
	  // if not specified, default at 26 (half a pile)

      Card deliver(int);
	  // deliver a random card to a player
	  // remove it from pile

     
	  

private:
	   
      void remove(int);
      // remove a card from pile, resize the pile array
	  vector <Card> pile;
	  // the card pile array
	  vector <Card> newpile; // shuffled deck
	  int pilesize;
	  // size of pile
	  int marker;
	  // use for tracking which card has been discarded
	  // during the shuffling process
	  int hands_played; 
	  // track number of hands played

};

#endif