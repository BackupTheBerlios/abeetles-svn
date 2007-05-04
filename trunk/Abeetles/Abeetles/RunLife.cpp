#include "StdAfx.h"
#include "RunLife.h"
#include "Environment.h"
#include "Beetle.h"
#include <iostream>
#include "defines.h"

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
	printf("SP:%d,SI:%d\n",sizeof(int*),sizeof(int));
	printf("Width: %d\n",Env.Grid.G_Width);
	//printf("MaxEnergy: %d\n",CBeetle::EnergyMax_C);
	int Time=0;
	//Zivot
	for (Time=0;Time<MAXTIME;Time++)
	{
		printf("\nT:%d ",Time);		
		Env.PrintEnv();

		if (getc(stdin) == QUIT_CHAR) break;

		for(I=0;I<Env.Grid.G_Width;I++)
			for(J=0;J<Env.Grid.G_Width;J++)
			{
				if (Env.Grid.GetCellContent(I,J)==BEETLE) Env.MakeBeetleAction(I,J);
				//if (Env.Grid.GetCellContent(I,J)==NOTHING); //Env.MakeFloweGrow(I,J);
				//if there is a wall, flower of something bad, do nothing
			}
		Env.NextTime();
	}
	return 0;
}
