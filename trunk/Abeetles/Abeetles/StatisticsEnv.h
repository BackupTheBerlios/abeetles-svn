#pragma once

class CStatisticsEnv
{
public:
	CStatisticsEnv(void);
	~CStatisticsEnv(void);

	int NumBeetles;
	int NumBirths;

	double AvgAge;
	double AvgEnergy;
	double AvgHungryThreshold;
	double AvgInvInChild;
	double AvgLearnAbility;

	void NextTime(int Time);
	int NumFlowers;
};
