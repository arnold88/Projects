#include "string.h"
#include "iostream"
using namespace::std;

int main ()
{
	//int PatNum,Period;
	//float RateMin;

	double RateMin [] = {74.8388, 74.8473, 74.4513, 74.3927, 74.855, 74.3676, 74.3676, 74.3676};
	int Period [] = {0,1,1,1,1,2,2,2};
	int Length [] = {0,3,2,1,1,2,2,2};

	printf("Enter patient number 1-8: ");
	int PatNum = getchar() - 49;

	printf("Statistics for patient %d\n", PatNum);
	printf("Heart Rate: %2.4f \n",RateMin[PatNum]);
	cout << endl;
	printf("Murmur Period:\n");
	if (Period[PatNum]==0)
	{
		printf("No Murmur");
		cout << endl;
	}
	else if (Period[PatNum]==1)
	{
		printf("Systolic");
		cout << endl;
	}
	else
	{
		printf("Diastolic");
		cout << endl;
	}

	cout << endl;
	

	printf ("Murmur Length: \n");
	if (Length[PatNum]==0)
	{
		printf("No Murmur");
		cout << endl;

	}
	else if (Length[PatNum]==1)
	{
		printf("early");
		cout << endl;
	}
	else if (Length[PatNum]==2)
	{
		printf("Late");
		cout << endl;
	}
	else
	{
          cout << "You are PHUCKED!" << endl;
		  cout << endl;
	}
	 
}
