#pragma once
#include "Beetle.h"
#include "Grid.h"
#include "CfgManager.h"
#include "StatisticsEnv.h"
#include <QWidget>
#include "defines.h"

//make globals visible
extern CfgManager CfgMng;
class QImage;

class CEnvironment: public QObject
{
	Q_OBJECT
public:
	CEnvironment(void);
	CEnvironment::CEnvironment(COneRun * oneRun);
	//CEnvironment(char * fname);//constructor for loading environment from file
	//CEnvironment::CEnvironment(int seed); // creation of random environment
	~CEnvironment(void);
	
	bool IsEmpty;
	CGrid Grid_Past; //actual grid
	CGrid Grid; //grid for the following time value
	int Time;
	int StepCost;int RotCost;int CopulCost;int WaitCost;
	bool LearningOn;
	CStatisticsEnv Statist; //Statistics of the environment
	//bool DisplayOn; removed to MainWindow
				
	void MakeBeetleAction(int x, int y);
	int GetBeetleNeighborCell(int x, int y, char direction, char L_R_F, CBeetle ** beetle =0);
	void NextTime(void); // increases time by 1
	bool PrintEnv(void);
	bool CleanEnv();


	bool LoadEnv(char * filename=0);
	bool SaveEnv(char * filename);
	bool CreateDefaultEnv(void);
	
	bool MakeFlowerGrow(int x, int y);
	bool A_Copulate(int x, int y, CBeetle * beetle);
	bool A_Step(int x, int y, char direction);
	void A_RotateLeft(CBeetle * beetle);
	void A_RotateRight(CBeetle * beetle);
	char RotateDirection(char direction, char L_R);
	void CountStatistics(void);

	char * getMapFileName(char *fname);
	char * getFlowersFileName(char *fname);
	char * getBeetlesFileName(char *fname);
	char * getTimeStatsFileName(char *fname);

	CBeetle * CreateRandomBeetle();
	bool FillEmptyEnvRandomly(int seed,int numBeetles=DEFAULT_NUM_BEETLES, char * mapFN=0);
};
