#pragma once
#include "defines.h"

class QImage;

class CBeetle
{
public:
	CBeetle(void);
	CBeetle(int id, int age,char brain[BRAIN_D1][BRAIN_D2][BRAIN_D3][BRAIN_D4],int direction,int energy,int expectOnPartner [EXPECT_ON_PARTNER_D], int hungryThreshold, int invInChild, int learnAbility, int numChildren );
	~CBeetle(void);
	static int EnergyMax_C;
	static int EFF_Age [EFF_BMP_X];
	static 	QImage * EffImg;

	int Id;
	int Energy;// 0-100
	char Direction; //0,1,2,3 = West, North, East, South
	int Age; 
	int HungryThreshold;
	char Brain[BRAIN_D1][BRAIN_D2][BRAIN_D3][BRAIN_D4];//Decision table - if hunger, what is on left, in front, on right
													//Indexes: 0-nothing, 1-wall, 2-flower, 3-beetle
													//Values: A_step, A_rotateleft,rotateright,wait, copulate
	
	int ExpectOnPartner[6]; 
	//	ExpectOnPartner - Age [2] = 2B how much older / younger can be the partner
	//	ExpectOnPartner - Energy = 1B how much more than ExpectOnPartner - InvInChild
	//	ExpectOnPartner - InvInChild = 1B how much more than InvInChild
	//	ExpectOnPartner - LearningAbility [2]= how much less/more can have the parter 
	
	int LearnAbility;
	int InvInChild;
	int NumChildren;
	static int LastId;

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
	
	static int CreateNewId(void);
};
