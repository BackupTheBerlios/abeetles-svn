#pragma once
#include "Beetle.h"
#include "Grid.h"
#include <windows.h>



class CfgManager
{
public:
	CfgManager(void);
	~CfgManager(void);
	//bool GetGridInit(CGrid * Grid);functionality removed to Env.LoadEnv()
	//bool GetOptionsInit(void);functionality removed to LoadCfgFile()
	//bool LoadNextBeetle(FILE * file, CBeetle* beetle); functionality removed to LoadBeetle
	bool SaveBeetles(CGrid * grid,char * filename);
	bool LoadGridShape(int * G_FirstIndex, int * G_Width, int * G_Height );
	int LoadCfgFile(char* cfg_filename);
	bool LoadMapFromBmp(CGrid * Grid, wchar_t * filename);
	bool LoadBeetles(CGrid * grid, char * filename);
protected:
	int FlowerProbabilityFromColor(COLORREF colorRef);

};
