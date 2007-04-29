#pragma once
#include "Beetle.h"
#include "CfgManager.h"

//make globals visible
extern CfgManager CfgMng;

class CEnvironment
{
public:
	CEnvironment(void);
	~CEnvironment(void);
	int Grid[20][20][2]; //aktual grid
	int Grid_Next [20][20][2]; //grid for the next time value
	int G_FirstIndex; //Grid[G_FirstIndex][G_FirstIndex][0]is the top left corner of the grid
	int G_Width; //Grid[G_FirstIndex+G_Width][G_FirstIndex+G_Height][0]is the bottom right corner of the grid
	int G_Height;


	int GetCell(int x, int y);
	void MakeBeetleAction(int x, int y);
	int GetBeetleNeighborCell(int x, int y, char l_r_f);
	void A_Step(int x, int y, char direction);
	void NextTime(void);
protected:
	int WestBorder(void);
	int NorthBorder(void);
	int EastBorder(void);
	int SouthBorder(void);
};
