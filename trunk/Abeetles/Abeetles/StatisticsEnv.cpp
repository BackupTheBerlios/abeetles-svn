#include "StdAfx.h"
#include "StatisticsEnv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




CStatisticsEnv::CStatisticsEnv(void)
{
	MakeEmpty();

	FILE * statTimeFile;
		errno_t err; 

		if ((err= fopen_s(&statTimeFile,STAT_TIME_FILE,"w"))!=0) 
		{
			printf("Creation of file for time statistics was not successful - Error No.%d.\n",err);
			return; //It is not a reason to finnish the program.
			//exit (EXIT_FAILURE);
		}
		else 
		{	//adding to rows
			/*
			fprintf(statTimeFile,"Number of beetles;\n");
			fprintf(statTimeFile,"Number of births;\n");
			fprintf(statTimeFile,"Number of flowers;\n");
			fprintf(statTimeFile,"Density of population;\n");*/
			//adding to columns
			fprintf(statTimeFile,"Number of beetles;Number of births;Number of flowers\n");
		}
	fclose(statTimeFile);

}

CStatisticsEnv::~CStatisticsEnv(void)
{
}

void CStatisticsEnv::NextTime(int Time)
{	
	PastNumBeetles[Time%BUF_SIZE]=NumBeetles;
	PastNumBirths[Time%BUF_SIZE]=NumBirths;
	PastNumFlowers[Time%BUF_SIZE]=NumFlowers;

	//After 1000 time slices add all time values into file.
	if (Time% BUF_SIZE == (BUF_SIZE-1))
	{
		//SaveTimeStatist_InRowsAppend();
		SaveTimeStatist_InColumnsAppend();
	}
	
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

/**
* Public method <br>
* Description: Saves {@link Abeetles.CStatisticsEnv} actual and agregated statistics<br>
* System dependence: no<br>
* Usage comments:<br>
* @return true - if successful, false - otherwise
* @param filename [name for file, where the statistics will be saved]
* @param time [Actual time to be writte](Parameters - meaning):
* @throws name [descrip](Exceptions - meaning)
* @see Abeetles.CStatisticsEnv #SaveTimeStatist_InColumnsAppend
* @see Abeetles.CStatisticsEnv #SaveTimeStatist_InRowsAppend
*/

bool CStatisticsEnv::SaveActAgrStatist(char * filename, int time)
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

bool CStatisticsEnv::SaveTimeStatist_InRowsAppend()
{
		FILE * stTFOld;FILE * stTF;
		errno_t err;
		char chr=0;
		
		//rename file to some other name
		rename(STAT_TIME_FILE,STAT_TIME_FILE_OLD);
		//open old file for reading and new file for writing
		if ((err= fopen_s(&stTFOld,STAT_TIME_FILE_OLD,"r"))!=0) 
		{
			printf("Error No.%d occured, opening of file %s unsuccessful.",err,STAT_TIME_FILE);			
			return false;
		}
		if ((err= fopen_s(&stTF,STAT_TIME_FILE,"w"))!=0) 
		{
			printf("Error No.%d occured, opening of file %s unsuccessful.",err,STAT_TIME_FILE);			
			return false;
		}
		//rewrite old to new up to the end of the first line
		chr=getc(stTFOld);
		while(chr!='\n')
		{
			putc(chr,stTF);chr=getc(stTFOld);
		}
			
		int I;
		for (I=0;I<BUF_SIZE;I++)
			fprintf(stTF,"%d;",PastNumBeetles[I]);
		fprintf(stTF,"\n");

		chr=getc(stTFOld);
		while(chr!='\n')
		{
			putc(chr,stTF);chr=getc(stTFOld);
		}
					        
        for (I=0;I<BUF_SIZE;I++)
            fprintf(stTF,"%d;",PastNumBirths[I]);
        fprintf(stTF,"\n");

		chr=getc(stTFOld);
		while(chr!='\n')
		{
			putc(chr,stTF);chr=getc(stTFOld);
		}
					
		for (I=0;I<BUF_SIZE;I++)
			fprintf(stTF,"%d;",PastNumFlowers[I]);
		fprintf(stTF,"\n");

		fclose(stTF);fclose(stTFOld);
		remove (STAT_TIME_FILE_OLD);
	return true;
}


/**
* Public method <br>
* Description: Writes last n value to a .csv file. The n is defined by constant BUF_SIZE. The name of the file is STAT_TIME_FILE. It adds every monitored variable into separate column. <br>
* System dependence: no<br>
* Usage comments:<br>
* @return True - if saving was successful and false, if opening of the file failed.
*/
bool CStatisticsEnv::SaveTimeStatist_InColumnsAppend()
{
	FILE *  stTF;
	errno_t err;	
	int I;

	if ((err= fopen_s(&stTF,STAT_TIME_FILE,"a+"))!=0) 
	{
		printf("Error No.%d occured: %s, opening of file %s unsuccessful.",err,strerror(err),STAT_TIME_FILE);			
		return false;
	}
	
	for (I=0;I<BUF_SIZE;I++)
        fprintf(stTF,"%d;%d;%d\n",PastNumBeetles[I],PastNumBirths[I],PastNumFlowers[I]);

	fclose(stTF);
	return true;
}
