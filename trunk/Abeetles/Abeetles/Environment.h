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
	CEnvironment(char * cfg_filename,char * btl_filename, wchar_t * map_filename, wchar_t * eff_filename);
	~CEnvironment(void);
	
	CGrid Grid_Past; //actual grid
	CGrid Grid; //grid for the following time value
	int Time;
	CStatisticsEnv Statist; //Statistics of the environment
				
	void MakeBeetleAction(int x, int y);
	int GetBeetleNeighborCell(int x, int y, char direction, char L_R_F, CBeetle ** beetle =0);
	void NextTime(void); // increases time by 1
	bool PrintEnv(void);
	CBeetle * CreateRandomBeetle();
	bool LoadEnv(char * btl_filename, wchar_t * map_filename);
	bool SaveEnv(char * btl_filename);
	bool CreateRandomEnv(void);
	bool MakeFlowerGrow(int x, int y);
	bool A_Copulate(int x, int y, CBeetle * beetle);
	bool A_Step(int x, int y, char direction);
	void A_RotateLeft(CBeetle * beetle);
	void A_RotateRight(CBeetle * beetle);
	char RotateDirection(char direction, char L_R);
	void CountStatistics(void);
	bool CreateDefaultEnv(void);
};
