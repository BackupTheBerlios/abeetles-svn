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
	~CEnvironment(void);
	
	CGrid Grid; //actual grid
	CGrid Grid_Next; //grid for the following time value
				
	void MakeBeetleAction(int x, int y);
	int GetBeetleNeighborCell(int x, int y, char l_r_f);
	void A_Step(int x, int y, char direction);
	void NextTime(void); // increases time by 1
};
