// Abeetles.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "RunLife.h"
#include "CfgManager.h"

#ifndef _CRT_RAND_S 
	#define _CRT_RAND_S
#endif;
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>


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
    errno_t         err=0;
	

	#ifdef _CRT_RAND_S
		//printf("Hura");
		//err = rand_s(&number);

	#endif;
	number=rand();

    
       if (err != 0)
    {
       printf("The rand_s function failed!\n");
	   return 0;
    }
	unsigned int Res = ((int)((((double)number /(double) RAND_MAX ) * bound))) % bound;
    return Res;

}