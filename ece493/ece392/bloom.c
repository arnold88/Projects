#include "bloom.h"
#include <math.h>

/*value of seed for random numbers */
static int seed_value = 2001;

/*parameter m , the length of bloom filter bit vector*/
static unsigned long  bloom_m = 1 <<20;
/*parameter n, the number of keys(values) being inserted into bloom filter bit vector*/
static unsigned long  bloom_n = 1 <<13;
/* parameter k, the number of hash functions*/
static int bloom_k = 8;
static unsigned long TEST_LEN = (1<<20);

/*bloom filter's bit vector*/
static char *bloom_filter;

/*hash function pointers array*/
typedef unsigned long (*bloom_filter_ptr) (md_addr_t , md_addr_t , md_inst_t );
static bloom_filter_ptr * bloom_hash_funs = NULL;

/* output file for data to be written to */
static FILE *output;
static FILE *input;

/*Compressing Macro: to convert 32 bit number to 16bit or whatever specified by bloom_m*/
 /*#define compress32_16(b3, b2, b1, b0) (((b3^b1) <<8 | b2^b0) & (bloom_m-1))*/
#define compress32_16(b3, b2, b1, b0) ((((b3)<<24 )| ((b2) <<16)|((b1)<<8)|(b0)) &(bloom_m-1))

/*check the input parameters, now bloom_m, bloom_n, bloom_k can be the input parameters.*/
void bloom_opt_check(int argc, char **argv)
{
    int ret_m, ret_n, ret_k, ret_test, ret_seed;
    int bloom_m_shft = 0, bloom_n_shft = 0, TEST_LEN_shft = 0;
    
    if (argc == 1)
    {
       /* fprintf(stderr, "using the default values for m(0x%x), n(0x%x), k(%d), test_len(0x%x)\n",
                  bloom_m, bloom_n,bloom_k, TEST_LEN); */
        return;
     }
     else 
     /* new command line args of 'prog m seed file' 
        takes 3 arguments */

     if (argc ==4) 
     {
          ret_m = sscanf(argv[1], "%d", &bloom_m_shft);
          ret_seed = sscanf(argv[2], "%d", &seed_value);

          if (!ret_m | !ret_seed)
          {
              fprintf(stderr, "parameters reading error, check the input format...exit\n");
              exit(0);
           }
	  else  
	  {
	      bloom_m = 1 << bloom_m_shft;
	  }
          	 
     }
     else
     /*currently we accept only 5 or 6 parameters*/
     /*5 parameters uses the default seed value, 6 takes a seed value */
     if (argc == 5 || argc == 6)
     {
          /*for m,n, and test, we read the shift amount, but read bloom_k as its orignal values*/
          /*note that use & for var that is going to read the input*/
          ret_m = sscanf(argv[1], "%d", &bloom_m_shft);
          ret_n = sscanf(argv[2], "%d", &bloom_n_shft);
          ret_k = sscanf(argv[3], "%d", &bloom_k);
          ret_test = sscanf(argv[4], "%d", &TEST_LEN_shft);
          if(argc ==6) ret_seed = sscanf(argv[5], "%d", &seed_value);
           else
           {
               bloom_m = 1 <<bloom_m_shft;
               bloom_n = 1 <<bloom_n_shft;               
               TEST_LEN = 1 <<TEST_LEN_shft;               
    	       fprintf(output, "\nm=%d, n=%d, k=%d, testlen=%d\n", bloom_m_shft, bloom_n_shft, bloom_k, TEST_LEN_shft);     
           }
           fprintf(stderr, "using the input values for m(0x%x), n(0x%x), k(%d), test_len(0x%x)\n",
           bloom_m, bloom_n,bloom_k, TEST_LEN); 
     }
     else
     {
         fprintf(stderr, " Wrong input numbers...%s bloom_m bloom_n bloom_k test_len\n", argv[0]);
         exit(0);
     }    
}
static unsigned long bloom_hash0(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;
     
     b3 = (pc        ^  (tpc >>24)) & 0xff;
     b2 = ((pc >> 8) ^  (tpc >>16)) & 0xff;
     b1 = ((pc >>16) ^  (tpc >> 8)) & 0xff;
     b0 = ((pc >>24) ^  tpc       ) & 0xff;
     return compress32_16(b3,b2,b1,b0);
}

static unsigned long bloom_hash1(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;

     b3 = ((pc >> 8) ^  (tpc >>24)) & 0xff;
     b2 = (pc        ^  (tpc >>16)) & 0xff;
     b1 = ((pc >>24) ^  (tpc >> 8)) & 0xff;
     b0 = ((pc >>16) ^  tpc       ) & 0xff;     
     return compress32_16(b1,b0,b3,b2);
}

static unsigned long bloom_hash2(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;

     b3 = ((pc >>24) ^  (tpc >>24)) & 0xff;
     b2 = ((pc >> 8) ^  (tpc >>16)) & 0xff;
     b1 = ((pc >>16) ^  (tpc >> 8)) & 0xff;
     b0 = (pc        ^  tpc       ) & 0xff;  
     return compress32_16(b0,b3,b1,b2);
}

static unsigned long bloom_hash3(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;
     b3 = ((pc >>16) ^  (tpc >>24)) & 0xff;
     b2 = ((pc >>24) ^  (tpc >>16)) & 0xff;
     b1 = (pc        ^  (tpc >> 8)) & 0xff;
     b0 = ((pc >> 8) ^  tpc       ) & 0xff; 
     return compress32_16(b2,b1,b0,b3);
}

static unsigned long bloom_hash4(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;
     b3 = ((pc >>16) ^  (tpc >>24)) & 0xff;
     b2 = ((pc >> 8) ^  (tpc >>16)) & 0xff;
     b1 = (pc        ^  (tpc >> 8)) & 0xff;
     b0 = ((pc >>24) ^  tpc       ) & 0xff; 
     return compress32_16(b1,b2,b3,b0);
}

static unsigned long bloom_hash5(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;
     b3 = (pc        ^  (tpc >>24)) & 0xff;
     b2 = ((pc >>24) ^  (tpc >>16)) & 0xff;
     b1 = ((pc >>16) ^  (tpc >> 8)) & 0xff;
     b0 = ((pc >> 8) ^  tpc       ) & 0xff; 
     return compress32_16(b2,b1,b0,b3);
}

static unsigned long bloom_hash6(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;
     b3 = ((pc >> 8) ^  (tpc >>24)) & 0xff;
     b2 = ((pc >>16) ^  (tpc >>16)) & 0xff;
     b1 = ((pc >>24) ^  (tpc >> 8)) & 0xff;
     b0 = (pc        ^  tpc       ) & 0xff; 
     return compress32_16(b0,b1,b3,b2);
}

static unsigned long bloom_hash7(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
     unsigned char b3, b2, b1,b0;
     b3 = ((pc >>24) ^  (tpc >>24)) & 0xff;
     b2 = (pc        ^  (tpc >>16)) & 0xff;
     b1 = ((pc >> 8) ^  (tpc >> 8)) & 0xff;
     b0 = ((pc >>16) ^  tpc       ) & 0xff; 
     return compress32_16(b1,b2,b0,b3);
}


/*Allocate space for bloom filter bit vector and hash function arrays*/
void bloom_init()
{
    if( (bloom_filter = (char *) calloc(bloom_m, sizeof(char))) == NULL)
        fatal("Failed to init bloom filter bit vector ");   
        
    if ((bloom_hash_funs = (bloom_filter_ptr*) calloc(bloom_k, sizeof(bloom_filter_ptr))) == NULL)
        fatal("Failed to init bloom filter hash functions");
        
    /*Assign the hash functions to the hash function array*/
    bloom_hash_funs[0] = &bloom_hash0;
    bloom_hash_funs[1] = &bloom_hash1;
    bloom_hash_funs[2] = &bloom_hash2;
    bloom_hash_funs[3] = &bloom_hash3;
    bloom_hash_funs[4] = &bloom_hash4;
    bloom_hash_funs[5] = &bloom_hash5;
    bloom_hash_funs[6] = &bloom_hash6;
    bloom_hash_funs[7] = &bloom_hash7;
}

/*free the data structure*/
void bloom_free()
{
    free(bloom_filter);
    free(bloom_hash_funs);
}

/*Insert a new element into the filter's array*/
int bloom_insert(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
    unsigned int i;
    unsigned long bloom_index;
    /*call hash functions and set the corresponding bit to 1*/
    for (i = 0; i <bloom_k; i++)
    {
        /* fun[1]() is a short form while (*fun[1])() is a correct form*/
        bloom_index = (*bloom_hash_funs[i] )( pc,  tpc,  inst);
        bloom_filter[bloom_index] = 1;
        /*printf("0x%x\t", bloom_index>>16);*/
    }
    return 1;
}

/*Test to see if one element is in the filter or not*/
int bloom_check(md_addr_t pc, md_addr_t tpc, md_inst_t inst)
{
    int i;
    unsigned long bloom_index;
    
//printf("pc=%x, tpc=%x, inst=%x\n", pc, tpc, inst);
    for (i = 0; i <bloom_k; i++)
    {
        bloom_index = (*bloom_hash_funs[i] ) ( pc,  tpc,  inst);
        /*if any bit is 0, it doesn't exist*/
        if (bloom_filter[bloom_index] == 0)
            return 0;
    }
    return 1;
}

/* return log of a number to the base 2 */
#ifdef MAIN_TEST
unsigned long
my_log_base2(unsigned long n)
{
  unsigned long power = 0;

  if (n <= 0 || (n & (n-1)) != 0)
    fatal("log2() only works for positive power of two values");

  while (n >>= 1)
    power++;

  return power;
}
#endif

int bloom_concentration(char * data, unsigned long  len)
{
     unsigned long  len_square;
     unsigned long * stat_array;
     unsigned long stat_num;
     double avg_data;
     double sum, var;
     unsigned long total_data=0;
     unsigned long i, j;
     /*ind = square(len)*/
     len_square = 1<<(my_log_base2(len)>>1);
     /*the length of the stat array*/
     stat_num = len/len_square;
     
     if ((stat_array = (unsigned long*) calloc(stat_num, sizeof(unsigned long))) == NULL)
         fatal("mem alloc failed\n");
         
     j = -1;
     for(i=0; i<len; i++)
     {
         if(i % len_square == 0)
              j++;                

         if (data[i]) 
         {
              stat_array[j]++;      
              total_data ++;
          }          
     }
     
     /*average of the stat array*/
     assert(stat_num == (j+1));
     avg_data = (double) total_data/stat_num;

     sum = 0;
     for (j=0; j<stat_num; j++)
     {
         var = stat_array[j] - avg_data;
         sum += var * var;        
         /*
         fprintf(stdout, " s %d; dev: %6.3f\n", stat_array[j], var);
         if (j %6 == 0) fprintf(stderr, "\nj=%d",j);
         */
     }

     sum = sqrt(sum)/stat_num;
     free(stat_array);     
     fprintf(stderr, "standard deviation: %f\n", sum);     
     fprintf(output, "standard deviation: %f\n", sum);     
}

FILE* check_open(char* name, char* mode)
{
	  FILE* fp;
	    if( (fp = fopen(name, mode)) == NULL ){
		        printf("error!!!  NAME[%s], MODE[%s]\n", name, mode);
			    exit(1);
            }
	  return fp;
}
	
int MAIN_TEST(int argc, char **argv)
{
    unsigned int low_rand, high_rand;

    int i, j;
    unsigned int false_positive=0;

    unsigned  long *rpc_a;
    unsigned  long *rtpc_a;
    unsigned  long *rinst_a;

    unsigned  long rpc_b;
    unsigned  long rtpc_b;
    unsigned  long rinst_b;

    unsigned  long conflict = 0;

    int flag = 0;
   
   input   =  check_open(argv[3], "r");
   output  =  check_open("resultsbench", "a");
    
    bloom_opt_check(argc, argv);
    if ((rpc_a = calloc(TEST_LEN, sizeof(unsigned long))) == NULL)
    {
        fprintf(stderr, "calloc for rpc_afailed..exit\n");
        exit(0);
    }
    if ((rtpc_a = calloc(TEST_LEN, sizeof(unsigned long))) == NULL)
    {
        fprintf(stderr, "calloc for rtpc_a failed..exit\n");
        exit(0);
    }
    if ((rinst_a = calloc(TEST_LEN, sizeof(unsigned long))) == NULL)
    {
        fprintf(stderr, "calloc for rinst_a failed..exit\n");
        exit(0);
    }
    bloom_init();
    
    srand(seed_value);

    fprintf(stderr, "begin to test...size of PC: %d, sizeof instr:%d\n",
    	       sizeof(md_addr_t), sizeof(md_inst_t));
    
 /*   for (i=0; i < bloom_n; i++)
    {
        low_rand = rand(); high_rand = rand(); 
        rpc_a[i] = (high_rand <<16 |low_rand) &0xffffffff;
        
        low_rand = rand(); high_rand = rand(); 
        rtpc_a[i] = (high_rand <<16 | low_rand) &0xffffffff;

        low_rand = rand(); high_rand = rand(); 
        rinst_a[i] = (high_rand <<16 | low_rand) &0xffffffff;

        bloom_insert((md_addr_t)rpc_a[i], (md_addr_t)rtpc_a[i], (md_inst_t)rinst_a[i]);
     }
   */ 
     for (i=0;flag != EOF ; i++) {
	//next line should read each line from file, but only take in the 3rd and 4th items.
	flag = fscanf(input," %*s %*s %x %x %*s %*s %*s\n", &rpc_a[i], &rtpc_a[i] );
	if (flag ==2) {
        	 low_rand = rand(); high_rand = rand(); 
        	 rinst_a[i] = (high_rand <<16 | low_rand) &0xffffffff;
		 

       		 //fprintf(stderr, "0x%x, 0x%x, 0x%x\n", rpc_a[i] ,rtpc_a[i], rinst_a[i]); 
		 bloom_insert((md_addr_t)rpc_a[i], (md_addr_t)rtpc_a[i], (md_inst_t)rinst_a[i]);

	
     	}
	else if (flag != EOF) fprintf(stderr, "Scan error in line %d\n", i+1);	 
     }
	i = i-2;
     for (; i >0; i--)
    {
        if (bloom_check(rpc_a[i], rtpc_a[i], rinst_a[i]) == 0)
           { 
              fprintf(stderr, "i: %d pc: 0x%x, tpc:0x%0x; inst:0x%x goes wrong!\n", i, rpc_a[i], rtpc_a[i], rinst_a[i]);
              exit(0);
            }
     }

     fprintf(stderr, "no miss...past test\n");
     
     bloom_concentration(bloom_filter, bloom_m);     
     
     /* degree_of_concentration(bloom_filter, bloom_m);*/
     fprintf(stderr, "testing false positive now...\n");
     i = 0; j = 0;
     while(i< TEST_LEN)
     {
        low_rand = rand(); high_rand = rand(); 
        rpc_b= high_rand <<16 | low_rand;        
        low_rand = rand(); high_rand = rand(); 
        rtpc_b = high_rand <<16 | low_rand;
        low_rand = rand(); high_rand = rand(); 
        rinst_b = high_rand <<16 | low_rand;
        
        conflict = 0;
         for (j=0; j<bloom_n; j++)
         {
             if (rpc_a[j] == rpc_b && rtpc_a[j] == rtpc_b && rinst_a[j] == rinst_b)
             {
                 conflict = 1;
                 break;
              }
         }
         if (conflict == 1)
             continue;
         else
         {
             i++;
             if (bloom_check(rpc_b, rtpc_b, rinst_b) == 1)
            { 
     //         fprintf(stderr, "False positive #:%d pc: 0x%x, tpc:0x%0x; inst:0x%x \n", i, rpc_b, rtpc_b, rinst_b);
	    if (false_positive %100 == 0) fprintf(stderr, ".");        
	    false_positive ++;
             }
         }
     }     
     fprintf(stderr, "\noccurrence %d (out of %d); \nfalse positive rate: %10.9f\n",
               false_positive, TEST_LEN, (double) false_positive/TEST_LEN);
     fprintf(stdout, "\noccurrence %d (out of %d); \nfalse positive rate: %10.9f\n",
               false_positive, TEST_LEN, (double) false_positive/TEST_LEN);
     fprintf(output, "occurrence %d (out of %d); \nfalse positive rate: %10.9f\n",
               false_positive, TEST_LEN, (double) false_positive/TEST_LEN);
     free(rpc_a); free(rtpc_a); free(rinst_a);
     bloom_free();
     
}

