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
		QString LearnStr;
		if(ListRuns.at(l)->LearningOn)	LearnStr="Learning On"; 
			else LearnStr="Learning Off";
		fprintf(stdout,("Script "+
					ListRuns.at(l)->DirName+" - configuration: \n "+
					ListRuns.at(l)-> MapFN+" "+
					ListRuns.at(l)-> BeetlesFN+" "+
					QString::number(ListRuns.at(l)-> Seed)+" "+
					QString::number(ListRuns.at(l)-> NumRandBeetles)+" "+
					QString::number(ListRuns.at(l)-> EndTime)+" "+
					LearnStr+" "+	
					ListRuns.at(l)->EffFN+" "+										
					QString::number(ListRuns.at(l)-> StepCost)+" "+
					QString::number(ListRuns.at(l)-> RotCost)+" "+
					QString::number(ListRuns.at(l)-> CopulCost)+" "+
					QString::number(ListRuns.at(l)-> WaitCost)+" "+										
					ListRuns.at(l)-> AggrStatFN+" "+
					ListRuns.at(l)-> HistStatFN+" "+
					ListRuns.at(l)-> TimeStatFN+" "+
					ListRuns.at(l)-> EnvFN+" "+
					QString::number(ListRuns.at(l)-> SaveTimeAggrReg)+" "+ 
					QString::number(ListRuns.at(l)-> SaveTimeHistReg)+" "+ 
					QString::number(ListRuns.at(l)-> SaveTimeEnvReg)+" "+
					QString::number(ListRuns.at(l)-> SaveTimesAggr[0]) +" "+
					QString::number(ListRuns.at(l)-> SaveTimesHist[0])+" "+
					QString::number(ListRuns.at(l)-> SaveTimesEnv[0])+"\n").toAscii().data() );

		oneRun=	ListRuns.at(l);
		//QMessageBox::information (NULL,"","1");
		env = new CEnvironment(oneRun);
		//QMessageBox::information (NULL,"","2");
		QDir::setCurrent(oneRun->DirName);
		int time;
		int I,J;
		int i_agr=0,i_hist=0,i_env=0;
		//QMessageBox::information (NULL,"","Life "+oneRun->DirName+" starts");
		for(time=0;time<=oneRun->EndTime;time++)
		{
			for(I=0;I<env->Grid_Past.G_Width;I++)
			for(J=0;J<env->Grid_Past.G_Height;J++)
			{
				if (env->Grid_Past.GetCellContent(I,J)==BEETLE) env->MakeBeetleAction(I,J);
				else if (env->Grid_Past.GetCellContent(I,J)==NOTHING) env->MakeFlowerGrow(I,J);
				else if (env->Grid_Past.GetCellContent(I,J)==FLOWER) env->MakeFlowerDie(I,J);
				//if there is a wall, flower of something bad, do nothing
			}


			
			//if (time%10==0) env->Statist.SaveActAgrStatist(oneRun->AggrStatFN.toAscii().data(),time);
			if (time==oneRun->SaveTimesAggr[i_agr])
			{
				env->CountStatistics();
				i_agr++;
				env->Statist.SaveActAgrStatist((QString::number(time)+oneRun->AggrStatFN).toAscii().data(),time);
			}
			if (time==oneRun->SaveTimesHist[i_hist])
			{
				i_hist++;
				env->Statist.SaveActHistStatist((QString::number(time)+oneRun->HistStatFN).toAscii().data(),time,&(env->Grid));
			}
			if (time==oneRun->SaveTimesEnv[i_env])
			{
				i_env++;
				env->SaveEnv((oneRun->EnvFN+QString::number(time)).toAscii().data());
			}
			if ((oneRun->SaveTimeAggrReg!=0) &&(time % oneRun->SaveTimeAggrReg==0))		
			{
				env->CountStatistics();
				env->Statist.SaveActAgrStatist((QString::number(time)+oneRun->AggrStatFN).toAscii().data(),time);
			}

			if ((oneRun->SaveTimeHistReg!=0) &&(time % oneRun->SaveTimeHistReg==0))		
				env->Statist.SaveActHistStatist((QString::number(time)+oneRun->HistStatFN).toAscii().data(),time,&(env->Grid));

			if ((oneRun->SaveTimeEnvReg!=0) &&(time % oneRun->SaveTimeEnvReg==0))	
				env->SaveEnv((oneRun->EnvFN+QString::number(time)).toAscii().data());
				

			env->NextTime();

		}
		env->Statist.SaveTimeStatist_InColumnsAppend(oneRun->TimeStatFN.toAscii().data());
		QDir::setCurrent("..");
		fprintf(stdout,("\nScript "+oneRun->DirName+" finnished.\n\n").toAscii().data());
		delete(env);
	}
	return 1;
}

