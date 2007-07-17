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

	bool SaveBeetles(CGrid * grid,char * filename);
	bool SaveBeetles(CGrid * grid,QString filename);
	bool SaveFlowers(CGrid * grid,char * filename);
	bool SaveFlowers(CGrid * grid,QString filename);
	bool SaveMapToBmp(CGrid * grid, char * filename);
	bool SaveMapToBmp(CGrid * grid, QString filename);

	//bool LoadCfgFile(char* cfg_filename);
	bool LoadMapFromBmp(CGrid * grid, char * filename);
	bool LoadMapFromBmp(CGrid * grid, QString filename);
	bool LoadBeetles(CGrid * grid, char * filename);
	bool LoadBeetles(CGrid * grid, QString filename);
	bool LoadFlowers(CGrid * grid, char * filename);
	bool LoadFlowers(CGrid * grid, QString filename);
	QImage LoadEnergyFromFlowerFromBmp(int EFF_Age [EFF_BMP_X], char * filename); //, QImage image);
	QImage LoadEnergyFromFlowerFromBmp(int EFF_Age [EFF_BMP_X], QString filename); //, QImage image);

	int ColorFromFlowerProbability(int prob);
	QList<COneRun*> LoadScript(QString scriptFN);

protected:
	int FlowerProbabilityFromColor(int colorNum);
	

};
