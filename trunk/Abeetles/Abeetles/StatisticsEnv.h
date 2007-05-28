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

	int PastNumBeetles [1000];
	int PastNumBirths [1000];
	int PastNumFlowers [1000];

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
