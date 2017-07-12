#include "string.h"
#include "iostream"

int main ()
{
	int PatNum,Period;
	float RateMin;

	RateMin = [74.8388 74.8473 74.4513 74.3927 74.855 74.3676 74.3676 74.3676];
	Period = [0 1 1 1 1 2 2 2];
	Length = [0 3 2 1 1 2 2 2];

	printf("Enter patient number 1-8: ");
	PatNum = getchar();

	printf("Statistics for patient %d\n", PatNum);
	printf("Heart Rate: %2.4f \n",RateMin[PatNum]);
	printf("Murmur Period:\n")
	if (Period[PatNum]==0){
		printf("No Murmur");
	else if (Period[PatNum]==1)
		printf("Systolic");
	else
		printf("Diastolic");
	}

	printf ("Murmur Length: \n")
	if (Length[PatNum]==0){
		printf("No Murmur");
	else if (Length[PatNum]==1)
		printf("early");
	else if (Length[PatNum]==2)
		printf("Late");
	 }
}
