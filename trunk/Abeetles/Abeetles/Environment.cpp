#include "StdAfx.h"
#include "Environment.h"
#include <string.h>
#include "Beetle.h"
#include "CfgManager.h"
#include "defines.h"

CEnvironment::CEnvironment(void)
{
	//Set values of options of environment and beetles
	CfgMng.GetOptionsInit();
	//Set size and start index of the Grid
	CfgMng.GetGridShape(&G_FirstIndex,&G_Width,&G_Height);
	//Init Grid and Grid_Next (with flowers probability, walls and beetles)
	CfgMng.GetGridInit(Grid,G_FirstIndex,G_Width,G_Height);
	CfgMng.GetGridInit(Grid_Next,G_FirstIndex,G_Width,G_Height);
}

CEnvironment::~CEnvironment(void)
{
}




int CEnvironment::GetCell(int x, int y)
{
	if ((x<0) ||(x>=(G_FirstIndex+G_Width))||(y<0)||(y>=(G_FirstIndex+G_Height))) return -1;
	else return Grid [x][y][0] ;
}

void CEnvironment::MakeBeetleAction(int x, int y)
{
	int Left,Front,Right; //content of Beetle's neighbor cells
	CBeetle * beetle= (CBeetle *)Grid[x][y][1];
	printf ("E:%dX:%dY:%d",beetle->GetEnergy(),x,y);
	
	Left=GetBeetleNeighborCell(x,y,'L');
	Right=GetBeetleNeighborCell(x,y,'R');
	Front=GetBeetleNeighborCell(x,y,'F');

	int action = beetle->Decide(Left,Front,Right);

	switch (action) 
	{
		case A_STEP: 
			A_Step(x,y,beetle->GetDirection());
			break;			
		case A_ROTATERIGHT: 
			beetle->A_RotateRight();
			break;
		case A_ROTATELEFT: 
			beetle->A_RotateLeft();
			break;
		case A_WAIT:
			break;
		case A_COPULATE:
			break;
	}

}

int CEnvironment::GetBeetleNeighborCell(int x, int y, char l_r_f)
{
	return 0;
}

void CEnvironment::A_Step(int oldx, int oldy, char direction)
{
	CBeetle * beetle= (CBeetle *) Grid[oldx][oldy][1];
	int x=oldx;
	int y=oldy;

	
	switch (direction)
	{
	case WEST:
		if (x==G_FirstIndex) x=WestBorder();
			else x=x-1;
		break;
	case NORTH:
		if (y==G_FirstIndex) y=NorthBorder();
			else y=y-1;
		break;
	case EAST:
		if (x==G_FirstIndex+G_Width-1) x=EastBorder();
			else x=x+1;
		break;
	case SOUTH:
		if (y==G_FirstIndex+G_Height-1) y=SouthBorder();
			else y=y+1;
		break;
	}
	
	//check, whether other beetle has decided to go to same cell sooner:
	if (Grid_Next[x][y][0]==BEETLE){} // do nothing, the first beetle goes there.
	else
	{		
		//step costs some energy
		int Res=beetle->ConsumeEnergy(A_STEP_COSTS);
		//if beetle is dead
		if (Res==DEAD) 
		{	
			beetle->Die();
			delete(beetle);
			Grid[oldx][oldy][1]=0;
			Grid_Next[oldx][oldy][0]=NOTHING;
			Grid_Next[oldx][oldy][1]=0;
		}
		//if beetle is alive, he makes the step
		else
		{
			//if there is a flower
			if (GetCell(x,y)==FLOWER) 
				beetle->AddEnergy(beetle->EnergyFromFlower());

			Grid_Next[oldx][oldy][0]=NOTHING;
			Grid_Next[oldx][oldy][1]=0;
			Grid_Next[x][y][0]=BEETLE;
			Grid_Next[x][y][1]=(int)beetle;
		}
	
	}	
}

int CEnvironment::WestBorder(void)
{
	return G_FirstIndex+G_Width-1;
}

int CEnvironment::NorthBorder(void)
{
	return G_FirstIndex+G_Height-1;
}

int CEnvironment::EastBorder(void)
{
	return G_FirstIndex;
}

int CEnvironment::SouthBorder(void)
{
	return G_FirstIndex;
}

//Should be called at the end of a time slice - rewrites Grid with Grid_Next
void CEnvironment::NextTime(void)
{
	int I,J;
	for (I=G_FirstIndex;I<(G_FirstIndex+G_Width);I++)
		for (J=G_FirstIndex;J<(G_FirstIndex+G_Height);J++)
		{
			Grid[I][J][0]=Grid_Next[I][J][0];
			Grid[I][J][1]=Grid_Next[I][J][1];

		}

}
