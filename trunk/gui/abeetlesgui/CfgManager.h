#pragma once
#include "Beetle.h"
#include "Grid.h"
//	#include <windows.h>

class QImage;



class CfgManager
{
public:
	CfgManager(void);
	~CfgManager(void);

	bool SaveBeetles(CGrid * grid,char * filename);
	bool SaveFlowers(CGrid * grid,char * filename);
	bool SaveMapToBmp(CGrid * grid, char * filename);

	//bool LoadCfgFile(char* cfg_filename);
	bool LoadMapFromBmp(CGrid * grid, char * filename);
	bool LoadBeetles(CGrid * grid, char * filename);
	bool LoadFlowers(CGrid * grid, char * filename);
	QImage LoadEnergyFromFlowerFromBmp(int EFF_Age [EFF_BMP_X], char * filename); //, QImage image);
	int ColorFromFlowerProbability(int prob);

protected:
	int FlowerProbabilityFromColor(int colorNum);
	

};
