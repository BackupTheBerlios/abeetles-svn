#include <QString>
#include <QList>
#include "COneRun.h"
#include "Environment.h"
#include "RunScript.h"
#include <QMessageBox>

CRunScript::CRunScript(QList<COneRun> listRuns)
{
	ListRuns = listRuns;
	
}

int CRunScript::run()
{
	COneRun oneRun;
	int i;
	for (i=0;i<ListRuns.size();i++)
	{
		QMessageBox::information (NULL,"Script",	ListRuns.at(i).DirName+" "+
										ListRuns.at(i). MapFN+" "+
										ListRuns.at(i). BeetlesFN+" "+
										QString::number(ListRuns.at(i). Seed)+" "+
										QString::number(ListRuns.at(i). NumRandBeetles)+" "+
										QString::number(ListRuns.at(i). EndTime)+" "+
										ListRuns.at(i).EffFN+" "+										
										QString::number(ListRuns.at(i). StepCost)+" "+
										QString::number(ListRuns.at(i). RotCost)+" "+
										QString::number(ListRuns.at(i). CopulCost)+" "+
										QString::number(ListRuns.at(i). WaitCost)+" "+										
										ListRuns.at(i). AggrStatFN+" "+
										ListRuns.at(i). HistStatFN+" "+
										ListRuns.at(i). TimeStatFN+" "+
										QString::number(ListRuns.at(i). SaveTimeAggrReg)+" "+ 
										QString::number(ListRuns.at(i). SaveTimeHistReg)+" "+ 
										QString::number(ListRuns.at(i). SaveTimesAggr[0]) +" "+
										QString::number(ListRuns.at(i). SaveTimesHist[0]) );
	}
}