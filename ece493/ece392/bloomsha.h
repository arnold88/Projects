#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bloom.h"
#include <math.h>
#include "sha1.h"


#define MAX_VALUES 4294967295	//This is the input to random # so 2^32 -1
//#define RAND_MAX 4294967295 //This is the input to random # so 2^32 -1
//#define m 65536 
//#define n 256
//#define k 4

short hash1(long c);
short hash2(long c);
short hash3(long c);
short hash4(long c);

/*create an array with the length of m*/
void create_vect(int);

/*iadd a 32-bit long c*/
int add_key(long );

/*return 1 if exists, 0 otherwise*/
int check(long );
