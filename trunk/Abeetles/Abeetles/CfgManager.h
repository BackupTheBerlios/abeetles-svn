#pragma once
#include "Beetle.h"
#include "Grid.h"
#include <windows.h>



class CfgManager
{
public:
	CfgManager(void);
	~CfgManager(void);
	bool GetGridInit(CGrid * Grid);		
	bool GetOptionsInit(void);
	bool LoadNextBeetle(FILE * file, CBeetle* beetle);
protected:
	bool LoadGridShape(int * G_FirstIndex, int * G_Width, int * G_Height );
	int LoadBeetleCfgFile(void);
	bool LoadEnvironmentFromBmp(CGrid * Grid);
	int FlowerProbabilityFromColor(COLORREF colorRef);
};
