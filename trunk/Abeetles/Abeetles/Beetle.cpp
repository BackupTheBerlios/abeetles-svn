#include "StdAfx.h"
#include "Beetle.h"
#include "defines.h"
int CBeetle::EnergyMax_C = 100; //static variable must be inicialized like this out of the class!

CBeetle::CBeetle(void)
: LearnAbility(0)
, InvInChild(0)
{	
	
}
CBeetle::CBeetle(int age,char brain[2][4][4][4],int direction,int energy,int expectOnPartner[EXPECT_ON_PARTNER_D1][EXPECT_ON_PARTNER_D2] , int hungryThreshold, int invInChild, int learnAbility )
{	
	int I,J,K,L;
	Age=age;
	for (I=0;I<2;I++)for (J=0;J<4;J++)for (K=0;K<4;K++)for (L=0;L<4;L++)
		Brain[I][J][K][L]=brain[I][J][K][L];
	if ((direction>=0) &&(direction<=3))Direction=direction;
		else Direction=0;
	if ((energy>0)&&(energy<=EnergyMax_C)) Energy=energy; 
		else energy=EnergyMax_C;
	for (I=0;I<EXPECT_ON_PARTNER_D1;I++)for (J=0;J<EXPECT_ON_PARTNER_D2;J++)
		ExpectOnPartner[I][J]=expectOnPartner[I][J];
	if ((hungryThreshold>0)&&(hungryThreshold<=EnergyMax_C))HungryThreshold = hungryThreshold;
		else HungryThreshold=EnergyMax_C;
	InvInChild=invInChild;
	LearnAbility = learnAbility;
	
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

void CBeetle::A_RotateLeft(void)//0,1,2,3 = West, North, East, South
{
	if (Direction>0) Direction--;
	else Direction=3;
}

void CBeetle::A_RotateRight(void)
{
	if (Direction<3) Direction++;
	else Direction=0;
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
	return 10;
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
	switch (which)
	{
		case 0: return EXPECT_ON_PARTNER_MAX_1;
		case 1: return EXPECT_ON_PARTNER_MAX_2;
		case 2: return EXPECT_ON_PARTNER_MAX_3;
		case 3: return EXPECT_ON_PARTNER_MAX_4;
		default:
			printf ("Wrong input for CBeetle::GetExpectOnPartnerMax(int which)\n");
			return 0;
	}
}

bool CBeetle::IsExpectOnPartnerSatisfied(int expect, int valueOfPartner)
{
	//0.Energy, 1.Age, 2.InvInChild, 3.LearningAbility
	if ((valueOfPartner >= ExpectOnPartner[expect][0])&&
		(valueOfPartner <= ExpectOnPartner[expect][1]))
	return true;
	else return false;

}

CBeetle * CBeetle::CreateChild(CBeetle * beetle2)
{
	CBeetle * beetle_child=new CBeetle(*beetle2);
	beetle_child->Age=0;
	/*
	beetle_child->Brain;
	beetle_child->Direction;
	beetle_child->Energy;
	beetle_child ->ExpectOnPartner;*/
	return beetle_child;
}
