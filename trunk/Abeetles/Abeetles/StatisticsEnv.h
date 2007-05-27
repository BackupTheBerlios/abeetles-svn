#pragma once

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

	void NextTime(int Time);
	
	void MakeEmpty(void);
	double GetAvgAge(void);
	double GetAvgEnergy(void);
	double GetAvgHungryThreshold(void);
	double GetAvgInvInChild(void);
	double GetAvgLearnAbility(void);
	double GetAvgNumChildren(void);
};
