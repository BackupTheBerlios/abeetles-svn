#include "StdAfx.h"
#include "StatisticsEnv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grid.h"
#include "assert.h"




CStatisticsEnv::CStatisticsEnv(void)
{
	MakeEmpty();

	FILE * statTimeFile;
		int err; 

		if ((statTimeFile= fopen(STAT_TIME_FILE,"w"))==0) 
		{
			printf("Creation of file for time statistics was not successful - Error No.%d.\n",errno);
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
	int err;

	if ((statFile= fopen(filename,"w"))==0) 
	{
		printf("%d",errno);
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
		int err;
		char chr=0;
		
		//rename file to some other name
		rename(STAT_TIME_FILE,STAT_TIME_FILE_OLD);
		//open old file for reading and new file for writing
		if ((stTFOld= fopen(STAT_TIME_FILE_OLD,"r"))==0) 
		{
			printf("Error No.%d occured, opening of file %s unsuccessful.",errno,STAT_TIME_FILE);			
			return false;
		}
		if ((stTF= fopen(STAT_TIME_FILE,"w"))==0) 
		{
			printf("Error No.%d occured, opening of file %s unsuccessful.",errno,STAT_TIME_FILE);			
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
	int err;	
	int I;

	if ((stTF= fopen(STAT_TIME_FILE,"a+"))==0) 
	{
		printf("Error No.%d occured: %s, opening of file %s unsuccessful.",errno,strerror(errno),STAT_TIME_FILE);			
		return false;
	}
	
	for (I=0;I<BUF_SIZE;I++)
        fprintf(stTF,"%d;%d;%d\n",PastNumBeetles[I],PastNumBirths[I],PastNumFlowers[I]);

	fclose(stTF);
	return true;
}

bool CStatisticsEnv::SaveActHistStatist(char * filename, int time,CGrid * grid)
{
	
	FILE *  statFile;
	int err;
	int I,J;
	
	int Ages [MAX_HIST];
	for (I=0;I<MAX_HIST;I++) Ages[I]=0;
	int LearnAbilities[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) LearnAbilities[I]=0;
	int InvInChilds[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) InvInChilds[I]=0;
	int	Energies[MAX_HIST];
	for (I=0;I<MAX_HIST;I++) Energies[I]=0;

	CBeetle * beetle=NULL;


	for(I=0;I<grid->G_Width;I++)
	for(J=0;J<grid->G_Height;J++)
	{
		if (grid->GetCellContent(I,J,&beetle)==BEETLE) 
		{
			if (beetle->Age <MAX_HIST)
				Ages[beetle->Age]++;

			assert(beetle->LearnAbility<MAX_HIST);
			LearnAbilities[beetle->LearnAbility]++;

			assert(beetle->InvInChild<MAX_HIST);
			InvInChilds[beetle->InvInChild]++;
			assert(beetle->Energy<MAX_HIST);			
			Energies[beetle->Energy]++;
		}

	}

	if ((statFile= fopen(filename,"w"))==0) 
	{
		printf("Error No.%d occured: %s, opening of file %s unsuccessful.",errno,strerror(errno),filename);			
		return false;
	}

	fprintf(statFile,"Ages;LearnAbilities;InvInChilds;Energies\n");
	for (I=0;I<MAX_HIST;I++)
	{
		fprintf(statFile,"%d;%d;%d;%d\n",Ages[I],LearnAbilities[I],InvInChilds[I],Energies[I]);
	}
	
	fclose(statFile);
	return true;
}
