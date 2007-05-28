#include "StdAfx.h"
#include "StatisticsEnv.h"

CStatisticsEnv::CStatisticsEnv(void)
{
	MakeEmpty();

	FILE * stTimeFile;
		errno_t err;

		if ((err= fopen_s(&statTimeFile,"p_statist.cvs","w"))!=0) 
		{
			fprintf(statTimeFile,"Number of beetles;\n");
			fprintf(statTimeFile,"Number of births;\n");
			fprintf(statTimeFile,"Number of flowers;\n");
			fprintf(statTimeFile,"Density of population;\n");
		}
		else 
		{
			printf("Creation of file for time statistics unsuccessful.");
			exit(EXIT_FAILURE);
		}

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
	
	//After 1000 time slices write all time values into files.
	if (Time%1000==999)
	{
		FILE * stTimeFile;
		errno_t err;

		if ((err= fopen_s(&statTimeFile,"p_numbeetles.cvs","a"))!=0) 
		{
			for (I=0;I<1000;I++)
			printf("%d;",PastNumBeetles[I]);
			return false;
		}
		
	PastNumBeetles[Time % 1000]

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
bool CStatisticsEnv::SaveStatist(char * filename, int time)
{
	FILE * statFile;
	errno_t err;

	if ((err= fopen_s(&statFile,filename,"w"))!=0) 
	{
		printf("%d",err);
		return false;
	}
	
	fprintf(statFile," ---------- \n");
	fprintf(statFile,"Time=%d\n",time);
	fprintf(statFile,"NumBeetles=%d;\n",NumBeetles);
	fprintf(statFile,"NumBirths=%d;\n",NumBirths);
	fprintf(statFile,"NumFlowers=%d;\n",NumFlowers);
	fprintf(statFile,"SumAge=%d;\n",SumAge);
	fprintf(statFile,"SumEnergy=%d;\n",SumEnergy);
	fprintf(statFile,"SumHungryThreshold=%d;\n",SumHungryThreshold);
	fprintf(statFile,"SumInvInChild=%d;\n",SumInvInChild);
	fprintf(statFile,"SumLearnAbility=%d;\n",SumLearnAbility);
	fprintf(statFile,"SumNumChildren=%d;\n",SumNumChildren);

	fprintf(statFile,"AvgAge=%f;\n",GetAvgAge());
	fprintf(statFile,"AvgEnergy=%f;\n",GetAvgEnergy());
	fprintf(statFile,"AvgHungryThreshold=%f;\n",GetAvgHungryThreshold());
	fprintf(statFile,"AvgInvInChild=%f;\n",GetAvgInvInChild());
	fprintf(statFile,"AvgLearnAbility=%f;\n",GetAvgLearnAbility());
	fprintf(statFile,"AvgNumChildren=%f;\n",GetAvgNumChildren());

	fprintf(statFile," ---------- \n");
	
	fclose(statFile);

	return true;
}
