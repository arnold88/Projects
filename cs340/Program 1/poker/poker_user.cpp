/*
Arnold Lee
CS 340 Program #1
User hand class implementation
Date: 01/17/2010
*/

#include "poker_user.h"
#include <math.h>

pokeruser::pokeruser() //default constructor
{
}

void pokeruser::start(cardpile & pile2,int player_num)
{
   // deal

   user_hand.resize(5);

   for (int i = 0; i < 5; i++)
   {
	   
	   user_hand[i] = pile2.deliver(player_num);
	  
   }

   // sort
   sort();

}


// display the user hand
void pokeruser::display_card()
{
	cout << "Your Current Hand is:" << endl;
    cout << endl;
   for (int i = 0; i < 5; i++)
   {
	   cout << i+1 <<") " << user_hand[i].string_rank() << "   ";
   }
	 
   cout << endl;
}

// the discard function
// accept up to 3 inputs, each represent a card
// get random chosen card in return
void pokeruser::discard(int x,int y,int z,cardpile & pile,int player_num)
{
	while ((x<0) || (x>5) || (y<0) || (y>5) || (z<0) || (z>5))
	{
	cout << endl;
	cout << "INVALID SELECTION. Please try again." << endl;
    cout << endl;
	cout <<"Enter three numbers, from 1,2,3,4 or 5, seperate by spaces." <<endl;
	cout << endl;
	cout <<"If you don't want to discard some cards, enter 0 instead." << endl;
	cout << endl;
	cout <<"Example: 2 0 0 (discard card 2 only)" << endl;
	cout <<"         1 4 3 (discard card 1,3 and 4)"<<endl;
	cout <<"         0 3 0 (discard only card 3)"<<endl;
	cout <<"         0 0 0 (discard none, keep current hand" << endl;
	cout <<"--->";
	cin >> x >> y >> z;
	}
   
	if (x!=0)
	{
	   user_hand[x-1] = pile.deliver(player_num);
	}

	if (y!=0)
	{
        user_hand[y-1] = pile.deliver(player_num);
	}

	if (z!=0)
	{
        user_hand[z-1] = pile.deliver(player_num);
	}

	sort();

}


// the following five functions are to return card values
// 14 = Ace, 13 = King etc.
int pokeruser::high_card()
{
	return int(ceil(double(user_hand[0].num_rank())/4));
}

int pokeruser::high_card2()
{
	return int(ceil(double(user_hand[1].num_rank())/4));
}

int pokeruser::high_card3()
{
	return int(ceil(double(user_hand[2].num_rank())/4));
}

int pokeruser::high_card4()
{
	return int(ceil(double(user_hand[3].num_rank())/4));
}

int pokeruser::high_card5()
{
	return int(ceil(double(user_hand[4].num_rank())/4));
}

//This returns the suit of the card as integer
//1=clubs,2=diamonds,3=hearts,0=spades
int pokeruser::suit_card()
{
	return user_hand[0].num_rank()%4;
}

int pokeruser::suit_card2()
{
	return user_hand[1].num_rank()%4;
}

int pokeruser::suit_card3()
{
	return user_hand[2].num_rank()%4;
}

int pokeruser::suit_card4()
{
	return user_hand[3].num_rank()%4;
}

int pokeruser::suit_card5()
{
	return user_hand[4].num_rank()%4;
}

// sorting function for extra credit
void pokeruser::sort()
{ 
	Card temp;
    Card temp1;
	Card temp2;

    for (int x = 0 ; x < 4 ; x++)
	{
		for (int y = 0; y < 4 ; y++)
		{
			if (user_hand[y].num_rank() < user_hand[y+1].num_rank())
			{
                 temp = user_hand[y];
				 user_hand[y] = user_hand[y+1];
				 user_hand[y+1]   = temp;
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
       temp = user_hand[0];
	   user_hand[0] = user_hand[1];
	   user_hand[1] = user_hand[2];
	   user_hand[2] = user_hand[3];
	   user_hand[3] = user_hand[4];
       user_hand[4] = temp;
   }
   else if (  (high_card2() == high_card3())
	  && (high_card3() == high_card4()) )
   {
	   // trips
       temp = user_hand[0];
	   user_hand[0] = user_hand[1];
	   user_hand[1] = user_hand[2];
	   user_hand[2] = user_hand[3];
       user_hand[3] = temp;
   }
   else if   ((high_card3() == high_card4())
	  && (high_card4() == high_card5()) )
   {
	   //trips
	   temp = user_hand[0];
	   temp1 = user_hand[1];
	   user_hand[0] = user_hand[2];
	   user_hand[1] = user_hand[3];
	   user_hand[2] = user_hand[4];
       user_hand[3] = temp;
	   user_hand[4] = temp1;
   }
   else if 
	( (high_card2() == high_card3() ) && 
	  (high_card4() == high_card5() )  )
   {
          //two pair
       temp = user_hand[0];
	   user_hand[0] = user_hand[1];
	   user_hand[1] = user_hand[2];
	   user_hand[2] = user_hand[3];
	   user_hand[3] = user_hand[4];
       user_hand[4] = temp;	  

   // to fix a rank-sort bug with two pairs
	for (int x = 0 ; x < 4 ; x++)
	{
		for (int y = 0; y < 4 ; y++)
		{
			if (user_hand[y].num_rank() < user_hand[y+1].num_rank())
			{
                 temp = user_hand[y];
				 user_hand[y] = user_hand[y+1];
				 user_hand[y+1]   = temp;
			}
		}
	}
	   


   }
   else if ( ( high_card2() == high_card3() )) 
   {
	   //pair
       temp = user_hand[0];
	   user_hand[0] = user_hand[1];
	   user_hand[1] = user_hand[2];
	   user_hand[2] = temp;
   }
   else if ( (high_card3() == high_card4() ) )
   {
	   //pair
       temp = user_hand[0];
	   temp1 = user_hand[1];
	   user_hand[0] = user_hand[2];
	   user_hand[1] = user_hand[3];
	   user_hand[2] = temp;
	   user_hand[3] = temp1;
   }
   else if ( (high_card3() == high_card4() ) ) 
   {
       //pair
	   temp = user_hand[0];
	   temp1 = user_hand[1];
       temp2 = user_hand[2];
	   user_hand[0] = user_hand[3];
	   user_hand[1] = user_hand[4];
	   user_hand[2] = temp;
	   user_hand[3] = temp1;
	   user_hand[4] = temp2;

   }

}// end sort


// display the ranking
// with the message : "You currently have a ..."
// i.e. Royal Flush, four of a kind etc.
int pokeruser::display_rank()
{
    
	cout << "You currently have a ";

	if ((user_hand[0].num_rank() == user_hand[1].num_rank() - 4)
       &&(user_hand[1].num_rank() == user_hand[2].num_rank() - 4) 	
	   &&(user_hand[2].num_rank() == user_hand[3].num_rank() - 4)
	   &&(user_hand[3].num_rank() == user_hand[4].num_rank() - 4))
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
	( (user_hand[1].num_rank() == user_hand[2].num_rank() - 4) 	
	 &&(user_hand[2].num_rank() == user_hand[3].num_rank() - 4)
	 &&(user_hand[3].num_rank() == user_hand[4].num_rank() - 4)
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
