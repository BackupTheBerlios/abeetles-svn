// Abeetles.cpp : Defines the entry point for the console application.
//
#define _CRT_RAND_S
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "stdafx.h"
#include "RunLife.h"
#include "CfgManager.h"

//Global variables
CfgManager CfgMng; 


int _tmain(int argc, _TCHAR* argv[])
{	
	CRunLife::run();
	printf("\nPress any key to finnish\n");
	getc(stdin);
	return 0;
}

int RandInBound (int bound)
{
    unsigned int    number;
    errno_t         err;
	
	#ifdef _CRT_RAND_S 
	#define _CRT_RAND_S
		//printf("Hura");
		err = rand_s(&number);
	#endif;

    
	
    // Display 10 random integers in the range [ 1,10 ].
    if (err != 0)
    {
       printf("The rand_s function failed!\n");
	   exit;
    }
    return((unsigned int) ((double)number /(double) UINT_MAX * bound) - 1);

}