#pragma once
#include "defines.h"

class CBeetle
{
public:
	CBeetle(void);
	CBeetle(int age,char brain[2][4][4][4],int direction,int energy,int expectOnPartner [EXPECT_ON_PARTNER_D], int hungryThreshold, int invInChild, int learnAbility );
	~CBeetle(void);
	static int EnergyMax_C;
	static int EFF_Age [EFF_BMP_X];
//protected:
	int Energy;// 0-100
	char Direction; //0,1,2,3 = West, North, East, South
	int Age; 
	int HungryThreshold;
	char Brain[2][4][4][4];//Decision table - if hunger, what is on left, in front, on right
													//Indexes: 0-nothing, 1-wall, 2-flower, 3-beetle
													//Values: A_step, A_rotateleft,rotateright,wait, copulate
	
	int ExpectOnPartner[6]; 
	//	ExpectOnPartner - Age [2] = 2B how much older / younger can be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much more than InvInChild
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 
	
	int LearnAbility;
	int InvInChild;

	int AddEnergy(int HowMuch);
	int GetAction(bool bHunger, char Left, char Front, char Right);	
	bool IsHungry(void);	
	int GetEnergy(void);
	char GetDirection(void);
	int EnergyFromFlower(void);
	int Decide(int Left, int Front, int Right);
	int ConsumeEnergy(int HowMuch);
	bool IsDead(void);
	void Die(void);
	
	void SetBrain(int Num, int Value);
	static int GetExpectOnPartnerMax(int which);
	bool IsExpectOnPartnerSatisfied(CBeetle * beetle2);
	CBeetle * CreateChild(CBeetle * beetle2);
	static CBeetle * Crossover1Point(CBeetle * beetle1, CBeetle * beetle2);
	static void Mutation(CBeetle * beetle);
	static int GetBrainDimension(int which);
	void LearnFrom(CBeetle* beetle2);
};
