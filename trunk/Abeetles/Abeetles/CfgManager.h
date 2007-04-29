#pragma once
#include "Beetle.h"


class CfgManager
{
public:
	CfgManager(void);
	~CfgManager(void);
	bool GetGridInit(int Grid [20][20][2]/*3D array*/,int FirstIndex, int Width, int Height);	
	bool GetGridShape(int * G_FirstIndex, int * G_Width, int * G_Height );
	bool GetOptionsInit(void);
	bool LoadNextBeetle(FILE * file, CBeetle* beetle);
protected:
	int LoadBeetleCfgFile(void);
	int LoadEnvironmentFromBmp(int G_x, int G_y);
};
