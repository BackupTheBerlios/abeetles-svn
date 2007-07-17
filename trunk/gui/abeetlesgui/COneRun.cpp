#include <QString>
#include <QTime>
#include <QDir>
#include <QFile>
#include "COneRun.h"

COneRun::COneRun()
{
}

bool COneRun::setDirName (QString dirName)
{
	if (dirName.isNull()) return false;
	if (QDir::mkdir(dirName)==true)
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

void COneRun::setRandom(int seed=-1, int numRandBeetles=-1)
{
	if (seed==-1) 
		seed=( QTime::currentTime().msec() * QTime::currentTime().min() ) % MAX_INT;
	else Seed=seed;
	NumRandBeetles=numRandBeetles;
	isBtlRandom=true;
}

void COneRun::setBeetlesFN(QString beetlesFN)
{
	if (false==QFile::exists(beetlesFN)) return false;
	BeetlesFN=beetlesFN;
	isBtlRandom=false;
	return true;
}

void COneRun::setEndTime(int endTime)
{
	if (endTime>0) && (endTime<MAXTIME)
		EndTime=endTime;
	else 
		EndTime=MAXTIME;
		
}
void COneRun::setEffFN (QString effFN)
{
	if (false==QFile::exists(effFN)) return false;
	EffFN=effFN;
	return true;
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

void COneRun::setSaveTimeAggrReg (int time)
{
	SaveTimeAggrReg=time;
}

void COneRun::setSaveTimeHistReg (int time)
{
	SaveTimeHistReg=time;
}

void COneRun::setSaveTimeAggr (int * timeArray)
{
	int i=0;
	while (timeArray[i]!=-1)
	{
		SaveTimeAggr[i]=timeArray[i];
		i++;
	}
	SaveTimeAggr[i]=timeArray[i]; //the copy of ending -1 value
}

void COneRun::setSaveTimeHist(int * timeArray)
{
	int i=0;
	while (timeArray[i]!=-1)
	{
		SaveTimeHist[i]=timeArray[i];
		i++;
	}
	SaveTimeHist[i]=timeArray[i]; //the copy of ending -1 value
}
	
