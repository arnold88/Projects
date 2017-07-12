/*
Arnold Lee
CS 340 Program #1
Card Pile Class Implementation
Date: 01/17/2010
*/

#include "cardpile.h"
#include <ctime>
#include <math.h>


// initialize a pile, or number of piles
// depends on number of players
cardpile::cardpile(int deck)
{
   pilesize = deck * 52;
   pile.resize(pilesize);
   newpile.resize(pilesize);
   marker = 0;
   hands_played = 0;
   
   for (int i = 0; i < pilesize ; i++)
   {
	   pile[i] = Card(i+5);

   }

   shuffle();
}

// Shuffle the pile
void cardpile::shuffle()
{
   int chosen;
   srand ( static_cast<unsigned int> ( time ( 0 ) ) );

   for (int i = 0;i < pilesize; i++)
   {
       chosen = (rand() / ( RAND_MAX / 52 ) );
       newpile[i] = pile[chosen];

   }
       
}


// This function to deliver a card from the pile.
// The number of players is needed to determine
// when to shuffle
Card cardpile::deliver(int player_num)
{
	
	Card temp;

	if ( hands_played >= floor(double(10/(player_num+1)))) // out of cards?
	{
		  
          if (player_num == 0) cout << "The deck is being shuffled...." << endl;
		  shuffle();
		  hands_played = 0;
		  marker = 0;
	}
    
	hands_played = hands_played + 1;
	
	temp = newpile[marker];
    marker = marker + 1;

	return temp;

}