#include "StdAfx.h"
#include "StatisticsEnv.h"

CStatisticsEnv::CStatisticsEnv(void)
{
	AvgAge=0;
	AvgEnergy=0;
	AvgHungryThreshold =0;
	AvgInvInChild=0;
	AvgLearnAbility=0;
	NumBeetles=0;
	NumBirths=0;
	NumFlowers=0;

}

CStatisticsEnv::~CStatisticsEnv(void)
{
}

void CStatisticsEnv::NextTime(int Time)
{
	NumBirths=0;
}
