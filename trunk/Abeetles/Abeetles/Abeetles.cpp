// Abeetles.cpp : Defines the entry point for the console application.
//

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

