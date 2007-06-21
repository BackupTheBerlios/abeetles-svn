#pragma once
#include "Beetle.h"
#include "Grid.h"
#include "CfgManager.h"
#include "StatisticsEnv.h"

//make globals visible
extern CfgManager CfgMng;

class CEnvironment
{
public:
	CEnvironment(void);
	CEnvironment(char * fname);
	~CEnvironment(void);
	
	CGrid Grid_Past; //actual grid
	CGrid Grid; //grid for the following time value
	int Time;
	CStatisticsEnv Statist; //Statistics of the environment
	bool DisplayOn;
				
	void MakeBeetleAction(int x, int y);
	int GetBeetleNeighborCell(int x, int y, char direction, char L_R_F, CBeetle ** beetle =0);
	void NextTime(void); // increases time by 1
	bool PrintEnv(void);


	bool LoadEnv(char * filename=0);
	bool SaveEnv(char * filename);
	bool CreateDefaultEnv(void);

	CBeetle * CreateRandomBeetle();
	bool CreateRandomEnv(void);

	bool MakeFlowerGrow(int x, int y);
	bool A_Copulate(int x, int y, CBeetle * beetle);
	bool A_Step(int x, int y, char direction);
	void A_RotateLeft(CBeetle * beetle);
	void A_RotateRight(CBeetle * beetle);
	char RotateDirection(char direction, char L_R);
	void CountStatistics(void);

	char * getMapFileName(char *fname);
	char * getFlowersFileName(char *fname);
	char * getBeetlesFileName(char *fname);
	char * getTimeStatsFileName(char *fname);


};
