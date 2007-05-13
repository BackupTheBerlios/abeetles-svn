#pragma once
#include "Beetle.h"
#include "Grid.h"
#include "CfgManager.h"

//make globals visible
extern CfgManager CfgMng;

class CEnvironment
{
public:
	CEnvironment(void);
	CEnvironment(char * cfg_filename,char * btl_filename, wchar_t * map_filename);
	~CEnvironment(void);
	
	CGrid Grid; //actual grid
	CGrid Grid_Next; //grid for the following time value
				
	void MakeBeetleAction(int x, int y);
	int GetBeetleNeighborCell(int x, int y, char direction, char L_R_F, CBeetle ** beetle =0);
	void A_Step(int x, int y, char direction);
	void NextTime(void); // increases time by 1
	bool PrintEnv(void);
	CBeetle * CreateRandomBeetle();
	bool LoadEnv(char * btl_filename, wchar_t * map_filename);
	bool SaveEnv(char * btl_filename);
	bool CreateRandomEnv(void);
	bool MakeFlowerGrow(int x, int y);
	bool A_Copulate(int x, int y, CBeetle * beetle);
	int RotateDirection(char direction, char L_R);
};
