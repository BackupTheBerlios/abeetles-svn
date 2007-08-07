#include <QString>
#include <QList>
#include "COneRun.h"
#include "Environment.h"
#include "Beetle.h"
#include "StatisticsEnv.h"
#include "RunScript.h"
#include <QMessageBox>
#include <QDir>

CRunScript::CRunScript(QString script)//QList<COneRun*> listRuns)
{

	ListRuns = CfgMng.LoadScript(script);
	
}

int CRunScript::run()
{
	COneRun * oneRun;
	CEnvironment * env;
	int l;
	for (l=0;l<ListRuns.size();l++)
	{
		QString LearnStr;QString FlowersDieStr;QString StepOnflowerStr;QString NoExpectationsStr;
		if(ListRuns.at(l)->LearningOn)	LearnStr="On"; 
			else LearnStr="Off";
		if(ListRuns.at(l)->IsFlowersDie) FlowersDieStr="On";
			else FlowersDieStr="Off";
		if(ListRuns.at(l)->IsStepOnFlower) StepOnflowerStr="Used";
			else StepOnflowerStr="Not used";
		if(ListRuns.at(l)->IsNoExpectations) NoExpectationsStr="Used";
			else NoExpectationsStr="Not used";
			fprintf(stdout,(QString::fromAscii("Script ")+
					"DirName="+ListRuns.at(l)->DirName+" - configuration: \n "+
					"MapFN="+ListRuns.at(l)-> MapFN+" "+
					"BeetlesFN="+ListRuns.at(l)-> BeetlesFN+" "+
					"Seed="+QString::number(ListRuns.at(l)-> Seed)+" "+
					"NumRandBeetles="+QString::number(ListRuns.at(l)-> NumRandBeetles)+" "+
					"EndTime="+QString::number(ListRuns.at(l)-> EndTime)+" "+
					"Learning="+LearnStr+" "+	
					"FlowersDie="+FlowersDieStr+" "+
					"StepOnFlower="+StepOnflowerStr+" "+
					"NoExpectations="+NoExpectationsStr+" "+
					"MutationProb="+QString::number(ListRuns.at(l)->MutationProb)+" "+
					"EffFN="+ListRuns.at(l)->EffFN+" "+										
					"StepCost="+QString::number(ListRuns.at(l)-> StepCost)+" "+
					"RotCost="+QString::number(ListRuns.at(l)-> RotCost)+" "+
					"CopulCost="+QString::number(ListRuns.at(l)-> CopulCost)+" "+
					"WaitCost="+QString::number(ListRuns.at(l)-> WaitCost)+" "+										
					"AggrStatFN="+ListRuns.at(l)-> AggrStatFN+" "+
					"HistStatFN="+ListRuns.at(l)-> HistStatFN+" "+
					"TimeStatFN="+ListRuns.at(l)-> TimeStatFN+" "+
					"EnvFN="+ListRuns.at(l)-> EnvFN+" "+
					"SaveTimeAggrReg="+QString::number(ListRuns.at(l)-> SaveTimeAggrReg)+" "+ 
					"SaveTimeHistReg="+QString::number(ListRuns.at(l)-> SaveTimeHistReg)+" "+ 
					"SaveTimeEnvReg="+QString::number(ListRuns.at(l)-> SaveTimeEnvReg)+" "+
					"SaveTimesAggr-1st="+QString::number(ListRuns.at(l)-> SaveTimesAggr[0]) +" "+
					"SaveTimesHist-1st="+QString::number(ListRuns.at(l)-> SaveTimesHist[0])+" "+
					"SaveTimesEnv-1st="+QString::number(ListRuns.at(l)-> SaveTimesEnv[0])+"\n").toAscii().data() );

		oneRun=	ListRuns.at(l);
		//QMessageBox::information (NULL,"","1");
		env = new CEnvironment(oneRun);
		QDir::setCurrent(oneRun->DirName);
		env->NextTime();
		//int I,J;
		int i_agr=0,i_hist=0,i_env=0;
		//QMessageBox::information (NULL,"","Life "+oneRun->DirName+" starts");
		while(true)
		{				

			env->Make1Update();
			
			//if (time%10==0) env->Statist.SaveActAgrStatist(oneRun->AggrStatFN.toAscii().data(),time);
			if (env->Time==oneRun->SaveTimesAggr[i_agr])
			{
				env->CountStatistics();
				i_agr++;
				env->Statist.SaveActAgrStatist((QString::number(env->Time)+oneRun->AggrStatFN).toAscii().data(),env->Time);
			}
			if (env->Time==oneRun->SaveTimesHist[i_hist])
			{
				i_hist++;
				env->Statist.SaveActHistStatist((QString::number(env->Time)+oneRun->HistStatFN).toAscii().data(),env->Time,&(env->Grid));
			}
			if (env->Time==oneRun->SaveTimesEnv[i_env])
			{
				i_env++;
				env->SaveEnv((oneRun->EnvFN+QString::number(env->Time)).toAscii().data());
			}
			if ((oneRun->SaveTimeAggrReg!=0) &&(env->Time % oneRun->SaveTimeAggrReg==0))		
			{
				env->CountStatistics();
				env->Statist.SaveActAgrStatist((QString::number(env->Time)+oneRun->AggrStatFN).toAscii().data(),env->Time);
			}

			if ((oneRun->SaveTimeHistReg!=0) &&(env->Time % oneRun->SaveTimeHistReg==0))		
				env->Statist.SaveActHistStatist((QString::number(env->Time)+oneRun->HistStatFN).toAscii().data(),env->Time,&(env->Grid));

			if ((oneRun->SaveTimeEnvReg!=0) &&(env->Time % oneRun->SaveTimeEnvReg==0))	
				env->SaveEnv((oneRun->EnvFN+QString::number(env->Time)).toAscii().data());
				

			env->NextTime();
			if (env->Time>=oneRun->EndTime) break;
			if (env->Statist.NumBeetles==0) break;

		}
		env->Statist.SaveTimeStatist_InColumnsAppend((QString::number(env->Time)+oneRun->TimeStatFN).toAscii().data());
		QDir::setCurrent("..");
		fprintf(stdout,("\nScript "+oneRun->DirName+" finnished after "+QString::number(env->Time)+" updates.\n\n").toAscii().data());
		delete(env);
	}
	return 1;
}

