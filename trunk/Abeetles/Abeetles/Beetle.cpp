#include "StdAfx.h"
#include "Beetle.h"
#include "defines.h"
int CBeetle::EnergyMax_C = 100; //static variable must be inicialized like this out of the class!

CBeetle::CBeetle(void)
: LearnAbility(0)
, InvInChild(0)
{	
	
}
CBeetle::CBeetle(int energy,char direction, int hungryThreshold, char brain[2][4][4][4])
{	
	int I,J,K,L;
	Age=0;
	for (I=0;I<2;I++)for (J=0;J<4;J++)for (K=0;K<4;K++)for (L=0;L<4;L++)
		Brain[I][J][K][L]=brain[I][J][K][L];
	if ((direction>=0) &&(direction<=3))Direction=direction;
		else Direction=0;
	if ((energy>0)&&(energy<=EnergyMax_C)) Energy=energy; 
		else energy=EnergyMax_C;
	//TODO add expect on partner
	if ((hungryThreshold>0)&&(hungryThreshold<=EnergyMax_C))HungryThreshold = hungryThreshold;
		else HungryThreshold=EnergyMax_C;
	InvInChild=EnergyMax_C/2;
	LearnAbility = 20;
	
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
