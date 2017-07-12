// Arnold Lee
// CS 421 HW #2A Exercise 1.2


// file input format: (TAG word)
// for example: (VB do), (IN from), (PP$ his)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct bigram
{
     string first;
	 string second;

};

struct wordpair
{
      string word;
      string tag;
};

bool operator == (const bigram & lhs, const bigram & rhs)
{
	return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
}

bool operator == (const wordpair & lhs, const wordpair & rhs)
{
	return ((lhs.word == rhs.word) && (lhs.tag == rhs.tag));
}

int main()
{
   fstream input;
   vector <string> tag(2000);
   vector <string> word(2000);
   int word_count(0);
   string dummy;
   bool inside(false);
   int left_p;
   int middle;
   int tag_count(0);
   vector <string> image(2000);
   vector <int> image2(2000);
   vector <string> tag_image(2000);
   vector <int> tag_image2(2000);
   int image_count(0);
   int tag_image_count(0);
   bool match(false);
   string image_dummy;
   int image2_dummy;
   ofstream output;

   vector <bigram> tag_bigram (2000);
   vector <wordpair> word_pair (2000);
   
   vector <bigram> tag_bigram_image(2000);
   vector <int> tag_bigram_image2(2000);
   int tag_bigram_count(0);

   vector <wordpair> word_pair_image(2000);
   vector <int> word_pair_image2(2000);
   int word_pair_count(0);

   

   input.open("hw2.txt");
   output.open("output.txt");

   if (input.fail())
   {
          cout << "Error opening file" <<endl;
		  exit(1);
   }

   while (!input.eof())
   {
         getline(input,dummy);
		 
		 for (unsigned int i = 0 ; i < dummy.length() ; i++)
		 {
                if (dummy[i] == '(')
				{
                      left_p = i+1;
					  inside = true;
				}

				if ((inside) && dummy[i] == ' ')
				{
				          tag[tag_count] = dummy.substr(left_p,i-left_p); 
						  tag_count++;
						  middle = i;
				}

				if ((inside) && dummy[i] == ')')
				{
				          word[word_count] = dummy.substr(middle+1,i-middle-1); 
						  word_count++;
						  inside = false;
				}

		 }

   }

   cout << tag_count << endl;
   cout << tag[0] << " " << tag[1] << endl;
   cout << word_count << endl;
   cout << word[0] << " " << word[1] << endl;

   //******************************** word process

   for (unsigned int i=0;i<image2.size();i++)
   {
         image2[i] = 0;

   }

   for (int i=0;i<word_count;i++)
   {

     for (int j=0;j<image_count;j++)
	 {
       if (image[j]==word[i])
	   {
           image2[j]++;
		   match=true;
		 
	   }
	 }

	 if (!match)
	 {
          image[image_count] = word[i];
		  image2[image_count]++;
		  image_count++;
		  
	 }

	 match = false;
   }


   //***********************tag process

   for (unsigned int i=0;i<tag_image2.size();i++)
   {
         tag_image2[i] = 0;

   }

   for (int i=0;i<tag_count;i++)
   {

     for (int j=0;j<tag_image_count;j++)
	 {
       if (tag_image[j]==tag[i])
	   {
           tag_image2[j]++;
		   match=true;
		 
	   }
	 }

	 if (!match)
	 {
          tag_image[tag_image_count] = tag[i];
		  tag_image2[tag_image_count]++;
		  tag_image_count++;
		  
	 }

	 match = false;
   }


   //************************sort results
  
   
  for (int b=0;b<image_count;b++)
  {
   for (int a=0;a<image_count-1;a++)
   {
	    if (image2[a] < image2[a+1])
		{
             image2_dummy=image2[a];
			 image2[a] = image2[a+1];
			 image2[a+1] = image2_dummy;

             image_dummy=image[a];
			 image[a] = image[a+1];
			 image[a+1] = image_dummy;
		}
   }
  }

 
  
/*
   for (int x=0;x<image_count;x++)
   {
	   output << "Word count for " << image[x] << " is:" << image2[x] << endl;
	   output << "Probability: " <<   double(image2[x])/double(word_count) << endl;
	   
   }

   output << "****************************" << endl;

   
 
  
   for (int x=0;x<tag_image_count;x++)
   {
	   
	   output << "Tag count for " << tag_image[x] << " is:" << tag_image2[x] << endl;
	   output << "Probability: " <<  double(tag_image2[x])/ double(tag_count) << endl;
	   
   }
   
*/

   //*******************************************

   for (int x=0;x<tag_count-1;x++)
   {
	   tag_bigram[x].first=tag[x];
	   tag_bigram[x].second=tag[x+1];
   }
   
   for (int x=0;x<word_count-1;x++)
   {
	   word_pair[x].tag=tag[x];
	   word_pair[x].word=word[x];
   }

   //*******************************************

   for (unsigned int i=0;i<tag_bigram_image2.size();i++)
   {
         tag_bigram_image2[i] = 0;

   }

   for (int i=0;i<tag_count-1;i++)
   {

     for (int j=0;j<tag_bigram_count;j++)
	 {
       if (tag_bigram_image[j]==tag_bigram[i])
	   {
           tag_bigram_image2[i]++;
		   match=true;
		 
	   }
	 }

	 if (!match)
	 {
          tag_bigram_image[tag_bigram_count] = tag_bigram[i];
		  tag_bigram_image2[tag_bigram_count]++;
		  tag_bigram_count++;
		  
	 }

	 match = false;
   }

  //****************************************************

   for (unsigned int i=0;i<word_pair_image2.size();i++)
   {
         word_pair_image2[i] = 0;

   }

   for (int i=0;i<word_count-1;i++)
   {

     for (int j=0;j<word_pair_count;j++)
	 {
       if (word_pair_image[j]==word_pair[i])
	   {
           word_pair_image2[i]++;
		   match=true;
		 
	   }
	 }

	 if (!match)
	 {
          word_pair_image[word_pair_count] = word_pair[i];
		  word_pair_image2[word_pair_count]++;
		  word_pair_count++;
		  
	 }

	 match = false;
   }

   //****************sort************

  bigram t_dummy;
  int t_dummy_2;

  for (int b=0;b<tag_bigram_count;b++)
  {
   for (int a=0;a<tag_bigram_count-1;a++)
   {
	    if (tag_bigram_image2[a] < tag_bigram_image2[a+1])
		{
             t_dummy_2=tag_bigram_image2[a];
			 tag_bigram_image2[a] = tag_bigram_image2[a+1];
			 tag_bigram_image2[a+1] = t_dummy_2;

             t_dummy=tag_bigram_image[a];
			 tag_bigram_image[a] = tag_bigram_image[a+1];
			 tag_bigram_image[a+1] = t_dummy;
		}
   }
  }

  wordpair w_dummy;
  int w_dummy_2;

  
  for (int b=0;b<word_pair_count;b++)
  {
   for (int a=0;a<word_pair_count-1;a++)
   {
	    if (word_pair_image2[a] <word_pair_image2 [a+1])
		{
             w_dummy_2=word_pair_image2[a];
			 word_pair_image2[a] = word_pair_image2[a+1];
			 word_pair_image2[a+1] = w_dummy_2;

             w_dummy=word_pair_image[a];
			 word_pair_image[a] = word_pair_image[a+1];
			 word_pair_image[a+1] = w_dummy;
		}
   }
  }
  



   //****************************


  output << "********** Tag bigram probabilities *********" << endl;
  output << endl;

    for (int x=0;x<tag_bigram_count;x++)
   {
	   
	  // output << "Tag count for :" << tag_bigram_image[x].first << " | "; 
	    // output <<	   tag_bigram_image[x].second << " is:" << tag_bigram_image2[x] << endl;
	   output << " P ( "  << tag_bigram_image[x].first << " | " <<   tag_bigram_image[x].second;
	        output << " ) is ->" <<  double(tag_bigram_image2[x])/ double(tag_bigram_count) << endl;
	   
   }

   output << endl;
   output << "**********lexical likelihood probabilities ************" << endl;
   output << endl;

	    for (int x=0;x<word_pair_count;x++)
   {
	   
	  // output << "Tag count for :" << word_pair_image[x].word << " | "; 
	    // output <<	   word_pair_image[x].tag << " is:" << word_pair_image2[x] << endl;

	   output << "P ( " << word_pair_image[x].word << " | " <<  word_pair_image[x].tag;
		 output << " ) is ->" <<  double(word_pair_image2[x])/ double(word_pair_count) << endl;
	   
   }


   


   input.close();
   output.close();

return 0;
}