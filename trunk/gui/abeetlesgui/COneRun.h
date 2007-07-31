#pragma once
#include <QString>

class COneRun
{
public:
	COneRun();


	QString DirName;
	QString MapFN;
	bool IsBtlRandom;
	bool IsStepOnFlower;
	bool LearningOn;
	QString BeetlesFN;
	int Seed;
	int NumRandBeetles;
	int EndTime;
	QString EffFN;
	int MutationProb; //0%-10%
	//cost of actions
	int StepCost;
	int RotCost;
	int CopulCost;
	int WaitCost;
	//Names of files of statistics... Time will be added
	QString AggrStatFN;
	QString HistStatFN;
	QString TimeStatFN;
	QString EnvFN; //without suffix!!

	int SaveTimeAggrReg; //if ==0, array saveTimesAggr is used
	int SaveTimeHistReg; // if ==0, array saveTimesHist is used
	int SaveTimeEnvReg; // if ==0, array saveTimesEnv is used
	int SaveTimesAggr[50] ;
	int SaveTimesHist[50] ;
	int SaveTimesEnv[50];

	bool setDirName (QString dirName);
	bool setMapFN(QString mapFN);
	void setRandom(int seed=-1, int numRandBeetles=-1);
	bool setBeetlesFN(QString beetlesFN);
	void setEndTime(int endTime);
	void setLearningOn (bool learningOn);
	void setIsStepOnFlower(bool isStepOnFlower);
	bool setEffFN (QString effFN);
	void setMutationProb(int mProb);
	void setCostsOfActions( int step, int rot, int copul, int wait);
	void setAggrStatFN( QString aggrStatFN);
	void setHistStatFN( QString histStatFN);
	void setTimeStatFN( QString timeStatFN);
	void setEnvFN( QString envFN);
	void setSaveTimeAggrReg (int time);
	void setSaveTimeHistReg (int time);
	void setSaveTimeEnvReg (int time);
	void setSaveTimesAggr (int * timeArray);
	void setSaveTimesHist(int * timeArray);
	void setSaveTimesEnv(int * timeArray);

};
