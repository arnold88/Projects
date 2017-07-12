/*
Arnold Lee
CS 340 Program #1
AI player class implementation
Date: 01/28/2010
*/

#include "poker_ai.h"
#include <ctime>
#include <math.h>


pokerai::pokerai() // default constructor
{
}

void pokerai::start(cardpile & pile2,int player_num)
{
   // deal
   ai_hand.resize(5);

   for (int i = 0; i < 5; i++)
   {
	   
	   ai_hand[i] = pile2.deliver(player_num);
	  
   }


   // sort
   sort();

}// end start

// sorting function for extra credit
void pokerai::sort()
{ 
	Card temp;
    Card temp1;
	Card temp2;

    for (int x = 0 ; x < 4 ; x++)
	{
		for (int y = 0; y < 4 ; y++)
		{
			if (ai_hand[y].num_rank() < ai_hand[y+1].num_rank())
			{
                 temp = ai_hand[y];
				 ai_hand[y] = ai_hand[y+1];
				 ai_hand[y+1]   = temp;
			}
		}
	}

    // hand is sorted by rank, need to check for pairs/trips/quads
	// and re-order
     
	
   if  (  (high_card2() == high_card3())
	   && (high_card3() == high_card4())
	   && (high_card4() == high_card5()) )
   {
	   // Quads
       temp = ai_hand[0];
	   ai_hand[0] = ai_hand[1];
	   ai_hand[1] = ai_hand[2];
	   ai_hand[2] = ai_hand[3];
	   ai_hand[3] = ai_hand[4];
       ai_hand[4] = temp;
   }
   else if (  (high_card2() == high_card3())
	  && (high_card3() == high_card4()) )
   {
	   // trips
       temp = ai_hand[0];
	   ai_hand[0] = ai_hand[1];
	   ai_hand[1] = ai_hand[2];
	   ai_hand[2] = ai_hand[3];
       ai_hand[3] = temp;
   }
   else if   ((high_card3() == high_card4())
	  && (high_card4() == high_card5()) )
   {
	   //trips
	   temp = ai_hand[0];
	   temp1 = ai_hand[1];
	   ai_hand[0] = ai_hand[2];
	   ai_hand[1] = ai_hand[3];
	   ai_hand[2] = ai_hand[4];
       ai_hand[3] = temp;
	   ai_hand[4] = temp1;
   }
   else if 
	( (high_card2() == high_card3() ) && 
	  (high_card4() == high_card5() )  )
   {
          //two pair
       temp = ai_hand[0];
	   ai_hand[0] = ai_hand[1];
	   ai_hand[1] = ai_hand[2];
	   ai_hand[2] = ai_hand[3];
	   ai_hand[3] = ai_hand[4];
       ai_hand[4] = temp;	  

	for (int x = 0 ; x < 4 ; x++)
	{
		for (int y = 0; y < 4 ; y++)
		{
			if (ai_hand[y].num_rank() < ai_hand[y+1].num_rank())
			{
                 temp = ai_hand[y];
				 ai_hand[y] = ai_hand[y+1];
				 ai_hand[y+1]   = temp;
			}
		}
	}

   }
   else if ( ( high_card2() == high_card3() )) 
   {
	   //pair
       temp = ai_hand[0];
	   ai_hand[0] = ai_hand[1];
	   ai_hand[1] = ai_hand[2];
	   ai_hand[2] = temp;
   }
   else if ( (high_card3() == high_card4() ) )
   {
	   //pair
       temp = ai_hand[0];
	   temp1 = ai_hand[1];
	   ai_hand[0] = ai_hand[2];
	   ai_hand[1] = ai_hand[3];
	   ai_hand[2] = temp;
	   ai_hand[3] = temp1;
   }
   else if ( (high_card3() == high_card4() ) ) 
   {
       //pair
	   temp = ai_hand[0];
	   temp1 = ai_hand[1];
       temp2 = ai_hand[2];
	   ai_hand[0] = ai_hand[3];
	   ai_hand[1] = ai_hand[4];
	   ai_hand[2] = temp;
	   ai_hand[3] = temp1;
	   ai_hand[4] = temp2;

   }

}// end sort

//display the cards
void pokerai::display_card()
{
	cout << endl;
	cout << "Its Hand:" << endl;
    
   for (int i = 0; i < 5; i++)
   {
	   cout << i+1 <<") " << ai_hand[i].string_rank() << "   ";
   }
	 
   cout << endl;
} // end display_card


// display the rank
// return the rank point of hand
// i.e. Royal Flush = 10 points
// Staright flush = 9 points
// Four of a kind = 8 points etc.
int pokerai::display_rank()
{
    
	cout << " currently have a ";

	if ((ai_hand[0].num_rank() == ai_hand[1].num_rank() - 4)
       &&(ai_hand[1].num_rank() == ai_hand[2].num_rank() - 4) 	
	   &&(ai_hand[2].num_rank() == ai_hand[3].num_rank() - 4)
	   &&(ai_hand[3].num_rank() == ai_hand[4].num_rank() - 4))
	{
		if (high_card() == 14)
		{
			cout << "Royal Flush!" << endl;
		    return 10;
		}
		else
		{
            cout << "Straight Flush!" << endl;
			return 9;
		}
	}
	else if 
	( (ai_hand[1].num_rank() == ai_hand[2].num_rank() - 4) 	
	 &&(ai_hand[2].num_rank() == ai_hand[3].num_rank() - 4)
	 &&(ai_hand[3].num_rank() == ai_hand[4].num_rank() - 4)
	 &&(high_card() == 14) && (high_card2() == 5) )
	{
            cout << "Straight Flush!" << endl;
			return 9;
	}
	else if 
    (  (high_card()==high_card2())
	&& (high_card2()==high_card3())
	&& (high_card3()==high_card4())  
	)
	{
           cout << "Four of a kind!" << endl;
		   return 8;	  
	}
	else if 
    (  (high_card()==high_card2())
	&& (high_card2()==high_card3())
	&& (high_card4()==high_card5())  
	)
	{
		cout << "Full House!" <<endl;
		return 7;
	}
	else if 
	(  (suit_card()==suit_card2())
	&& (suit_card2()==suit_card3())
	&& (suit_card3()==suit_card4()) 
    && (suit_card4()==suit_card5())
	)	
	{
		cout << "Flush!" <<endl;
		return 6;
	}
	else if 
	(  (suit_card()==suit_card2())
	&& (suit_card2()==suit_card3())
	&& (suit_card3()==suit_card4()) 
    && (suit_card4()==suit_card5())
	)	
	{
		cout << "Flush!" <<endl;
		return 6;
	}
	else if
	(  ( high_card2() == high_card3() - 1)
	 &&( high_card3() == high_card4() - 1)
      &&( high_card4() == high_card5() - 1)
	 &&(high_card() == 14) && (high_card2() == 5) )
	{
            cout << "Straight!" << endl;
			return 5;
	}
	else if 
    ( (high_card2() == high_card3() - 1)
	 &&( high_card3() == high_card4() - 1)
     &&( high_card4() == high_card5() - 1)
	 &&(high_card() == high_card2() - 1)  )
	{
		 cout << "Straight!" << endl;
		 return 5;
	}
	else if 
	(  (high_card()==high_card2())
	&& (high_card2()==high_card3())
	)
	{ 
	    cout << "Three of a kind." << endl;
		 return 4;
	}
	else if
    (  (high_card()==high_card2())
	&& (high_card3()==high_card4())
	)
	{
         cout << "Two Pair." << endl;
		 return 3;

	}
	else if
	(  (high_card()==high_card2() )
	)
	{
         cout << "a Pair." << endl;
		 return 2;
	}
	else
	{

          switch (high_card())
		  {
		  case 14:
			  cout <<"Ace ";
			  break;
		  case 13:
			  cout <<"King ";
			  break;
	      case 12:
			  cout <<"Queen ";
			  break;
		  case 11:
			  cout <<"Jack ";
			  break;
		  case 10:
			  cout <<"Ten ";
			  break;
		  case 9:
			  cout <<"Nine ";
			  break;
		  case 8:
			  cout <<"Eight ";
			  break;
		  case 7:
			  cout <<"Seven ";
			  break;
     	  }

          cout << "high." << endl;
		  return 1;
	}
	 	
}// end display_rank 


// the following five functions are to return card values
// 14 = Ace, 13 = King etc.
int pokerai::high_card()
{
	return int(ceil(double(ai_hand[0].num_rank())/4));
}

int pokerai::high_card2()
{
	return int(ceil(double(ai_hand[1].num_rank())/4));
}

int pokerai::high_card3()
{
	return int(ceil(double(ai_hand[2].num_rank())/4));
}

int pokerai::high_card4()
{
	return int(ceil(double(ai_hand[3].num_rank())/4));
}

int pokerai::high_card5()
{
	return int(ceil(double(ai_hand[4].num_rank())/4));
}

//This returns the suit of the card as integer
//1=clubs,2=diamonds,3=hearts,0=spades

int pokerai::suit_card()
{
	return ai_hand[0].num_rank()%4;
}

int pokerai::suit_card2()
{
	return ai_hand[1].num_rank()%4;
}

int pokerai::suit_card3()
{
	return ai_hand[2].num_rank()%4;
}

int pokerai::suit_card4()
{
	return ai_hand[3].num_rank()%4;
}

int pokerai::suit_card5()
{
	return ai_hand[4].num_rank()%4;
}


// This is the AI discard process for the computer users
int pokerai::process(cardpile & pile2,int player_num)
{

	int qualifier;

	qualifier=display_rank_supress();

    if (qualifier >= 2) // pair or better
	{
          //discard lowest 3 cards

          ai_hand[2] = pile2.deliver(player_num); 
		  ai_hand[3] = pile2.deliver(player_num);
		  ai_hand[4] = pile2.deliver(player_num);
		  return 3;
	}
	else //high card only
	{
		if (  // if on a flush draw
	     (suit_card()==suit_card2())
	  && (suit_card2()==suit_card3())
	  && (suit_card3()==suit_card4()) 
	  )
	  { 
 
         ai_hand[4] = pile2.deliver(player_num);  
		 return 1;
	  }
	  else  if ( // if on flush draw
	     (suit_card()==suit_card2())
	  && (suit_card2()==suit_card3())
	  && (suit_card3()==suit_card5()) 
	  )
	  { 
         ai_hand[3] = pile2.deliver(player_num); 
		 return 1;
	  }
	  else if ( //flush draw
	     (suit_card()==suit_card2())
	  && (suit_card2()==suit_card4())
	  && (suit_card4()==suit_card5()) 
	  )
	  { 
         ai_hand[2] = pile2.deliver(player_num);  
		 return 1;
	  }
	  else if (  //flush draw
	     (suit_card()==suit_card3())
	  && (suit_card3()==suit_card4())
	  && (suit_card4()==suit_card5()) 
	  )
	  { 
         ai_hand[1] = pile2.deliver(player_num); 
		 return 1;
	  }
	  else if ( // flush draw
	     (suit_card2()==suit_card3())
	  && (suit_card3()==suit_card4())
	  && (suit_card4()==suit_card5()) 
	  )
	  { 
         ai_hand[0] = pile2.deliver(player_num);  
		 return 1;
	  }
	  else if ( // if on staright draw
		  (high_card2() == high_card3() - 1)
	 &&( high_card3() == high_card4() - 1)
	 &&(high_card() == high_card2() - 1)  )
	  {
          ai_hand[4] = pile2.deliver(player_num); 
          return 1;
	  }
	  else if (high_card() == 14) // ace high
	  {
          //discard 4 cards

          ai_hand[1] = pile2.deliver(player_num);
          ai_hand[2] = pile2.deliver(player_num); 
		  ai_hand[3] = pile2.deliver(player_num);
		  ai_hand[4] = pile2.deliver(player_num);
		  return 4;
	  }

       // if everything else, discard 3 lowest cards

	   ai_hand[2] = pile2.deliver(player_num); 
	   ai_hand[3] = pile2.deliver(player_num);
	   ai_hand[4] = pile2.deliver(player_num);
	   return 3;

	}

}//end process



// the following function is the same as the display_rank function
// only the output is supressed
int pokerai::display_rank_supress()
{
    if ((ai_hand[0].num_rank() == ai_hand[1].num_rank() - 4)
       &&(ai_hand[1].num_rank() == ai_hand[2].num_rank() - 4) 	
	   &&(ai_hand[2].num_rank() == ai_hand[3].num_rank() - 4)
	   &&(ai_hand[3].num_rank() == ai_hand[4].num_rank() - 4))
	{
		if (high_card() == 14)
		{
		    return 10;
		}
		else
		{
			return 9;
		}
	}
	else if 
	( (ai_hand[1].num_rank() == ai_hand[2].num_rank() - 4) 	
	 &&(ai_hand[2].num_rank() == ai_hand[3].num_rank() - 4)
	 &&(ai_hand[3].num_rank() == ai_hand[4].num_rank() - 4)
	 &&(high_card() == 14) && (high_card2() == 5) )
	{
			return 9;
	}
	else if 
    (  (high_card()==high_card2())
	&& (high_card2()==high_card3())
	&& (high_card3()==high_card4())  
	)
	{

		   return 8;	  
	}
	else if 
    (  (high_card()==high_card2())
	&& (high_card2()==high_card3())
	&& (high_card4()==high_card5())  
	)
	{
		
		return 7;
	}
	else if 
	(  (suit_card()==suit_card2())
	&& (suit_card2()==suit_card3())
	&& (suit_card3()==suit_card4()) 
    && (suit_card4()==suit_card5())
	)	
	{
		
		return 6;
	}
	else if 
	(  (suit_card()==suit_card2())
	&& (suit_card2()==suit_card3())
	&& (suit_card3()==suit_card4()) 
    && (suit_card4()==suit_card5())
	)	
	{
		
		return 6;
	}
	else if
	(  ( high_card2() == high_card3() - 1)
	 &&( high_card3() == high_card4() - 1)
      &&( high_card4() == high_card5() - 1)
	 &&(high_card() == 14) && (high_card2() == 5) )
	{
            
			return 5;
	}
	else if 
    ( (high_card2() == high_card3() - 1)
	 &&( high_card3() == high_card4() - 1)
     &&( high_card4() == high_card5() - 1)
	 &&(high_card() == high_card2() - 1)  )
	{
		
		 return 5;
	}
	else if 
	(  (high_card()==high_card2())
	&& (high_card2()==high_card3())
	)
	{
		 return 4;
	}
	else if
    (  (high_card()==high_card2())
	&& (high_card3()==high_card4())
	)
	{
		 return 3;

	}
	else if
	(  (high_card()==high_card2() )
	)
	{
		 return 2;
	}
	else
	{
		  return 1;
	}

}//end display_rank_supress