/*
Arnold Lee
CS 340 Program #1
Five Card Draw Poker - Main Module
Date: 01/28/2010
*/


#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include "cardpile.h"
#include "poker_user.h"
#include "poker_ai.h"

using namespace std;

int main() // main program
{
    pokeruser player; 
	// initialize player (human user) class

	cardpile deck;
	// initialize the deck

    vector <pokerai> computer;
    // initiaze the computer players (AI) as an array
	// for the multiplayer mode.
	// Up to 3 AI allowed.

	vector <int> leader_points;
    // for multiplayer mode
	// To keep track the rank of hand for each player
	// by using an integer (leader points)

	int leader_flag = 0;
    // to keep track who has the best hand

	int top_score = 0;
	// for comparison purpose

    char retry('Y'); 
	// the user response for restarting the game at the end

	int disc1,disc2,disc3;
	// the user input for which card to discard


  while ((retry == 'Y') || (retry == 'y'))
  {

	cout <<"*************Welcome to Arnold's Five Card Draw Poker!! *************" <<endl;
	cout << endl;
	cout <<"*********************GUARANTEED 100% FAIR!!! ************************" << endl;
    cout << endl;

	int comp_num; 
	// number of computer players

	cout <<"    LET'S GET STARTED!!!! " << endl;
	cout << endl;
	cout <<"Please choose number of computer players, from 0 to 3." << endl;
	cout <<"--->";
	cin >> comp_num;
	cout << endl;

	while ((comp_num < 0) || (comp_num > 3))
	{
          cout << "***Invalid Selection. Please Try Again.***"<<endl;
		  cout <<"Please choose number of computer players, from 0 to 3." << endl;
	      cout <<"--->";
	      cin >> comp_num;
		  cout << endl;
	}
	
	if (comp_num !=0) computer.resize(comp_num);
	// resize the AI array

	leader_points.resize(comp_num+1);
	// resize the points tracking array

	cout << endl;
	
	if (comp_num !=0)
	{
          cout << "****************Opponent Information*****************" << endl;
		  cout << endl;
	}

	// this only triggers during multiplayer mode
	for (int a=0; a < comp_num; a++)
	{
        computer[a].start(deck,comp_num);
		cout << endl;
		cout <<	"Computer Player #" <<a+1;

		// run the AI discard algorithm
		cout << " has discarded " << computer[a].process(deck,comp_num) <<  " cards" << endl;
       
		cout << endl;
	}

   if (comp_num == 0)
   {
    //single player mode

	player.start(deck,comp_num);
	player.display_card(); // display the cards
	cout << endl;
	player.display_rank(); // display the rank of hand
   }
   else
   {
    // multiplayer mode

	cout << endl;
	cout << "*********************IT IS YOUR TURN!!!!******************" << endl;
	cout << endl;
    player.start(deck,comp_num);
	player.display_card();
	cout << endl;
	player.display_rank();
   }
	cout << endl;
	cout <<"         Choose up to 3 cards to discard." << endl;
	cout <<endl;
	cout <<"      Enter three numbers, from 1,2,3,4 or 5, seperate by spaces." <<endl;
	cout << endl;
	cout <<"       If you don't want to discard some cards, enter 0 instead." << endl;
    cout <<endl;
	cout <<"Example: 2 0 0 (discard card 2 only)" << endl;
	cout <<"         1 4 3 (discard card 1,3 and 4)"<<endl;
	cout <<"         0 3 0 (discard only card 3)"<<endl;
	cout <<"         0 0 0 (discard none, keep current hand)" << endl;
	cout <<"--->";

 
   // enter upto three cards to discard
    cin >> disc1 >> disc2 >> disc3;
	

	cout << endl;
	//player proceeds to discard the chosen cards
	player.discard(disc1,disc2,disc3,deck,comp_num);
	player.display_card();
	cout << endl;
	// assign rank points in multiplayer rank
	leader_points[0] = player.display_rank();
    


   for (int b=0; b < comp_num; b++)
	{
        
		// for computer player to display their cards

		cout <<	"Computer Player #" <<b+1;

		// record leader points
		leader_points[b+1] = computer[b].display_rank();

		computer[b].display_card();
        cout << endl;
	}


   // determine who has the winning hand in multiplayer mode
   if (comp_num !=0)
   {
    top_score = 0;
    for (int c = 0; c < comp_num; c++)
    {
           if (top_score <= leader_points[c])
		   {
			   top_score = leader_points[c];
			   leader_flag = c;  // WINNER
		   }
    }
   }

   // This IF statement only triggers in multiplayer mode
   // leader_flag == 0 means the human user has the highest hand
   // leader_flag == 1 means computer #1 has the highest hand ... etc.
   // This will determine the appropriate message to display
   if ((leader_flag == 0) && (comp_num != 0))
   {
	   cout << endl;
	   cout <<"************You're WINNER************** " << endl;
   }
   else if (leader_flag !=0)
   {
	   cout << endl;
	   cout <<"Computer Player #" << leader_flag;
	   cout <<" has the best hand of the table." << endl;
	   cout << endl;
	   cout <<"***********LOSER!!!!!!!!!!!!!!!******** " << endl;
   }  
   
    cout << endl;
	cout << "Play Again?" <<endl;
	cout << "Enter Y or y to play again, everything else to exit-->";
	cin >> retry;  // Want to play again?


  }//no more retry
	return 0;
}

