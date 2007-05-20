#include "StdAfx.h"
#include "Beetle.h"
#include "defines.h"
#include <assert.h>
int CBeetle::EnergyMax_C = MAX_ENERGY; //static variable must be inicialized like this out of the class!
int CBeetle::EFF_Age [EFF_BMP_X]={10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}; 
extern int RandInBound(int);

CBeetle::CBeetle(void)
{	
	
}
CBeetle::CBeetle(int age,char brain[2][4][4][4],int direction,int energy,int expectOnPartner[EXPECT_ON_PARTNER_D], int hungryThreshold, int invInChild, int learnAbility )
{	
	int I,J,K,L;
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
//Left,Right, Front: 0-nic, 1-stena, 2-kytka, 3-brouk
int CBeetle::GetAction(bool bHunger, char Left, char Front, char Right)
{	
	return Brain[bHunger][Left][Front][Right];
}



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
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much more than InvInChild
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 

	switch (which)
	{
		case 0: return 100;
		case 1: return 100;
		case 2: return 100;
		case 3: return 100;
		case 4: return 100;
		case 5: return 100;
		default:
			printf ("Wrong input for CBeetle::GetExpectOnPartnerMax(beetle)\n");
			return 0;
	}
}

bool CBeetle::IsExpectOnPartnerSatisfied(CBeetle * beetle2)
{
	//	ExpectOnPartner - Age [2] = 2B how much older / younger can be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much more than InvInChild
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 

	if (beetle2->Age < Age - ExpectOnPartner[0]) return false;
	if (beetle2->Age > Age + ExpectOnPartner[1]) return false;
	if (beetle2->Energy < ExpectOnPartner[3]+ExpectOnPartner[2])return false; 
	if (beetle2->InvInChild< ExpectOnPartner[3])return false; 
	if (beetle2->LearnAbility < LearnAbility - ExpectOnPartner[4]) return false;
	if (beetle2->LearnAbility > LearnAbility + ExpectOnPartner[5]) return false;
	if (beetle2->Energy <=beetle2->InvInChild) return false; //beetle2 would not survive creation of the child
	return true;
	
}

CBeetle * CBeetle::CreateChild(CBeetle * beetle2)
{
	CBeetle * beetle_child = Crossover1Point(this, beetle2);

	
	return beetle_child;
}

CBeetle * CBeetle::Crossover1Point(CBeetle * beetle1, CBeetle * beetle2)
{
	CBeetle * beetle_child1=new CBeetle();
	CBeetle * beetle_child2=new CBeetle();
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
	
	CBeetle * beetle_child=NULL;
	if (RandInBound(2)) beetle_child=beetle_child1;
	else beetle_child=beetle_child2;
	beetle_child->Age=0;
	beetle_child->Energy= beetle1->InvInChild + beetle2->InvInChild;	
	if (beetle_child->Energy > MAX_ENERGY)beetle_child->Energy= MAX_ENERGY;
	assert (beetle_child->Energy>0); 
	beetle_child->Direction = RandInBound(4);
	return beetle_child;
}

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
