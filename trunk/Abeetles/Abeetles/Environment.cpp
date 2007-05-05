#include "StdAfx.h"
#include "Environment.h"
#include <string.h>
#include "Beetle.h"
#include "CfgManager.h"
#include "defines.h"

extern int RandInBound (int bound);

CEnvironment::CEnvironment(void)
{
	//Set values of options of environment and beetles
	CfgMng.LoadCfgFile("BeetleCfg.txt");
	
	//Init Grid and Grid_Next (with sizes, flowers probability, walls and beetles)
	LoadEnv("Beetle.txt",MAP_BMP_FILE);
}

CEnvironment::CEnvironment(char * cfg_filename,char * btl_filename, wchar_t * map_filename)
{	
	//Set values of options of environment and beetles
	CfgMng.LoadCfgFile(cfg_filename);

	//Init Grid and Grid_Next (with sizes, flowers probability, walls and beetles)
	LoadEnv(btl_filename,map_filename);
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

bool CEnvironment::PrintEnv(void)
{
	int I,J;
	CBeetle * beetle;
	int what=NOTHING;
	
	printf("\n");
	for(J=0;J<Grid.G_Height;J++)
	{
		for(I=0;I<Grid.G_Height;I++)
		{
			what = Grid.GetCellContent(I,J,&beetle);
			if (what==NOTHING) putc('.',stdout);
			if (what==FLOWER) putc('$',stdout);
			if (what==WALL) putc('W',stdout);
			if (what==BEETLE)
			{
				if (beetle->Direction == WEST)putc('<',stdout);
				if (beetle->Direction == NORTH)putc('^',stdout);
				if (beetle->Direction == EAST)putc('>',stdout);
				if (beetle->Direction == SOUTH)putc('V',stdout);
			}
		}
		printf("\n");
	}
	printf("\n");
	
	return true;
}
/**
* Public method:
* Desc: Creates a random beetle and places it on given coords
* System dependence:
* Usage comments:
* @return (Return values - meaning) :
* @param name [ descrip](Parameters - meaning):
* @throws name [descrip](Exceptions - meaning)
*/

CBeetle * CEnvironment::CreateRandomBeetle()
{
	int I,J,K,L;
	int energy=1+RandInBound(MAX_ENERGY);
	char direction = RandInBound(4);
	int hungryThreshold = RandInBound(MAX_ENERGY);
	char brain[2][4][4][4];
	for (I=0;I<BRAIN_D1;I++)
		for(J=0;J<BRAIN_D2;J++)
			for(K=0;K<BRAIN_D3;K++)
				for(L=0;L<BRAIN_D4;L++)
					brain [I][J][K][L]=RandInBound(NUM_ACTIONS);
	
	CBeetle * beetle;
	beetle = new CBeetle(energy,direction,hungryThreshold,brain);


	return beetle;
}

bool CEnvironment::LoadEnv(char * btl_filename, wchar_t * map_filename)
{
	int FI,W,H;
	if (false==CfgMng.LoadGridShape(&FI,&W,&H)) return false;
	if (false==Grid.SetGridShape(FI,W,H)) return false;
	//if (false==Grid_Next.SetGridShape(FI,W,H)) return false;

	//First part - init environment: Loads environment without beetles
	if (false==CfgMng.LoadMapFromBmp(&Grid,map_filename))return false;
	//if (false==CfgMng.LoadMapFromBmp(&Grid_Next,map_filename))return false;

	//Second part - load beetles and add them to half finished environment
	
	if (false==CfgMng.LoadBeetles(&Grid,btl_filename))return false;
	//if (false==CfgMng.LoadBeetles(&Grid_Next,btl_filename))return false;
	
	Grid_Next=Grid;

	return true;
}

bool CEnvironment::SaveEnv(char * btl_filename)
{
	if (false==CfgMng.SaveBeetles(&Grid,btl_filename))return false;
	return true;
}

bool CEnvironment::CreateRandomEnv(void)
{
	int FI,W,H;
	if (false==CfgMng.LoadGridShape(&FI,&W,&H)) return false;
	if (false==Grid.SetGridShape(FI,W,H)) return false;
	//if (false==Grid_Next.SetGridShape(FI,W,H)) return false;

	//First part - init environment: Loads environment without beetles
	if (false==CfgMng.LoadMapFromBmp(&Grid,MAP_BMP_FILE))return false;
	//if (false==CfgMng.LoadMapFromBmp(&Grid_Next,map_filename))return false;

	//Second part - load beetles and add them to half finished environment
	int I,J,K;
	CBeetle * beetle;
	for (K=0;K<20;K++)
	{
		I=RandInBound(Grid.G_Width);
		J=RandInBound(Grid.G_Height);
		beetle=CreateRandomBeetle();
		Grid.SetCellContent(BEETLE,I,J,beetle);
	}
			
	//if (false==CfgMng.LoadBeetles(&Grid_Next,btl_filename))return false;
	
	Grid_Next=Grid;
}
