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
	
	//Init Grid and Grid_Next (with sizes, flowers probability, walls and beetles)
	CfgMng.GetGridInit(&Grid);
	CfgMng.GetGridInit(&Grid_Next);
}

CEnvironment::~CEnvironment(void)
{
}





void CEnvironment::MakeBeetleAction(int x, int y)
{
	int Left,Front,Right; //content of Beetle's neighbor cells
	CBeetle * beetle=NULL;
	Grid.GetCellContent(x,y,&beetle);
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
	CBeetle * beetle=NULL;
	Grid.GetCellContent(oldx,oldy,&beetle);
	int x=oldx;
	int y=oldy;
	Grid.GetNeigborCellCoords(oldx,oldy,&x,&y,direction);
	
	//check, whether other beetle has decided to go to same cell sooner:
	if (Grid_Next.GetCellContent(x,y)==BEETLE){} // do nothing, the first beetle goes there.
	else if (Grid_Next.GetCellContent(x,y)==WALL) {}// do nothing, there is a wall
	else
	{		
		//step costs some energy
		int Res=beetle->ConsumeEnergy(A_STEP_COSTS);
		//if beetle is dead
		if (Res==DEAD) 
		{	
			beetle->Die();
			delete(beetle);
			Grid.SetCellContent(NOTHING,oldx,oldy);// even in old grid beetle must be removed - it would be reference to deleted memory
			Grid_Next.SetCellContent(NOTHING,oldx,oldy);//in next grid the beetle is on same position as in old one.
		}
		//if beetle is alive, he makes the step
		else
		{
			//if there is a flower
			if (Grid.GetCellContent(x,y)==FLOWER) 
				beetle->AddEnergy(beetle->EnergyFromFlower());

			Grid_Next.SetCellContent(NOTHING, oldx, oldy);
			Grid_Next.SetCellContent(BEETLE,x,y,beetle);			
		}
	
	}	
}



//Should be called at the end of a time slice - rewrites Grid with Grid_Next
void CEnvironment::NextTime(void)
{
	int I,J;
	//TODO: use overloaded operator '='
	Grid=Grid_Next;
}
