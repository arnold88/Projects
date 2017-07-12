import csv
import random

complete_data = list(csv.reader(open('original.txt', 'rb'), delimiter='\t'))

cess_tweets = [];
no_cess_tweets = [];

total_num_tweets =  len(complete_data);
cess_num = 1592;
no_cess_num = total_num_tweets - cess_num;

cess_sample = cess_num * 3/4;
no_cess_sample = no_cess_num * 3/4;

print ("Total number of Tweets = " + str(len(complete_data)));






for i in range (0,cess_num):
    cess_tweets.append(complete_data[i]);

for i in range (cess_num , total_num_tweets):
    no_cess_tweets.append(complete_data[i]);


print ("Cessation (after parsing) = " + str(len(cess_tweets)));
print("No Cessation (after parsing) = " + str(len(no_cess_tweets)));


cess_training = [];
no_cess_training = [];

cess_training = random.sample ( cess_tweets, cess_sample);
no_cess_training = random.sample ( no_cess_tweets, no_cess_sample);

print ("Size of Cessation Training Set = " + str(len(cess_training)));
print ("Size of No Cessation Training Set = " + str(len(no_cess_training)));

ct = open('cess_training.txt', 'w')
nct = open('no_cess_training.txt', 'w')




for item in cess_training:
        print >> ct , item[0] + "\t" + item[1] + "\t" + item[2] + "\t" + item[3] + "\t"+ item[4] + "\t"+ item[5] + "\t"+ item[6] + "\t" + item[7];
    


for item in no_cess_training:
        print >> nct , item[0] + "\t" + item[1] + "\t" + item[2] + "\t" + item[3] + "\t"+ item[4] + "\t"+ item[5] + "\t"+ item[6] + "\t" + item[7];

cess_validation = [item for item in cess_tweets if item not in cess_training];
no_cess_validation = [item for item in no_cess_tweets if item not in no_cess_training];

cv = open('cess_validation.txt', 'w')
ncv = open('no_cess_validation.txt', 'w')

print ("Size of Cessation Validation Set = " + str(len(cess_validation)));
print ("Size of No Cessation Validation Set = " + str(len(no_cess_validation)));

for item in cess_validation:
        print >> cv , item[0] + "\t" + item[1] + "\t" + item[2] + "\t" + item[3] + "\t"+ item[4] + "\t"+ item[5] + "\t"+ item[6] + "\t" + item[7];

for item in no_cess_validation:
        print >> ncv , item[0] + "\t" + item[1] + "\t" + item[2] + "\t" + item[3] + "\t"+ item[4] + "\t"+ item[5] + "\t"+ item[6] + "\t" + item[7];


ct.closed
nct.closed
cv.closed
ncv.closed




