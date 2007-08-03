#pragma once
#include "Beetle.h"
#include "Grid.h"
#include <QList>
#include <QString>
#include "COneRun.h"


class QImage;



class CfgManager
{
public:
	CfgManager(void);
	~CfgManager(void);
	
	float FlowerGrowingRatioTable[9];

	bool SaveBeetles(CGrid * grid,char * filename);
	bool SaveBeetles(CGrid * grid,QString filename);
	bool SaveFlwAndOpt(CGrid * grid,int time, bool learningOn,int flowerGrowingRatio,int mutationProb,int stepCost, int rotCost, int copulCost,int waitCost,char * filename);
	bool SaveFlwAndOpt(CGrid * grid,int time, bool learningOn, int flowerGrowingRatio, int mutationProb,int stepCost, int rotCost, int copulCost,int waitCost,QString filename);
	bool SaveMapToBmp(CGrid * grid, char * filename);
	bool SaveMapToBmp(CGrid * grid, QString filename);
	bool SaveEffToBmp(QString filename);
	bool SaveEffToBmp(char * filename);

	//bool LoadCfgFile(char* cfg_filename);
	bool LoadMapFromBmp(CGrid * grid, char * filename);
	bool LoadMapFromBmp(CGrid * grid, QString filename);
	bool LoadBeetles(CGrid * grid, char * filename);
	bool LoadBeetles(CGrid * grid, QString filename);
	bool LoadFlwAndOpt(CGrid * grid,int *time, bool *learningOn,int* flowerGrowingRatio, int * mutationProb,int *stepCost, int *rotCost, int *copulCost,int *waitCost, char * filename);
	bool LoadFlwAndOpt(CGrid * grid,int *time, bool *learningOn,int* flowerGrowingRatio, int * mutationProb,int *stepCost, int *rotCost, int *copulCost,int *waitCost, QString filename);
	QImage LoadEffFromBmp(int EFF_Age [EFF_BMP_X], char * filename); //, QImage image);
	QImage LoadEffFromBmp(int EFF_Age [EFF_BMP_X], QString filename); //, QImage image);

	int ColorFromFlowerProbability(int prob);
	QList<COneRun*> LoadScript(QString scriptFN);

protected:
	int FlowerProbabilityFromColor(int colorNum);
	

};
