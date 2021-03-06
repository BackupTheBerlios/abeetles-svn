#include "StdAfx.h"
#include "Beetle.h"
#include "defines.h"
#include <assert.h>
#include  <QImage>
#include <QString>

int CBeetle::EnergyMax_C = MAX_ENERGY; //static variable must be inicialized like this out of the class!
int CBeetle::LastId=0;
int CBeetle::EFF_Age [EFF_BMP_X]={10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}; 
QImage CBeetle::EffImg;
int CBeetle::MutationProb=MUTATION_PROB_DEFAULT;
extern int RandInBound(int);
int CBeetle::AlocBeetles=0;

CBeetle::CBeetle(void)
{	
	Species=NO_SPECIES;
}
CBeetle::CBeetle(int id, int age,char brain[BRAIN_D1][BRAIN_D2][BRAIN_D3][BRAIN_D4],int direction,int energy,int expectOnPartner[EXPECT_ON_PARTNER_D], int hungryThreshold, int invInChild, int learnAbility, int numChildren=0)
{	
	int I,J,K,L;
	Species=NO_SPECIES;

	Age=age;
	for (I=0;I<2;I++)for (J=0;J<4;J++)for (K=0;K<4;K++)for (L=0;L<4;L++)
		Brain[I][J][K][L]=brain[I][J][K][L];
	if ((direction>=0) &&(direction<=3))Direction=direction;
		else Direction=0;
	if ((energy>0)&&(energy<=MAX_ENERGY)) Energy=energy; 
		else Energy=MAX_ENERGY;
	for (I=0;I<EXPECT_ON_PARTNER_D;I++)
		ExpectOnPartner[I]=expectOnPartner[I];
	if ((hungryThreshold>0)&&(hungryThreshold<=EnergyMax_C))HungryThreshold = hungryThreshold;
		else HungryThreshold=EnergyMax_C;
	InvInChild=invInChild;
	LearnAbility = learnAbility;
	NumChildren=numChildren;
	Id=id;

	assert(Energy>0);
	
}

CBeetle::~CBeetle(void)
{
}

//returns amount really added to the beetle
int CBeetle::AddEnergy(int HowMuch) 
{
	if (Energy+HowMuch<=EnergyMax_C)
	{
		Energy+=HowMuch;
		return HowMuch;
	}
	else
	{
		Energy=EnergyMax_C;
		return EnergyMax_C-Energy;
	}
}
/*
//Left,Right, Front: 0-nic, 1-stena, 2-kytka, 3-brouk
int CBeetle::GetAction(bool bHunger, char Left, char Front, char Right)
{	
	return (int)Brain[bHunger][Left][Front][Right];
}
*/


bool CBeetle::IsHungry(void)
{
	if (Energy>=HungryThreshold)return false;
	else return true;
}

int CBeetle::GetEnergy(void)
{
	return Energy;
}

char CBeetle::GetDirection(void)
{
	return Direction;
}

int CBeetle::Decide(int Left, int Front, int Right)
{
	//Left, Front, Right: NOTHING=1/WALL/FLOWER/BEETLE=4
	if (Front==WALL) return A_ROTATERIGHT;
	return Brain [IsHungry()][Left-1][Front-1][Right-1];
}

char CBeetle::GetBrainItemShortcut(int H,int L,int F, int R)
{
	if (Brain[H][L][F][R] == A_STEP) return 'S';
	if (Brain[H][L][F][R] == A_ROTATERIGHT) return 'L';
	if (Brain[H][L][F][R] == A_ROTATELEFT) return 'R';
	
	

	//QErrorMessage errDlg;
	//errDlg.showMessage(QString::fromAscii("Invalid cell of Brain:")+QString::number(H)+QString::number(L)+QString::number(F)+QString::number(R));
	return '?';
}
int CBeetle::EnergyFromFlower(void)
{
	if (Age<EFF_BMP_X) return EFF_Age[Age];
	else return EFF_Age[EFF_BMP_X-1];

		//(int)((((double)1/(Age+1)) * 10)+1);
}

int CBeetle::ConsumeEnergy(int HowMuch)
{
	Energy-=HowMuch;
	if (IsDead())return DEAD;
	else if (IsHungry()) return HUNGRY;
	else return NOT_HUNGRY;
}

bool CBeetle::IsDead(void)
{
	if (Energy<=0) return true;
	else return false;
}

void CBeetle::Die(void)
{
	//actions connected with beetles death.
}

void CBeetle::SetBrain(int Num, int Value)
{
	int I1=0,I2=0,I3=0,I4=0;
	I4=Num%4;Num=Num/4;
	I3=Num%4;Num=Num/4;
	I2=Num%4;Num=Num/4;
	I1=Num%2;
	
	Brain[I1][I2][I3][I4]=Value;
}

int CBeetle::GetExpectOnPartnerMax(int which)
{	
	//	ExpectOnPartner - Age [2] = 2B how much older / younger can be the partner
	//	ExpectOnPartner - Energy = 1B how much more must at least have than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much at least
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 

	switch (which)
	{
		case 0: return 100;
		case 1: return 100;
		case 2: return MAX_ENERGY - MAX_INV_IN_CHILD;
		case 3: return MAX_INV_IN_CHILD;
		case 4: return 100;
		case 5: return 100;
		default:
			printf ("Wrong input for CBeetle::GetExpectOnPartnerMax(beetle)\n");
			return 0;
	}
}

bool CBeetle::IsExpectOnPartnerSatisfied(CBeetle * beetle2)
{
	//	ExpectOnPartner - Age [2] = 2B how much younger / older  can be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much should have at least
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 

	if (beetle2->Age < Age - ExpectOnPartner[1]) return false;
	if (beetle2->Age > Age + ExpectOnPartner[0]) return false;
	if (beetle2->Energy < ExpectOnPartner[3]+ExpectOnPartner[2])return false; 
	if (beetle2->InvInChild< ExpectOnPartner[3])return false; 
	if (beetle2->LearnAbility < LearnAbility - ExpectOnPartner[4]) return false;
	if (beetle2->LearnAbility > LearnAbility + ExpectOnPartner[5]) return false;
	if (beetle2->Energy <=beetle2->InvInChild) return false; //beetle2 would not survive creation of the child
	//if the beetle who checks the other beetle is not hungry -- I am not sure whether this check should not be somewhere else
	if (IsHungry() == true) return false;
	return true;
	
}

bool CBeetle::IsExpectOnPartnerPossibleToSatisfy(CBeetle * beetle2)
{
	//	ExpectOnPartner - Age [2] = 2B how much younger / older  can be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much should have at least
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 
	
//Only features that are part of genome are included.

//	if (beetle2->Age < Age - ExpectOnPartner[1]) return false;
//	if (beetle2->Age > Age + ExpectOnPartner[0]) return false;
//	if (beetle2->Energy < ExpectOnPartner[3]+ExpectOnPartner[2])return false; 
	if (beetle2->InvInChild< ExpectOnPartner[3])return false; 
	if (beetle2->LearnAbility < LearnAbility - ExpectOnPartner[4]) return false;
	if (beetle2->LearnAbility > LearnAbility + ExpectOnPartner[5]) return false;
//	if (beetle2->Energy <=beetle2->InvInChild) return false; //beetle2 would not survive creation of the child
	//if the beetle who checks the other beetle is not hungry -- I am not sure whether this check should not be somewhere else
//	if (IsHungry() == true) return false;
	return true;
	
}

CBeetle * CBeetle::CreateChild(CBeetle * beetle2)
{
	CBeetle * beetle_child = Crossover1Point(this, beetle2);
	Mutation(beetle_child);
	
	return beetle_child;
}

CBeetle * CBeetle::Crossover1Point(CBeetle * beetle1, CBeetle * beetle2)
{
	CBeetle * beetle_child1=new CBeetle();CBeetle::AlocBeetles++;
	//fprintf(stdout,("Beetle "+QString::number(beetle1->Id)+" + Beetle "+QString::number(beetle2->Id)+"alloc 2 babies").toAscii().data());
	CBeetle * beetle_child2=new CBeetle();CBeetle::AlocBeetles++;
	CBeetle * pom_ref_beetle;
	
	
	int N,J,pom,rand;

	//indexes of 
	int  I [4];
	int  indxInI [4]={0,1,2,3};
	
	for (N=3;N>=0;N--)
	{
		pom=indxInI[N];
		indxInI[N] = indxInI[rand=RandInBound(N+1)];
		indxInI[rand]=pom;
	}

	int PossibleCrossPoints = CBeetle::GetBrainDimension(indxInI[0]) +//size of first dimension of Brain
							  EXPECT_ON_PARTNER_D + //size of ExpectOnPartner array
							  1;	// There are 3 variables left - we start CP_count from 0, thus 2 more CP and after the last variable is no CP, thus 1.
	int CrossPoint = RandInBound(PossibleCrossPoints+1);
	int CP_count=0;
	bool isCrossed=false;
	
	//Brain
	for (I[indxInI[0]]=0;I[indxInI[0]]<CBeetle::GetBrainDimension(indxInI[0]);I[indxInI[0]]++)
	{
		for(I[indxInI[1]]=0;I[indxInI[1]]<CBeetle::GetBrainDimension(indxInI[1]);I[indxInI[1]]++)
			for(I[indxInI[2]]=0;I[indxInI[2]]<CBeetle::GetBrainDimension(indxInI[2]);I[indxInI[2]]++)
				for(I[indxInI[3]]=0;I[indxInI[3]]<CBeetle::GetBrainDimension(indxInI[3]);I[indxInI[3]]++)
				{
					beetle_child1->Brain[I[0]][I[1]][I[2]][I[3]] = beetle1->Brain[I[0]][I[1]][I[2]][I[3]];
					beetle_child2->Brain[I[0]][I[1]][I[2]][I[3]] = beetle2->Brain[I[0]][I[1]][I[2]][I[3]];
				}

		
		if (!isCrossed &&(CP_count==CrossPoint)) 
		{
			isCrossed=true;
			// switch of references of child 1 and 2
			pom_ref_beetle = beetle_child1;beetle_child1=beetle_child2;beetle_child2=pom_ref_beetle;
		}
		CP_count++;
	}
	//ExpectOnPartner
	for (J=0;J<EXPECT_ON_PARTNER_D;J++)
	{
		beetle_child1->ExpectOnPartner[J] = beetle1->ExpectOnPartner[J];
		beetle_child2->ExpectOnPartner[J] = beetle2->ExpectOnPartner[J];

		
		if (!isCrossed &&(CP_count==CrossPoint)) 
		{
			isCrossed=true;
			// switch of references of child 1 and 2
			pom_ref_beetle = beetle_child1;beetle_child1=beetle_child2;beetle_child2=pom_ref_beetle;
		}
		CP_count++;
	}

	//Hungry Threshold
	beetle_child1->HungryThreshold = beetle1->HungryThreshold;
	beetle_child2->HungryThreshold = beetle2->HungryThreshold;
	
	if (!isCrossed &&(CP_count==CrossPoint)) 
	{
		isCrossed=true;
		// switch of references of child 1 and 2
		pom_ref_beetle = beetle_child1;beetle_child1=beetle_child2;beetle_child2=pom_ref_beetle;
	}
	CP_count++;

	//InvInChild
	beetle_child1->InvInChild = beetle1->InvInChild;
	beetle_child2->InvInChild = beetle2->InvInChild;
	
	if (!isCrossed &&(CP_count==CrossPoint)) 
	{
		isCrossed=true;
		// switch of references of child 1 and 2
		pom_ref_beetle = beetle_child1;beetle_child1=beetle_child2;beetle_child2=pom_ref_beetle;
	}
	CP_count++;

	//LearnAbility
	beetle_child1->LearnAbility = beetle1->LearnAbility;
	beetle_child2->LearnAbility = beetle2->LearnAbility;

	assert (isCrossed==true);
	
	//choice of one of two beetle_childs, produced by crossover}
	CBeetle * beetle_child=NULL;
	if (RandInBound(2)==0) {beetle_child=beetle_child1;delete(beetle_child2); AlocBeetles--; beetle_child2=NULL;}//fprintf(stdout,"One child deleted.");}
	else {beetle_child=beetle_child2;delete(beetle_child1);AlocBeetles--; beetle_child1=NULL; }//	fprintf(stdout,"One child deleted.");};

	beetle_child->Age=0;
	beetle_child->Energy= beetle1->InvInChild + beetle2->InvInChild;	
	if (beetle_child->Energy > MAX_ENERGY)beetle_child->Energy= MAX_ENERGY;
	//assert (beetle_child->Energy>0); 
	beetle_child->Direction = RandInBound(4);
	beetle_child->NumChildren=0;
	beetle_child->Id=CBeetle::CreateNewId();
	return beetle_child;
}

/**
* Static method: GetBrainDimension
* Desc: Returns certain dimension range of the Brain attribute
* System dependence: no
* Usage comments:
* @return (Return values - meaning) : no return value
* @param name [ descrip](Parameters - meaning): which - zero based index of the dimension, in which the range will be returned
* @throws name [descrip](Exceptions - meaning)
*/
int CBeetle::GetBrainDimension(int which)
{
	switch (which)
	{
		case 0: return BRAIN_D1;
		case 1: return BRAIN_D2;
		case 2: return BRAIN_D3;
		case 3: return BRAIN_D4;
		default: return 0;
	}
}


/**
* Static method: Mutation
* Desc: Mutates Genom a beetle with probability MutationProb
* System dependence: no
* Usage comments:
* @return (Return values - meaning) : no return value
* @param name [ descrip](Parameters - meaning):beetle - reference to the beetle, whose genome is to be mutated
* @throws name [descrip](Exceptions - meaning)
*/
void CBeetle::Mutation(CBeetle * beetle)
{
	int M,N,K,L;		
	bool isChange = false;
				for (M=0;M<BRAIN_D1;M++)
					for(N=0;N<BRAIN_D2;N++)
						for(K=0;K<BRAIN_D3;K++)
							for(L=0;L<BRAIN_D4;L++)
								if (RandInBound(100)<MutationProb)
									{beetle->Brain [M][N][K][L]= RandInBound(NUM_ACTIONS); isChange=true;}
				for (M=1;M<EXPECT_ON_PARTNER_D;M++)
					if (RandInBound(100)<MutationProb){beetle->ExpectOnPartner[M]= RandInBound(GetExpectOnPartnerMax(M));isChange=true;}
				if (RandInBound(100)<MutationProb){beetle->HungryThreshold= 1+RandInBound(MAX_ENERGY);isChange=true;}
				if (RandInBound(100)<MutationProb){beetle->InvInChild= 1+ RandInBound(MAX_INV_IN_CHILD);isChange=true;}
				if (RandInBound(100)<MutationProb){beetle->LearnAbility= 1+RandInBound(MAX_LEARN_ABILITY);	isChange=true;}
}

void CBeetle::LearnFrom(CBeetle* beetle2)
{
	int M,N,K,L;		
		bool isChange = false;
					for (M=0;M<BRAIN_D1;M++)
						for(N=0;N<BRAIN_D2;N++)
							for(K=0;K<BRAIN_D3;K++)
								for(L=0;L<BRAIN_D4;L++)
									if (RandInBound(100)<LEARN_PROB)
										{Brain [M][N][K][L]= beetle2->Brain [M][N][K][L]; isChange=true;}

					for (M=1;M<EXPECT_ON_PARTNER_D;M++)
						if (RandInBound(100)<LEARN_PROB){ExpectOnPartner[M]= beetle2->ExpectOnPartner[M];isChange=true;}
					if (RandInBound(100)<LEARN_PROB){HungryThreshold= beetle2->HungryThreshold;isChange=true;}
					if (RandInBound(100)<LEARN_PROB){InvInChild= beetle2->InvInChild;isChange=true;}
					if (RandInBound(100)<LEARN_PROB){LearnAbility= beetle2->LearnAbility;	isChange=true;}
	
}

int CBeetle::CreateNewId(void)
{
	if (LastId<MAX_INT)	return ++LastId;
	else return LastId=1;
}

QString CBeetle::GetWordDirection(char direction)
{
	if (direction==WEST) return QString("west");
	if (direction==NORTH) return QString("north");
	if (direction==EAST) return QString("east");
	if (direction==SOUTH) return QString("south");
	
	return "";
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


CBeetle * CBeetle::CreateRandomBeetle(bool isStepOnFlower, bool isNoExpectations)
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
					if (isStepOnFlower) //if rule "Step On flower should be set for every beetle
					{
						if ((I==1)&&(K==(FLOWER-1))) brain[I][J][K][L]=A_STEP;
						else
							if (K==(WALL-1)) brain [I][J][K][L]=1 + RandInBound(NUM_ACTIONS-1); //with wall in the front, never makes a step
							else brain [I][J][K][L]=RandInBound(NUM_ACTIONS);
					}
					else //if brain of beetle should be totaly random
					{
						if (K==(WALL-1)) brain [I][J][K][L]=1 + RandInBound(NUM_ACTIONS-1); //with wall in the front, never makes a step
						else brain [I][J][K][L]=RandInBound(NUM_ACTIONS);
					}
				}
	char direction = RandInBound(4);
	int energy=20+RandInBound(MAX_ENERGY-20);
	
	
	//	ExpectOnPartner - Age [2] = 2B how much younger/older  can be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much at least
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 

	//for (M=0;M<EXPECT_ON_PARTNER_D;M++)
	//maximal ranges of expectations
	if (isNoExpectations==true)
	{
		expectOnPartner [0]= CBeetle::GetExpectOnPartnerMax(0); 
		expectOnPartner [1]= CBeetle::GetExpectOnPartnerMax(1); 
		expectOnPartner [2]= 1; 
		expectOnPartner [3]= 1; 
		expectOnPartner [4]=MAX_ENERGY;
		expectOnPartner [5]=MAX_ENERGY;
	}
	else
	//random ranges of expectations
	{
		expectOnPartner [0]= 20+RandInBound(MAX_ENERGY-20); 
		expectOnPartner [1]= 20+RandInBound(MAX_ENERGY-20); 
		expectOnPartner [2]= 1+RandInBound(MAX_ENERGY / 4); 
		expectOnPartner [3]= 1+RandInBound(MAX_ENERGY / 4); 
		expectOnPartner [4]= 20+RandInBound(MAX_ENERGY-20); 
		expectOnPartner [5]= 20+RandInBound(MAX_ENERGY-20); 
	}

	
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
	CBeetle::AlocBeetles++;
	/* Removed to CountStatistics()
	Statist.SumHungryThreshold+=hungryThreshold;
	Statist.SumInvInChild+=invInChild;
	Statist.SumLearnAbility+=learnAbility;*/


	return beetle;
}

