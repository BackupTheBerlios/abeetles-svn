#include "StdAfx.h"
#include "StatisticsEnv.h"

CStatisticsEnv::CStatisticsEnv(void)
{
	MakeEmpty();

}

CStatisticsEnv::~CStatisticsEnv(void)
{
}

void CStatisticsEnv::NextTime(int Time)
{
	NumBirths=0;
	SumAge=0;
	SumEnergy=0;
	SumNumChildren=0;

}

void CStatisticsEnv::MakeEmpty(void)
{
	SumAge=0;
	SumEnergy=0;
	SumHungryThreshold =0;
	SumInvInChild=0;
	SumLearnAbility=0;
	SumNumChildren=0;
	NumBeetles=0;
	NumBirths=0;
	NumFlowers=0;
}

double CStatisticsEnv::GetAvgAge(void)
{
	return (double)SumAge/NumBeetles;
}

double CStatisticsEnv::GetAvgEnergy(void)
{
	return (double)SumEnergy/NumBeetles;
}

double CStatisticsEnv::GetAvgHungryThreshold(void)
{
	return (double)SumHungryThreshold/NumBeetles;
}

double CStatisticsEnv::GetAvgInvInChild(void)
{
	return (double)SumInvInChild/NumBeetles;
}

double CStatisticsEnv::GetAvgLearnAbility(void)
{
	return (double)SumLearnAbility/NumBeetles;
}

double CStatisticsEnv::GetAvgNumChildren(void)
{
	return (double)SumNumChildren/NumBeetles;
}