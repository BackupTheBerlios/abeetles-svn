#include <QString>
#include <QTime>
#include <QDir>
#include <QFile>
#include "COneRun.h"
#include "defines.h"
#include <iostream>

extern int RandInBound (int bound);

COneRun::COneRun()
{
	DirName = "newdir"+QString::number(RandInBound(20));
	MapFN = MAP_BMP_FILE;
	EffFN = EFF_BMP_FILE;
	AggrStatFN="aggr.txt";
	HistStatFN="hist.txt";
	TimeStatFN="time.txt";
	EnvFN="env"; //without suffix!!
	LearningOn=true;
	IsStepOnFlower = true;
	IsBtlRandom=true;
	IsFlowersDie=true; 
	IsNoExpectations=true;
	Seed=-1;
	NumRandBeetles=-1;
	EndTime=MAXTIME;
	MutationProb=MUTATION_PROB_DEFAULT;
	//cost of actions
	StepCost=A_STEP_COSTS;
	RotCost=A_ROTATION_COSTS;
	CopulCost=A_COPULATION_COSTS;
	WaitCost=A_WAIT_COSTS;
	//Names of files of statistics... Time will be added

	SaveTimeAggrReg=0; //if ==0, array saveTimesAggr is used
	SaveTimeHistReg=0; // if ==0, array saveTimesHist is used
	SaveTimeEnvReg=0; // if ==0, array saveTimesEnv is used

	int i=0;
	for(i=0;i<50;i++)
	{
		SaveTimesAggr[i]=-1 ;
		SaveTimesHist[i]=-1 ;
		SaveTimesEnv[i]=-1 ;
	}
}

bool COneRun::setDirName (QString dirName)
{
	if (dirName.isNull()) return false;
	if ((QDir::current().mkdir(dirName)==true) ||(QDir::current().exists(dirName)))
	{
		DirName=dirName;
		return true;
	}

	return false;	 
}

bool COneRun::setMapFN(QString mapFN)
{
	if (QFile::exists(mapFN)==false) return false;
	MapFN=mapFN;
	return true;
}

void COneRun::setRandom(int seed, int numRandBeetles)
{	
	if (seed==-1) 		
		Seed= RandInBound( MAX_INT);
	else Seed=seed;
	NumRandBeetles=numRandBeetles;
	IsBtlRandom=true;
}

bool COneRun::setBeetlesFN(QString beetlesFN)
{
	if (false==QFile::exists(beetlesFN)) return false;
	BeetlesFN=beetlesFN;
	IsBtlRandom=false;
	return true;
}

void COneRun::setEndTime(int endTime)
{
	if ( (endTime>0) && (endTime<MAXTIME))
		EndTime=endTime;
	else 
		EndTime=MAXTIME;
		
}

void COneRun::setLearningOn (bool learningOn)
{
	LearningOn=learningOn;
}

void COneRun::setIsStepOnFlower (bool isStepOnFlower)
{
	IsStepOnFlower=isStepOnFlower;
}

void COneRun::setIsFlowersDie (bool isFlowersDie)
{
	IsFlowersDie=isFlowersDie;
}
void COneRun::setIsNoExpectations (bool isNoExpectations)
{
	IsNoExpectations=isNoExpectations;
}
bool COneRun::setEffFN (QString effFN)
{
	if (false==QFile::exists(effFN)) return false;
	EffFN=effFN;
	return true;
}

void COneRun::setMutationProb(int mProb)
{
	if (mProb<0) mProb=0;
	if (mProb>10) mProb=10;
	MutationProb=mProb;
}

void COneRun::setCostsOfActions( int step, int rot, int copul, int wait)
{
	StepCost = step;
	RotCost = rot;
	CopulCost = copul;
	WaitCost = wait;
}

//Names of files of statistics... Time will be added
void COneRun::setAggrStatFN( QString aggrStatFN)
{
	if (aggrStatFN.contains(".")) AggrStatFN=aggrStatFN;
	else AggrStatFN= aggrStatFN+".txt";
}
void COneRun::setHistStatFN( QString histStatFN)
{
	if (histStatFN.contains(".")) HistStatFN=histStatFN;
	else HistStatFN= histStatFN+".txt";
}
void COneRun::setTimeStatFN( QString timeStatFN)
{
	if (timeStatFN.contains(".")) TimeStatFN=timeStatFN;
	else TimeStatFN= timeStatFN+".txt";
}
void COneRun::setEnvFN( QString envFN)
{
	if (envFN.contains(".")) EnvFN=envFN.left(envFN.indexOf(".")); //EnvFN must be without suffix
	EnvFN= envFN;
}

void COneRun::setSaveTimeAggrReg (int time)
{
	SaveTimeAggrReg=time;
}

void COneRun::setSaveTimeHistReg (int time)
{
	SaveTimeHistReg=time;
}

void COneRun::setSaveTimeEnvReg (int time)
{
	SaveTimeEnvReg=time;
}


void COneRun::setSaveTimesAggr (int * timeArray)
{
	int i=0;
	while (timeArray[i]!=-1)
	{
		SaveTimesAggr[i]=timeArray[i];
		i++;
	}
	SaveTimesAggr[i]=timeArray[i]; //the copy of ending -1 value
}

void COneRun::setSaveTimesHist(int * timeArray)
{
	int i=0;
	while (timeArray[i]!=-1)
	{
		SaveTimesHist[i]=timeArray[i];
		i++;
	}
	SaveTimesHist[i]=timeArray[i]; //the copy of ending -1 value
}

void COneRun::setSaveTimesEnv(int * timeArray)
{
	int i=0;
	while (timeArray[i]!=-1)
	{
		SaveTimesEnv[i]=timeArray[i];
		i++;
	}
	SaveTimesEnv[i]=timeArray[i]; //the copy of ending -1 value
}
