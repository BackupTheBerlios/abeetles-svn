#pragma once
#include "Beetle.h"
#include "Grid.h"
#include <windows.h>



class CfgManager
{
public:
	CfgManager(void);
	~CfgManager(void);

	bool SaveBeetles(CGrid * grid,char * filename);
	bool LoadGridShape(int * G_FirstIndex, int * G_Width, int * G_Height );
	bool LoadCfgFile(char* cfg_filename);
	bool LoadMapFromBmp(CGrid * grid, wchar_t * filename);
	bool LoadBeetles(CGrid * grid, char * filename);
	bool LoadEnergyFromFlowerFromBmp(int EFF_Age [EFF_BMP_X], wchar_t * filename);

protected:
	int FlowerProbabilityFromColor(COLORREF colorRef);

};
