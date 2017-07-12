// Arnold Lee
// UIN #665453451
// CS 385 PROG 4
// CS ACCOUNT ID: temp109

// 12/09/2006

// disk sturcture

#ifndef _DISK_H
#define _DISK_H


#include <stdio.h>
#include <cstdlib> 
#include <errno.h>
#include <iostream>
using namespace::std;
#include <string.h>
#include <vector>
#include <strings.h>
#include <unistd.h>
#include <assert.h>
#include <iomanip>
#include "matrix.h"
#include <string>
using std::string;

#include "time.h"
#include "timer.h"

class disk
{
      public:
             disk ();
             disk (int h,int s,int c);
             
             int total_cylinder();
             int current_cylinder();
             int current_sector();
             int current_head();
             int total_sector();
             int total_heads();
             
             void resizer (int h,int s,int c);
             
             void writedisk(int data, int h,int s,int c);
             int readdisk(int h,int s,int c);
             void delay(int msec);
             
             bool busy ();

             
      private:
              int headcurrent;
              int sectorcurrent;
              int cylindercurrent;
              int htotal;
              int stotal;
              int ctotal;
              timer moving;
              vector < matrix <int> > core;
};

disk::disk()
{
   headcurrent = 0;
   sectorcurrent = 0;
   cylindercurrent = 0;
   htotal = 0;
   stotal = 0;
   ctotal = 0;
}

disk::disk(int h,int s,int c)
{
   headcurrent = 1;
   sectorcurrent = 1;
   cylindercurrent = 1;
   htotal = h;
   stotal = s;
   ctotal = c;
   
   core.resize(h);
   
   for (int x = 0; x < h ; x++)
   {
       core[x].resize(s,c);
       
       for (int y = 0; y < s; y++)
        for (int z = 0; z < c; z++)
          core[x][y][z] = 0;
   }          
}   

int disk::total_cylinder()
{
    return ctotal;
}

int disk::current_cylinder()
{
    return  cylindercurrent;  
}

int disk::current_sector()
{
    return sectorcurrent;
}

int disk::current_head()
{
    return headcurrent;
}

int disk::total_sector()
{
    return stotal;
}
             
int disk::total_heads()
{
     return htotal;   
}

void disk::resizer(int h,int s,int c)
{
     
   moving.start();
   headcurrent = 1;
   sectorcurrent = 1;
   cylindercurrent = 1;
   htotal = h;
   stotal = s;
   ctotal = c;
   
   core.resize(h);
   
   for (int x = 0; x < h ; x++)
   {
       core[x].resize(s,c);
       
       for (int y = 0; y < s; y++)
        for (int z = 0; z < c; z++)
          core[x][y][z] = 0;
   }          
   
   delay(1000);
   moving.stop();
}

int disk::readdisk(int h,int s,int c)
{
   
   moving.start();
   delay(int(1+ (0.003 * abs(c - cylindercurrent))));
   
   headcurrent = h;
   sectorcurrent = s;
   cylindercurrent = c;
   
   moving.stop();
   return  core[h-1][s-1][c-1];
}

void disk::writedisk(int data,int h,int s,int c)
{
       moving.start();
    
       core[h-1][s-1][c-1] = data;
       
       delay(int(1+ (0.003 * abs(c - cylindercurrent))));
    
       headcurrent = h;
       sectorcurrent = s;
       cylindercurrent = c;
    
       moving.stop();
    
}

void disk::delay(int msec)
{
    clock_t endpoint = msec + clock();
    while (endpoint > clock());
}

bool disk::busy()
{
     return moving.active();
}


#endif
