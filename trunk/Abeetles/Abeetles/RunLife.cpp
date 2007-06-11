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
	CEnvironment env;
	if (false == env.CreateRandomEnv()) return EXIT_FAILURE ;
	//env.LoadEnv("sb_t2.txt",MAP_BMP_FILE);
	int jumpTime;

	//First, output to console the situation at the beginning
	printf("SP:%d,SI:%d\n",sizeof(int*),sizeof(int));
	printf("Width: %d\n",env.Grid.G_Width);
	printf("\nTime:%d",env.Time);
	if (env.DisplayOn)
	{
		printf(" NumBeetles: %d, NumBirths: %d, NumFlowers: %d ",env.Statist.NumBeetles,env.Statist.NumBirths,env.Statist.NumFlowers);		
		env.PrintEnv();		
	}

	if (false==DialogWithUser(&env,&jumpTime)) exit(EXIT_SUCCESS);

	env.NextTime();
	
	//Zivot
	for (;;)
	{
		//go through all environment, make actions of all beetles and try grow a flower in all empty cells
		for(I=0;I<env.Grid_Past.G_Width;I++)
			for(J=0;J<env.Grid_Past.G_Height;J++)
			{
				if (env.Grid_Past.GetCellContent(I,J)==BEETLE) env.MakeBeetleAction(I,J);
				if (env.Grid_Past.GetCellContent(I,J)==NOTHING) env.MakeFlowerGrow(I,J);
				//if there is a wall, flower of something bad, do nothing
			}

		//output to console
		printf("\nTime:%d",env.Time);
		if (env.DisplayOn)
		{
			printf(" NumBeetles: %d, NumBirths: %d, NumFlowers: %d ",env.Statist.NumBeetles,env.Statist.NumBirths,env.Statist.NumFlowers);		
			env.PrintEnv();	
		}
		
		if (jumpTime>0) jumpTime--;
		else	
			if (false==DialogWithUser(&env,&jumpTime)) break;
				
		env.NextTime();
		if (env.Time>=MAXTIME) break;

	}
	return EXIT_SUCCESS;
}
/**
* Static method: DialogWithUser
* Desc: Encapsulates communication with user after 1 time slice.
* System dependence: no 
* Usage comments: communication through std input and output
* @return (Return values - meaning) : true - go on running Environment, false - finnish it without saving
* @param name [ descrip](Parameters - meaning): env - reference to environment being run. jumpTime - number of time slices without users input. Can be modified in this method according to users wishes.
* @throws name [descrip](Exceptions - meaning)
*/
bool CRunLife::DialogWithUser(CEnvironment * env, int* jumpTime)
{
	char fname [40];	
	char input;

	//communication with user
	printf("(quit: x + Enter, continue: Enter, set time for not stopping: n\n save: s, save statistics: t, Display on/off: d): ");
	if (input = _getch()) // (_kbhit()) - zjisteni, byla-li stisknuta klavesa
	{
		//input = _getch();
		//input = getc(stdin); //if this function is used, any key +Enter is read as two keys - key and next time program does not wait but uses the Enter.
		if (input == QUIT_CHAR) return false;
		if (input== 's') 
		{
			sprintf_s (fname,40,"sb_t%d.txt",env->Time);
			CfgMng.SaveBeetles(&env->Grid,fname);
		}
		if (input =='t')
		{
			env->CountStatistics();
			sprintf_s(fname,40,"stat_t%d.txt",env->Time);
			env->Statist.SaveActAgrStatist(fname,env->Time);
			sprintf_s(fname,40,"histStat_t%d.csv",env->Time);
			env->Statist.SaveActHistStatist(fname,env->Time,&env->Grid);
		}
		if (input =='d')
		{
			if (env->DisplayOn) env->DisplayOn=false;
			else env->DisplayOn=true;
		}
		if (input =='n')
		{
			if (env->DisplayOn) env->DisplayOn=false;
			printf("\nNum of time for not stopping run: ");
			scanf("%d",jumpTime);
		}
	}
	printf("\n\n");
	return true;
}
