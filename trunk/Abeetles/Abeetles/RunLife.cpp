#include "StdAfx.h"
#include "RunLife.h"
#include "Environment.h"
#include "Beetle.h"
#include <conio.h>
#include "defines.h"
//#include <mscorlib.dll>
//using namespace System;


CRunLife::CRunLife(void)
{
}

CRunLife::~CRunLife(void)
{
}

int CRunLife::run(void)
{
	int I,J;
	CEnvironment Env;
	Env.CreateRandomEnv();
	//Env.LoadEnv("sb_t2.txt",MAP_BMP_FILE);

	printf("SP:%d,SI:%d\n",sizeof(int*),sizeof(int));
	printf("Width: %d\n",Env.Grid.G_Width);
	char fname [15];

	int Time=0;
	char input;	
	//Zivot
	for (Time=0;Time<MAXTIME;Time++)
	{
		printf("\nT:%d ",Time);		
		Env.PrintEnv();		

		//communication with user
		printf("(quit: x + Enter, continue: Enter, save: s + Enter): ");
		//if (input = _getch())
		//{
			input = getc(stdin);
			if (input == QUIT_CHAR) break;
			sprintf_s (fname,15,"sb_t%d.txt",Time);
			if (input== 's') CfgMng.SaveBeetles(&Env.Grid,fname);
		//}
		printf("\n\n");
		
		for(I=0;I<Env.Grid.G_Width;I++)
			for(J=0;J<Env.Grid.G_Width;J++)
			{
				if (Env.Grid.GetCellContent(I,J)==BEETLE) Env.MakeBeetleAction(I,J);
				if (Env.Grid.GetCellContent(I,J)==NOTHING) Env.MakeFlowerGrow(I,J);
				//if there is a wall, flower of something bad, do nothing
			}
		
		Env.NextTime();

	}
	return 0;
}
