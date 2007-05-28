#pragma once
#include "defines.h"

class CStatisticsEnv
{
public:
	CStatisticsEnv(void);
	~CStatisticsEnv(void);
	public:
	int NumBeetles;
	int NumBirths;
	int NumFlowers;

	double SumAge;
	double SumEnergy;
	double SumHungryThreshold;
	double SumInvInChild;
	double SumLearnAbility;
	double SumNumChildren;

	int PastNumBeetles [BUF_SIZE];
	int PastNumBirths [BUF_SIZE];
	int PastNumFlowers [BUF_SIZE];

	void NextTime(int Time);
	
	void MakeEmpty(void);
	double GetAvgAge(void);
	double GetAvgEnergy(void);
	double GetAvgHungryThreshold(void);
	double GetAvgInvInChild(void);
	double GetAvgLearnAbility(void);
	double GetAvgNumChildren(void);

	bool CStatisticsEnv::SaveStatist(char * filename, int time);
};
