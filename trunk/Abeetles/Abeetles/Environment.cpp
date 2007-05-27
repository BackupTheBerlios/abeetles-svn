#include "StdAfx.h"
#include "Environment.h"
#include <string.h>
#include "Beetle.h"
#include "CfgManager.h"
#include "defines.h"
#include <time.h>
#include <assert.h>

extern int RandInBound (int bound);

CEnvironment::CEnvironment(void)
{
	Time=0;

	//Set values of options of environment and beetles
	if (false == CfgMng.LoadCfgFile("BeetleCfg.txt"))
	{
		printf("Loading of cfg file %s was not successful.","BeetleCfg.txt");
		exit (EXIT_FAILURE);
	}

	//Init Grid_Past and Grid (with sizes, flowers probability, walls and beetles)	
	if (false == LoadEnv("Beetle.txt",MAP_BMP_FILE))
	{
		printf("Loading of environment bmp file %S or beetle %s file was not successful.",MAP_BMP_FILE,"Beetle.txt");
		exit (EXIT_FAILURE);
	}

	//load function of Age and EnergyFromFlower from bmp file	
	if (false == CfgMng.LoadEnergyFromFlowerFromBmp(CBeetle::EFF_Age, EFF_BMP_FILE))
	{
		printf("Loading of energy from flower bmp file %S was not successful.",EFF_BMP_FILE);
		exit (EXIT_FAILURE);
	}
}

CEnvironment::CEnvironment(char * cfg_filename,char * btl_filename, wchar_t * map_filename, wchar_t * eff_filename)
{	
	Time=0; //Remake to load it from some save file of the environment!

	//Set values of options of environment and beetles
	if (false == CfgMng.LoadCfgFile(cfg_filename))
	{
		printf("Loading of cfg file %s was not successful.",cfg_filename);
		exit (EXIT_FAILURE);
	}

	//Init Grid_Past and Grid (with sizes, flowers probability, walls and beetles)
	if (false == LoadEnv(btl_filename,map_filename))
	{
		printf("Loading of environment bmp file %S or beetle %s file was not successful.",map_filename,btl_filename);
		exit (EXIT_FAILURE);
	}

	//load function of Age and EnergyFromFlower from bmp file
	if (false == CfgMng.LoadEnergyFromFlowerFromBmp(CBeetle::EFF_Age, eff_filename))
	{
		printf("Loading of energy from flower bmp file %S was not successful.",eff_filename);
		exit (EXIT_FAILURE);
	}
}

CEnvironment::~CEnvironment(void)
{
}





void CEnvironment::MakeBeetleAction(int x, int y)
{
	int Left,Front,Right; //content of Beetle's neighbor cells
	CBeetle * beetle=NULL;
	Grid_Past.GetCellContent(x,y,&beetle);
	printf("E:%dX:%dY:%d",beetle->GetEnergy(),x,y); //debug info about beetles location
	
	//beetle looks around him
	Left=GetBeetleNeighborCell(x,y,beetle->Direction,'L');
	Right=GetBeetleNeighborCell(x,y,beetle->Direction,'R');
	Front=GetBeetleNeighborCell(x,y,beetle->Direction,'F');
	
	assert (! beetle->IsDead());

	int action = INVALID_NUM;
	//HA_COPULATE - hardwired action of every beetle, when there is another beetle in front of him
	bool newChild = false;
	if (Front==BEETLE)
	{
		action=HA_COPULATE;
		if (beetle->Energy > A_COPULATION_COSTS)
			{
				if (true == A_Copulate(x,y,beetle))
				{
					Statist.NumBeetles++;
					Statist.NumBirths++;
					beetle->ConsumeEnergy(A_COPULATION_COSTS);
					newChild = true;
				}
				//else beetle->ConsumeEnergy(A_WAIT_COSTS);
			}
			else beetle->Energy =0;
	}	
	// if there was no copulation or no child created, beetle decides what to do according to what he sees and whether he is hungry
	
	if (newChild==false) action = beetle->Decide(Left,Front,Right);

	assert(action!=INVALID_NUM);

	//int Res = 0; //whether is the beetle still alive -1==DEAD

	//IDEA: beetle learns himself: if beetle is at the same place for ...

	//he makes the action he decided to do
	switch (action) 
	{
		case A_STEP: 
			if (beetle->Energy > A_STEP_COSTS)
			{
				if (true ==A_Step(x,y,beetle->GetDirection())) // check, whether the step was really made
					beetle->ConsumeEnergy(A_STEP_COSTS);
				else beetle->ConsumeEnergy(A_WAIT_COSTS);
			}
			else beetle->Energy =0;
			break;			
		case A_ROTATERIGHT: 
			if (beetle->Energy > A_ROTATION_COSTS)
			{ 
				A_RotateRight(beetle);
				beetle->ConsumeEnergy(A_ROTATION_COSTS);
			}
			else beetle->Energy =0;
			break;
		case A_ROTATELEFT: 
			if (beetle->Energy > A_ROTATION_COSTS)
			{
				A_RotateLeft(beetle);
				beetle->ConsumeEnergy(A_ROTATION_COSTS);
			}
			else beetle->Energy =0;
			break;
/*		case A_WAIT:		
			if (beetle->Energy > A_WAIT_COSTS)
			{
				beetle->ConsumeEnergy(A_WAIT_COSTS);
			}
			else beetle->Energy =0;
			break;*/
		case HA_COPULATE:
				//realized beforehead.
			break;
	}

	if (beetle->IsDead()) 
		{	
			beetle->Die();
			Statist.NumBeetles--;
			delete(beetle);	beetle = NULL;
			Grid_Past.SetCellContent(NOTHING,x,y);// even in old grid beetle must be removed - it would be reference to deleted memory
			Grid.SetCellContent(NOTHING,x,y);//in next grid the beetle is on same position as in old one.
			return;
		}

	//when beetle meets some other beetle2 and didn't create child with beetle2
	// and the beetle is better = has more energy than him, he can learn something from beetle2 according to beetle's learning ability
	int b2_x, b2_y;
	CBeetle * beetle2=NULL;
	if ((newChild==false)&&(Front==BEETLE) && 
		(RandInBound(MAX_LEARN_ABILITY) < beetle->LearnAbility )) // beetles that have higher learnAbility, have higher probability, that they learn something
	{
		Grid_Past.GetNeigborCellCoords(x,y,&b2_x,&b2_y, beetle->Direction);
		Grid_Past.GetCellContent(b2_x,b2_y, &beetle2);
		if (beetle2 != NULL)
		{
			if (beetle2->Energy > beetle->Energy)
				beetle->LearnFrom(beetle2);
		}
	}


	beetle->Age++; //beetle is now 1 time slice older

	//add changed features to statistics:
	Statist.SumAge+=beetle->Age;
	Statist.SumEnergy+=beetle->Energy;
	Statist.SumNumChildren+=beetle->NumChildren;

}


int CEnvironment::GetBeetleNeighborCell(int x, int y, char direction, char L_R_F, CBeetle ** beetle)
{
	int x_n,y_n;
	direction = RotateDirection(direction,L_R_F);
	
	Grid_Past.GetNeigborCellCoords(x,y,&x_n,&y_n,direction);
	return Grid_Past.GetCellContent(x_n,y_n, beetle);		
}

/**
* Public method:
* Desc: Realizes one of the beetles actions
* System dependence:
* Usage comments: Called from CEnvironment::MakeBeetleAction()
* @return (Return values - meaning) : true - step was made, false - step was not made
* @param name [ descrip](Parameters - meaning):
* @throws name [descrip](Exceptions - meaning)
*/
bool CEnvironment::A_Step(int oldx, int oldy, char direction)
{
	CBeetle * beetle=NULL;
	Grid_Past.GetCellContent(oldx,oldy,&beetle);
	int x=oldx;
	int y=oldy;
	Grid_Past.GetNeigborCellCoords(oldx,oldy,&x,&y,direction);
	
	//check, whether other beetle has decided to go to same cell sooner:
	if (Grid.GetCellContent(x,y)==BEETLE) return false; // do nothing, the first beetle goes there.
	else if (Grid.GetCellContent(x,y)==WALL) return false;// do nothing, there is a wall
	else
	{		
			//if there is a flower
			if (Grid_Past.GetCellContent(x,y)==FLOWER) 
			{
				Statist.NumFlowers--;
				beetle->AddEnergy(beetle->EnergyFromFlower());
			}

			Grid.SetCellContent(NOTHING, oldx, oldy);
			Grid.SetCellContent(BEETLE,x,y,beetle);						
	}	
	return true;
}



//Should be called at the end of a time slice - rewrites Grid_Past with Grid
void CEnvironment::NextTime(void)
{
	Time++;
	Statist.NextTime(Time);
	Grid_Past=Grid;
}

bool CEnvironment::PrintEnv(void)
{
	int I,J;
	CBeetle * beetle;
	int what=NOTHING;
	
	printf("\n");

	//upper line of numbers
	putc(' ',stdout);
	for (I=0;I<Grid.G_Width;I++)
		putc((char)(I%10)+'0',stdout);
	printf("\n");

	for(J=0;J<Grid.G_Height;J++)
	{
		putc((char)(J%10)+'0',stdout); //left column of numbers
		for(I=0;I<Grid.G_Width;I++)
		{
			what = Grid.GetCellContent(I,J,&beetle);
			if (what==NOTHING) {putc('.',stdout);continue;}
			if (what==FLOWER) {putc('~',stdout);continue;}
			if (what==WALL) {putc('W',stdout);continue;}
			if (what==BEETLE)
			{
				if ((beetle->Age)==0) putc('*',stdout);
				else
				{
					if (beetle->Direction == WEST)putc('<',stdout);
					if (beetle->Direction == NORTH)putc('^',stdout);
					if (beetle->Direction == EAST)putc('>',stdout);
					if (beetle->Direction == SOUTH)putc('V',stdout);
				}
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
* Remarks: method sums up all restriction for beetles' genes, that exclude all genotype that are "non sense"
* @return (Return values - meaning) :
* @param name [ descrip](Parameters - meaning):
* @throws name [descrip](Exceptions - meaning)
*/

CBeetle * CEnvironment::CreateRandomBeetle()
{
	int I,J,K,L;
	//int a;
	char brain[BRAIN_D1][BRAIN_D2][BRAIN_D3][BRAIN_D4];
	int expectOnPartner [EXPECT_ON_PARTNER_D];
	//children oriented Beetle
	for (I=0;I<BRAIN_D1;I++)
		for(J=0;J<BRAIN_D2;J++)
			for(K=0;K<BRAIN_D3;K++)
				for(L=0;L<BRAIN_D4;L++)
				{
					//Special set for debugging:
						if ((I==1)&&(K==(FLOWER-1))) brain[I][J][K][L]=A_STEP;
						else
							brain [I][J][K][L]=RandInBound(NUM_ACTIONS);
				}
	char direction = RandInBound(4);
	int energy=10+RandInBound(MAX_ENERGY);
	
	
	//	ExpectOnPartner - Age [2] = 2B how much older / younger can be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much more than InvInChild
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 

	//for (M=0;M<EXPECT_ON_PARTNER_D;M++)
	expectOnPartner [0]= CBeetle::GetExpectOnPartnerMax(0); 
	expectOnPartner [1]= CBeetle::GetExpectOnPartnerMax(1); 
	expectOnPartner [2]= 6; 
	expectOnPartner [3]= 10; 
	expectOnPartner [4]=30;
	expectOnPartner [5]=30;
				 		
	
	int hungryThreshold = 1+RandInBound(MAX_ENERGY);
	int invInChild = 1+RandInBound(MAX_ENERGY);
	int learnAbility= 1+RandInBound(MAX_LEARN_ABILITY);

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
		expectOnPartner [M]= a;
	}
	int hungryThreshold = RandInBound(MAX_ENERGY);
	int invInChild = RandInBound(MAX_ENERGY);
	int learnAbility= RandInBound(MAX_LEARN_ABILITY);
	*/
	CBeetle * beetle;
	beetle = new CBeetle(CBeetle::CreateNewId(),0,brain,direction,energy,expectOnPartner,hungryThreshold,invInChild,learnAbility,0);
	/* Removed to CountStatistics()
	Statist.SumHungryThreshold+=hungryThreshold;
	Statist.SumInvInChild+=invInChild;
	Statist.SumLearnAbility+=learnAbility;*/


	return beetle;
}

bool CEnvironment::LoadEnv(char * btl_filename, wchar_t * map_filename)
{
	int FI,W,H;
	if (false==CfgMng.LoadGridShape(&FI,&W,&H)) return false;
	if (false==Grid_Past.SetGridShape(FI,W,H)) return false;
	//if (false==Grid.SetGridShape(FI,W,H)) return false;

	//First part - init environment: Loads environment without beetles
	if (false==CfgMng.LoadMapFromBmp(&Grid_Past,map_filename))return false;
	//if (false==CfgMng.LoadMapFromBmp(&Grid,map_filename))return false;

	//Second part - load beetles and add them to half finished environment
	
	if (false==CfgMng.LoadBeetles(&Grid_Past,btl_filename))return false;
	//if (false==CfgMng.LoadBeetles(&Grid,btl_filename))return false;
	
	Grid=Grid_Past;

	CountStatistics();

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
	if (false==Grid_Past.SetGridShape(FI,W,H)) return false;
	//if (false==Grid.SetGridShape(FI,W,H)) return false;

	//First part - init environment: Loads environment without beetles
	if (false==CfgMng.LoadMapFromBmp(&Grid_Past,MAP_BMP_FILE))return false;
	//if (false==CfgMng.LoadMapFromBmp(&Grid,map_filename))return false;

	//Second part - load beetles and add them to half finished environment
	srand( 100);//(unsigned)time( NULL ) );
	int I,J,K;
	CBeetle * beetle;
	for (K=0;K<20;K++)
	{
		I=RandInBound(Grid_Past.G_Width);
		J=RandInBound(Grid_Past.G_Height);
		beetle=CreateRandomBeetle();
		if (Grid_Past.SetCellContent(BEETLE,I,J,beetle))
			Statist.NumBeetles++;
		assert(beetle->GetEnergy()>0);
		printf("E:%dX:%dY:%d",beetle->GetEnergy(),I,J); //debug info about beetles location

	}
			
	//if (false==CfgMng.LoadBeetles(&Grid,btl_filename))return false;
	
	Grid=Grid_Past;
	CountStatistics();
	return true;
}

//tries agains probability to plant a flower on the x,y.
bool CEnvironment::MakeFlowerGrow(int x, int y)
{
	int prob = Grid_Past.GetCellGrowingProbability(x,y);
	if ((Grid.GetCellContent(x,y) == NOTHING) //a beetle might have made a step into this cell
		&&(prob> RandInBound(100))) 
	{
		
		if (true == Grid.SetCellContent(FLOWER,x,y))
		{
			Statist.NumFlowers++;
			return true;
		}
	}
	return false;
}

void CEnvironment::A_RotateLeft(CBeetle * beetle)//0,1,2,3 = West, North, East, South
{
	if (beetle->Direction>0) beetle->Direction--;
	else beetle->Direction=3;	
}

void CEnvironment::A_RotateRight(CBeetle * beetle)
{
	if (beetle->Direction<3) beetle->Direction++;
	else beetle->Direction=0;	
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
	if (beetle->IsExpectOnPartnerSatisfied(beetle2))
		//check his conditions
	{
		if (beetle2->IsExpectOnPartnerSatisfied(beetle))
		{
			//check if there is a space next to both of beetles( 4 possibile cells)
				int neigh[4][3];//1st column - what, 2nd - x, 3rd - y
				int x2,y2;			
				Grid_Past.GetNeigborCellCoords(x,y,&x2,&y2,beetle->Direction);//get coords of beetle2
				int free_n=0; //number of free cell from the 4 of the neighborhood 

				Grid_Past.GetNeigborCellCoords(x,y,&(neigh[0][1]),&(neigh[0][2]),RotateDirection(beetle->Direction,'L'));
				Grid_Past.GetNeigborCellCoords(x,y,&(neigh[1][1]),&(neigh[1][2]),RotateDirection(beetle->Direction,'R'));
				Grid_Past.GetNeigborCellCoords(x2,y2,&(neigh[2][1]),&(neigh[2][2]),RotateDirection(beetle->Direction,'L'));
				Grid_Past.GetNeigborCellCoords(x2,y2,&(neigh[3][1]),&(neigh[3][2]),RotateDirection(beetle->Direction,'R'));

				//get content of neighbor cells in following step and count the number of free ones
				int I,J;
				for (I=0;I<4;I++)
				{
					neigh[I][0]=Grid.GetCellContent(neigh[I][1],neigh[I][2]);				
					free_n++;
				}
				
				//if there is no free cell in neighborhood, new beetle cannot be born
				if (free_n== 0 )return false;
				
				//take random one from free neighbors
				int rand_n = RandInBound (free_n);
				rand_n++;
				for (J=0;J<4;J++)
					if ((neigh[J][0]==FLOWER) ||(neigh[J][0]==NOTHING)) 
					{
						rand_n--;
						if (rand_n==0)
							break;
					}
				//J is now the index of the chosen neighbor
						
				CBeetle * beetle_child=beetle->CreateChild(beetle2);
				beetle->NumChildren++;
				beetle2->NumChildren++;
				
				//beetles might die during the consumption
				beetle->ConsumeEnergy(beetle->InvInChild);
				beetle2->ConsumeEnergy(beetle2->InvInChild);
				assert(beetle->Energy >0);
				assert(beetle2->Energy >0);

				if (Grid.SetCellContent(BEETLE,neigh[J][1],neigh[J][2],beetle_child))
					return true;
				else return false;
		
		}
	}

	return false;
}

char CEnvironment::RotateDirection(char direction, char L_R_F)
{
	//there are 4 directions: W=0,N=1,E=2,S=3, so the "right" adds 1 and "left" subtracts 1
	if (L_R_F== 'L') { direction-=1; if (direction<0) direction=3; }
	if (L_R_F== 'R') { direction+=1;direction%=4;}
	//if (L_R_F== 'F') ;
	return direction;
}

void CEnvironment::CountStatistics(void)
{
	int I,J,what;
	Statist.MakeEmpty();
	CBeetle * beetle=NULL;
	for(I=0;I<Grid.G_Width;I++)
			for(J=0;J<Grid.G_Height;J++)
			{
				what=Grid.GetCellContent(I,J,&beetle);
				if (what==BEETLE)
				{
					Statist.NumBeetles++;
					if (beetle->Age ==0 )Statist.NumBirths++;
					Statist.SumAge+=beetle->Age;
					Statist.SumEnergy+=beetle->Energy;
					Statist.SumHungryThreshold+=beetle->HungryThreshold;
					Statist.SumInvInChild+=beetle->InvInChild;
					Statist.SumLearnAbility+=beetle->LearnAbility;
					Statist.SumNumChildren+=beetle->NumChildren;
				}
				if (what==FLOWER) 
					Statist.NumFlowers++;
				
			}

}
