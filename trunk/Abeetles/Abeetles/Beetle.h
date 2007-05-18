#pragma once
#include "defines.h"

class CBeetle
{
public:
	CBeetle(void);
	CBeetle(int age,char brain[2][4][4][4],int direction,int energy,int expectOnPartner [EXPECT_ON_PARTNER_D1][EXPECT_ON_PARTNER_D2], int hungryThreshold, int invInChild, int learnAbility );
	~CBeetle(void);
	static int EnergyMax_C;
//protected:
	int Energy;// 0-100
	char Direction; //0,1,2,3 = West, North, East, South
	int Age; 
	int HungryThreshold;
	char Brain[2][4][4][4];//Decision table - if hunger, what is on left, in front, on right
													//Values: 0-nothing, 1-wall, 2-flower, 3-beetle
public:
	int AddEnergy(int HowMuch);
	int GetAction(bool bHunger, char Left, char Front, char Right);
	void A_RotateLeft(void);
	void A_RotateRight(void);
	bool IsHungry(void);	
	int GetEnergy(void);
	char GetDirection(void);
	int EnergyFromFlower(void);
	int Decide(int Left, int Front, int Right);
	int ConsumeEnergy(int HowMuch);
	bool IsDead(void);
	void Die(void);
	int LearnAbility;
	int InvInChild;
	int ExpectOnPartner[4][2]; //0.Energy, 1.Age, 2.InvInChild, 3.LearningAbility
	void SetBrain(int Num, int Value);
	static int GetExpectOnPartnerMax(int which);
	bool IsExpectOnPartnerSatisfied(int expect, int valueOfPartner);
	CBeetle * CreateChild(CBeetle * beetle2);
	static CBeetle * Crossover1Point(Cbeetle * beetle1, Cbeetle * beetle2);
};
