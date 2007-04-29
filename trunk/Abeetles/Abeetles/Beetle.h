#pragma once

class CBeetle
{
public:
	CBeetle(void);
	CBeetle(int energy,char direction, int hungryThreshold, char brain[2][4][4][4]);
	~CBeetle(void);
	static int EnergyMax_C;
//protected:
	int Energy;// 0-100
	char Direction; //0,1,2,3 = West, North, East, South
	int Age; 
	int HungryThreshold;
	char Brain[2][4][4][4];//Decision table - if hunger, what is on left, in front, on right
													//Values: 0-nothing, 1-wall, 2-flower, 3-beetl
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
	int ExpectOnPartner[4][2];
	void SetBrain(int Num, int Value);
};
