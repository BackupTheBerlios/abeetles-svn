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
	char fname [40];	
	char input;

	//First, output to console the situation at the beginning
	printf("SP:%d,SI:%d\n",sizeof(int*),sizeof(int));
	printf("Width: %d\n",Env.Grid.G_Width);
	printf("\nTime:%d NumBeetles: %d, NumBirths: %d, NumFlowers: %d ",Env.Time,Env.Statist.NumBeetles,Env.Statist.NumBirths,Env.Statist.NumFlowers);		
	Env.PrintEnv();		
	printf("(quit: x + Enter, continue: Enter, save: s + Enter, save statistics: t + Enter): ");
		if (input = _getch())
		{
			//input = getc(stdin); //if this function is used, any key +Enter is read as two keys - key and next time program does not wait but uses the Enter.
			if (input == QUIT_CHAR) return EXIT_SUCCESS;
			if (input== 's') 
			{
				sprintf_s (fname,40,"sb_t%d.txt",Env.Time);
				CfgMng.SaveBeetles(&Env.Grid,fname);
			}
			if (input =='t')
			{
				sprintf_s(fname,40,"stat_t%d.txt",Env.Time);
				Env.Statist.SaveStatist(fname,Env.Time);
			}

		}
	printf("\n\n");

	Env.NextTime();

	
	//Zivot
	for (;;)
	{
		//go through all environment, make actions of all beetles and try grow a flower in all empty cells
		for(I=0;I<Env.Grid_Past.G_Width;I++)
			for(J=0;J<Env.Grid_Past.G_Height;J++)
			{
				if (Env.Grid_Past.GetCellContent(I,J)==BEETLE) Env.MakeBeetleAction(I,J);
				if (Env.Grid_Past.GetCellContent(I,J)==NOTHING) Env.MakeFlowerGrow(I,J);
				//if there is a wall, flower of something bad, do nothing
			}

		//output to console
		printf("\nTime:%d NumBeetles: %d, NumBirths: %d, NumFlowers: %d ",Env.Time,Env.Statist.NumBeetles,Env.Statist.NumBirths,Env.Statist.NumFlowers);		
		Env.PrintEnv();	

		//communication with user
	printf("(quit: x + Enter, continue: Enter, save: s + Enter, save statistics: t + Enter): ");
		if (input = _getch())
		{
			//input = getc(stdin); //if this function is used, any key +Enter is read as two keys - key and next time program does not wait but uses the Enter.
			if (input == QUIT_CHAR) break;
			if (input== 's') 
			{
				sprintf_s (fname,40,"sb_t%d.txt",Env.Time);
				CfgMng.SaveBeetles(&Env.Grid,fname);
			}
			if (input =='t')
			{
				sprintf_s(fname,40,"stat_t%d.txt",Env.Time);
				Env.Statist.SaveStatist(fname,Env.Time);
			}
		}
		printf("\n\n");
		Env.NextTime();
		if (Env.Time>=MAXTIME) break;

	}
	return EXIT_SUCCESS;
}
