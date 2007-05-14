#include "StdAfx.h"
#include "Environment.h"
#include <string.h>
#include "Beetle.h"
#include "CfgManager.h"
#include "defines.h"
#include <time.h>

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
	
	Left=GetBeetleNeighborCell(x,y,beetle->Direction,'L');
	Right=GetBeetleNeighborCell(x,y,beetle->Direction,'R');
	Front=GetBeetleNeighborCell(x,y,beetle->Direction,'F');

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
			A_Copulate(x,y,beetle);
			break;
	}

}


int CEnvironment::GetBeetleNeighborCell(int x, int y, char direction, char L_R_F, CBeetle ** beetle)
{
	int x_n,y_n;
	direction = RotateDirection(direction,L_R_F);
	
	Grid.GetNeigborCellCoords(x,y,&x_n,&y_n,direction);
	return Grid.GetCellContent(x_n,y_n, beetle);		
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
		for(I=0;I<Grid.G_Width;I++)
		{
			what = Grid.GetCellContent(I,J,&beetle);
			if (what==NOTHING) putc('.',stdout);
			if (what==FLOWER) putc('~',stdout);
			if (what==WALL) putc('W',stdout);
			if (what==BEETLE)
			{
				if (beetle->Direction == WEST)putc('<',stdout);
				if (beetle->Direction == NORTH)putc('^',stdout);
				if (beetle->Direction == EAST)putc('>',stdout);
				if (beetle->Direction == SOUTH)putc('V',stdout);
			}
		}
		printf("     ");
		for(I=0;I<Grid.G_Width;I++)
		{
			what=Grid.GetCellGrowingProbability(I,J);
			if (what==0) putc('.', stdout);
			if ((what>0)&&(what<50)) putc('o', stdout);
			if ((what>=50) && (what<100)) putc('O',stdout);

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
	int I,J,K,L,M;
	int a,b;
	char brain[BRAIN_D1][BRAIN_D2][BRAIN_D3][BRAIN_D4];
	int expectOnPartner [EXPECT_ON_PARTNER_D1][EXPECT_ON_PARTNER_D2];
	//children oriented Beetle
	for (I=0;I<BRAIN_D1;I++)
		for(J=0;J<BRAIN_D2;J++)
			for(K=0;K<BRAIN_D3;K++)
				for(L=0;L<BRAIN_D4;L++)
					//beetle tries to copulate always if there is a beetle in front of them
					if (K==(BEETLE-1))brain [I][J][K][L]=A_COPULATE;
					else brain [I][J][K][L]=RandInBound(NUM_ACTIONS-1); //A_COPULATE is the last action
	char direction = RandInBound(4);
	int energy=1+RandInBound(MAX_ENERGY);
	
	for (M=0;M<EXPECT_ON_PARTNER_D1;M++)
	{
		expectOnPartner [M][0]= 0; expectOnPartner [M][1]=CBeetle::GetExpectOnPartnerMax(M);
		//too strict, no children occur then		 		
	}
	int hungryThreshold = RandInBound(MAX_ENERGY);
	int invInChild = RandInBound(MAX_ENERGY);
	int learnAbility= RandInBound(MAX_LEARN_ABILITY);
	//general Beetle
	/*
	for (I=0;I<BRAIN_D1;I++)
		for(J=0;J<BRAIN_D2;J++)
			for(K=0;K<BRAIN_D3;K++)
				for(L=0;L<BRAIN_D4;L++)
					//beetle tries to copulate only if there is a beetle in front of them
					if (K==(BEETLE-1))brain [I][J][K][L]=RandInBound(NUM_ACTIONS);
					else brain [I][J][K][L]=RandInBound(NUM_ACTIONS-1); //A_COPULATE is the last action
	char direction = RandInBound(4);
	int energy=1+RandInBound(MAX_ENERGY);
	
	for (M=0;M<EXPECT_ON_PARTNER_D1;M++)
	{			 
		a=RandInBound(CBeetle::GetExpectOnPartnerMax(M));
		b=RandInBound(CBeetle::GetExpectOnPartnerMax(M));
		if (a<=b){expectOnPartner [M][0]= a;expectOnPartner [M][1]= b;}
		else {expectOnPartner [M][0]= b;expectOnPartner [M][1]= a;}
	}
	int hungryThreshold = RandInBound(MAX_ENERGY);
	int invInChild = RandInBound(MAX_ENERGY);
	int learnAbility= RandInBound(MAX_LEARN_ABILITY);
	*/
	CBeetle * beetle;
	beetle = new CBeetle(0,brain,direction,energy,expectOnPartner,hungryThreshold,invInChild,learnAbility);

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
	srand( (unsigned)time( NULL ) );
	int I,J,K;
	CBeetle * beetle;
	for (K=0;K<60;K++)
	{
		I=RandInBound(Grid.G_Width);
		J=RandInBound(Grid.G_Height);
		beetle=CreateRandomBeetle();
		Grid.SetCellContent(BEETLE,I,J,beetle);
	}
			
	//if (false==CfgMng.LoadBeetles(&Grid_Next,btl_filename))return false;
	
	Grid_Next=Grid;
}

//tries agains probability to plant a flower on the x,y.
bool CEnvironment::MakeFlowerGrow(int x, int y)
{
	int prob = Grid.GetCellGrowingProbability(x,y);
	if (prob> RandInBound(100)) 
	{
		if (true == Grid_Next.SetCellContent(FLOWER,x,y))
			return true;
	}
	return false;
}

/**
* Public method:
* Desc: Realises the intention of one beetle to copulate.
* System dependence:
* Usage comments: Used as whole action from beetles brain, contains all checks of conditions.
* @return (Return values - meaning) : true - child(ren) created, false - no copulation
* @param name [descrip](Parameters - meaning):x,y - coordinates of the beetle, who intends to copulate. beetle - the beetle's reference.
* @throws name [descrip](Exceptions - meaning)
*/
bool CEnvironment::A_Copulate(int x, int y, CBeetle * beetle)
{
	CBeetle * beetle2 = NULL;
	int what = GetBeetleNeighborCell(x,y,beetle->Direction,'F', &beetle2);
	if (what != BEETLE) return false;

	//check my conditions
	if ((beetle->IsExpectOnPartnerSatisfied(EXPECT_ENERGY, beetle2->Energy)) &&
		(beetle->IsExpectOnPartnerSatisfied(EXPECT_AGE, beetle2->Age))&&
		(beetle->IsExpectOnPartnerSatisfied(EXPECT_INVINCHILD, beetle2->InvInChild))&&
		(beetle->IsExpectOnPartnerSatisfied(EXPECT_LEARNABILITY, beetle2->LearnAbility)))
	
	if (beetle2->Energy >= beetle2->InvInChild)
	//check his conditions
	if ((beetle2->IsExpectOnPartnerSatisfied(EXPECT_ENERGY, beetle->Energy)) &&
		(beetle2->IsExpectOnPartnerSatisfied(EXPECT_AGE, beetle->Age))&&
		(beetle2->IsExpectOnPartnerSatisfied(EXPECT_INVINCHILD, beetle->InvInChild))&&
		(beetle2->IsExpectOnPartnerSatisfied(EXPECT_LEARNABILITY, beetle->LearnAbility)))

	if (beetle->Energy >= beetle->InvInChild)
	{
		//check if there is a space next to both of beetles( 4 possibile cells)
		int neigh[4][3];//1st column - what, 2nd - x, 3rd - y
		int x2,y2;
		int free_n=0; //number of free cell from the 4 of the neighborhood 
		Grid.GetNeigborCellCoords(x,y,&x2,&y2,beetle->Direction);//get coords of beetle2

			Grid.GetNeigborCellCoords(x,y,&(neigh[0][1]),&(neigh[0][2]),RotateDirection(beetle->Direction,'L'));
			Grid.GetNeigborCellCoords(x,y,&(neigh[1][1]),&(neigh[1][2]),RotateDirection(beetle->Direction,'R'));
			Grid.GetNeigborCellCoords(x2,y2,&(neigh[2][1]),&(neigh[2][2]),RotateDirection(beetle->Direction,'L'));
			Grid.GetNeigborCellCoords(x2,y2,&(neigh[3][1]),&(neigh[3][2]),RotateDirection(beetle->Direction,'R'));

			//get content of neighbor cells and count the number of free ones
			int I,J;
			for (I=0;I<4;I++)
			{
				neigh[I][0]=Grid.GetCellContent(neigh[I][1],neigh[I][2]);
				if ((neigh[I][0]==FLOWER) ||(neigh[I][0]==NOTHING))
					neigh[I][0]=NOTHING; free_n++;
			}
			
			//if there is no free cell in neighborhood, new beetle cannot be born
			if (free_n== 0 )return false;
			
			//take random one from free neighbors
			int rand_n = RandInBound (free_n);
			rand_n++;
			for (J=0;J<4;J++)
				if (neigh[J][0]==NOTHING) 
				{
					rand_n--;
					if (rand_n==0)
						break;
				}
			//J is now the index of the chosen neighbor
		
			beetle->ConsumeEnergy(beetle->InvInChild);
			beetle2->ConsumeEnergy(beetle2->InvInChild);

			CBeetle * beetle_child=beetle->CreateChild(beetle2);
			if (Grid.SetCellContent(BEETLE,neigh[J][1],neigh[J][2],beetle_child))
				return true;
			else return false;
	}

	
	

	//

	return true;
}

char CEnvironment::RotateDirection(char direction, char L_R_F)
{
	//there are 4 directions: W=0,N=1,E=2,S=3, so the "right" adds 1 and "left" subtracts 1
	if (L_R_F== 'L') { direction-=1; if (direction<0) direction=3; }
	if (L_R_F== 'R') { direction+=1;direction%=4;}
	//if (L_R_F== 'F') ;
	return direction;
}
