#pragma once
#include "defines.h"
#include "Grid.h"

/**
* Desc: Class CStatisticsEnv serves to monitor features of the environment and its inhabitants, collect them into data structures and output them on demand.
* System dependence: no
* Usage comments:
* Relations to other classes: its methods are called from Env class. Env uses object of CStatisticsEnv as its attribute.
* Remarks: Statistics in Abeetles:
* Statistics in Abeetles can be structured in several groups.
* 1. Aggregated statistics, counted in one moment on demand: SumAge, SumEnergy, SumHungryThreshold, ... <br>
*	There is no need to keep trace of this values continuoustly. There are count by function Env::CountStatistics()
* 2. Actual statistics, that are displayed at every step should be count continuosly. 
* 3. Past statistics, that are logged into file every MAX_BUF time slices: PastNumBeetles[], PastNumBirths,..
*	The value of statistics of type 2 are add to them at every end of a time slice.
*	Problem: When time > 
*
*/
class CStatisticsEnv
{
public:
	CStatisticsEnv(void);
	~CStatisticsEnv(void);
	public:
	// Values valid at 1 time slice:
	//Type 1:
	int NumBeetles; //added at every birth / death
	int NumBirths; //added at every birth in one time slice
	int NumFlowers; //added at every growth/eaten up/deletion by beetle at the same time slice

	//Type 2:
	int SumAge;
	int SumEnergy;
	int SumHungryThreshold;
	int SumInvInChild;
	int SumLearnAbility;
	int SumNumChildren;

	//Type 3: Time Statistics
	int PastNumBeetles [BUF_SIZE];
	int PastNumBirths [BUF_SIZE];
	int PastNumFlowers [BUF_SIZE];
	
	//non-statistic helpers
	int startBuf; // startBuf is First valid index in TimeStatistics arrays. (From startBuf+1) can be the buffer written to the .csv file. (+1), because the startBuf is already the last writen value in the .csv.Meaning: If the Env was loaded and arrays of TimeStatistic don't begin from one.

	void NextTime(int Time);
	
	void MakeEmpty(void);
	double GetAvgAge(void);
	double GetAvgEnergy(void);
	double GetAvgHungryThreshold(void);
	double GetAvgInvInChild(void);
	double GetAvgLearnAbility(void);
	double GetAvgNumChildren(void);

	bool SaveActAgrStatist(char * filename, int time);
	bool SaveTimeStatist_InRowsAppend();
	bool SaveTimeStatist_InColumnsAppend(int upto = BUF_SIZE, char * fname =0);
	bool LoadTimeStatist_FromColums(char * tst_filename,int * pTime);

	bool SaveActHistStatist(char * filename, int time,CGrid * grid);
};
