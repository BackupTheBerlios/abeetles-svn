#include "StdAfx.h"
#include "Environment.h"
#include <string.h>
#include "Beetle.h"
#include "CfgManager.h"
#include "defines.h"
#include <time.h>
#include <assert.h>
#include <QtGui>
#include <iostream>
#include <stdio.h>

extern int RandInBound (int bound);

CEnvironment::CEnvironment(void)
{
	//Grid is initialized in its constructor to default size and empty content.
	Time=0; 
	IsEmpty=true;
	StepCost=A_STEP_COSTS;RotCost=A_ROTATION_COSTS;CopulCost=A_COPULATION_COSTS;WaitCost=A_WAIT_COSTS;
	LearningOn=true;
	IsFlowersDie=true;
	FlowerGrowingRatio=FLOWERGROWINGRATIO_INIT;
	//MapFilePath ="";
	//EffFilePath ="";
	//BeetlesFilePath ="";

	

	//load function of Age and EnergyFromFlower from bmp file		
	if ((CBeetle::EffImg= CfgMng.LoadEffFromBmp(CBeetle::EFF_Age, EFF_BMP_FILE)).isNull())
	{
		QErrorMessage errDlg;
		errDlg.showMessage(QString::fromAscii("Loading of energy from flower bmp file ")+EFF_BMP_FILE+QString::fromAscii(" was not successful. Application will terminate."));
		exit (EXIT_FAILURE);
	}
	//1QMessageBox::information(NULL,"MyApp","Bmp map,"+QString::number(CBeetle::EffImg.width())+", "+QString::number(CBeetle::EffImg.height()));
	
}

CEnvironment::CEnvironment(COneRun * oneRun)
{
	//Grid is initialized in its constructor to default size and empty content.
	//pom=true; //DEBUG !!!!!!!!!!!!!!!!111

	Time=0; 
	IsEmpty=false;
	StepCost=oneRun->StepCost;
	RotCost=oneRun->RotCost;
	CopulCost=oneRun->CopulCost;
	WaitCost=oneRun->WaitCost;
	LearningOn=oneRun->LearningOn;
	FlowerGrowingRatio=FLOWERGROWINGRATIO_INIT;
	IsFlowersDie=oneRun->IsFlowersDie;
	CBeetle::MutationProb=oneRun->MutationProb;
	//MapFilePath ="";
	//EffFilePath ="";
	//BeetlesFilePath ="";

	//QMessageBox::information(NULL,"MyApp","2"+oneRun->EffFN);
	
		//QMessageBox::information(NULL,"MyApp","Bmp map,"+QString::number(CBeetle::EffImg.width())+", "+QString::number(CBeetle::EffImg.height()));
	if (oneRun->BeetlesFN.isEmpty())
	{
		if (false==	FillEmptyEnvRandomly(oneRun->Seed, oneRun->NumRandBeetles,oneRun->MapFN.toAscii().data(),oneRun->EffFN.toAscii().data(), oneRun->IsStepOnFlower,oneRun->IsNoExpectations))
		{
			CleanEnv();
			IsEmpty=true;
			return;
		}
		//QFileInfo mapFInfo(oneRun->MapFN);MapFilePath=mapFInfo.absoluteFilePath();
		//QFileInfo effFInfo(oneRun->EffFN);EffFilePath=effFInfo.absoluteFilePath();
	}
	else
	{
		int res = true;	
		QString err;
		//1st part - init environment: Loads map of environment
		if (false==CfgMng.LoadMapFromBmp(&Grid,oneRun->MapFN,&NumFreeCells)){res=false; err+="Map was not loaded.\n";}
		//2nd - load beetles and add them to half finished environment
		if (false==CfgMng.LoadBeetles(&Grid,oneRun->BeetlesFN)){res=false;	err+="Beetles were not loaded.\n";}	
		//Grid=Grid_Past;
		CountStatistics();
		IsEmpty=false;
		if (res==false)
		{
			CleanEnv();
			IsEmpty=true;
			return;
		}
		//QFileInfo mapFInfo(oneRun->MapFN);MapFilePath=mapFInfo.absoluteFilePath();
		//QFileInfo effFInfo(oneRun->EffFN);EffFilePath=effFInfo.absoluteFilePath();
		//QFileInfo beetlesFInfo (oneRun->BeetlesFN);BeetlesFilePath=beetlesFInfo.absoluteFilePath();
	}

	//QMessageBox::information(NULL,"MyApp","Filled Randomly"); //ch1
}
void CEnvironment::SetEnv(COneRun * oneRun)
{
	//Grid is initialized in constructor to default size and empty content.

	Time=0; 
	IsEmpty=false;
	StepCost=oneRun->StepCost;
	RotCost=oneRun->RotCost;
	CopulCost=oneRun->CopulCost;
	WaitCost=oneRun->WaitCost;
	LearningOn=oneRun->LearningOn;
	FlowerGrowingRatio=FLOWERGROWINGRATIO_INIT;
//	IsFlowersDie=oneRun->IsFlowersDie;..tady ne!
	CBeetle::MutationProb=oneRun->MutationProb;
	//MapFilePath ="";
	//EffFilePath ="";
	//BeetlesFilePath ="";

	//QMessageBox::information(NULL,"MyApp","2"+oneRun->EffFN);
	
		//QMessageBox::information(NULL,"MyApp","Bmp map,"+QString::number(CBeetle::EffImg.width())+", "+QString::number(CBeetle::EffImg.height()));
	if (oneRun->BeetlesFN.isEmpty())
	{
		if (false==	FillEmptyEnvRandomly(oneRun->Seed, oneRun->NumRandBeetles,oneRun->MapFN.toAscii().data(),oneRun->EffFN.toAscii().data(), oneRun->IsStepOnFlower,oneRun->IsNoExpectations))
		{
			CleanEnv();
			IsEmpty=true;
			return;
		}
		//QFileInfo mapFInfo(oneRun->MapFN);MapFilePath=mapFInfo.absoluteFilePath();
		//QFileInfo effFInfo(oneRun->EffFN);EffFilePath=effFInfo.absoluteFilePath();
	}
	else
	{
		//fprintf(stdout,"Beetles from file");
		int res = true;	
		QString err;
		//1st part - init environment: Loads map of environment
		if (false==CfgMng.LoadMapFromBmp(&Grid,oneRun->MapFN,&NumFreeCells)){res=false; err+="Map was not loaded.\n";}
		//2nd - load beetles and add them to half finished environment
		if (false==CfgMng.LoadBeetles(&Grid,oneRun->BeetlesFN)){res=false;	err+="Beetles were not loaded.\n";}	
		//Grid=Grid_Past;
		CountStatistics();
		IsEmpty=false;

	}

	//QMessageBox::information(NULL,"MyApp","Filled Randomly"); //ch1
}
/*
CEnvironment::CEnvironment(char * fname)
{	
	Time=0; //Remake to load it from some save file of the environment!
	LoadEnv(fname);	
	//load function of Age and EnergyFromFlower from bmp file	
	if ((CBeetle::EffImg= CfgMng.LoadEffFromBmp(CBeetle::EFF_Age, EFF_BMP_FILE)).isNull())
	{
		QErrorMessage errDlg;
		errDlg.showMessage(QString::fromAscii("Loading of energy from flower bmp file ")+EFF_BMP_FILE+QString::fromAscii(" was not successful."));
		exit (EXIT_FAILURE);
	}
}*/

CEnvironment::~CEnvironment(void)
{
}

void CEnvironment::MakeBeetleAction(int x, int y)
{
	int Left,Front,Right; //content of Beetle's neighbor cells
	CBeetle * beetle=NULL;
	Grid.GetCellContent(x,y,&beetle);
	//fprintf(stdout,"E:%dX:%dY:%d",beetle->GetEnergy(),x,y); //debug info about beetles location
	
	//beetle looks around him
	Left=GetBeetleNeighborCell(x,y,beetle->Direction,'L');
	Right=GetBeetleNeighborCell(x,y,beetle->Direction,'R');
	Front=GetBeetleNeighborCell(x,y,beetle->Direction,'F');
	
	assert (! beetle->IsDead());

	int action = INVALID_NUM;
	//HA_COPULATE - hardwired action of every beetle, when there is another beetle in front of him
	bool newChild = false;
	if (Front==BEETLE)
	{
		action=HA_COPULATE;
		if (beetle->Energy > (CopulCost + beetle->InvInChild))
		{
			if (true == A_Copulate(x,y,beetle))
			{										
				Statist.NumBeetles++;
				Statist.NumBirths++;
				beetle->ConsumeEnergy(CopulCost);
				newChild = true;
			}
			//else beetle->ConsumeEnergy(WaitCost);
		}
		else beetle->Energy =0;
	}	
	// if there was no copulation or no child created, beetle decides what to do according to what he sees and whether he is hungry
	
	if (newChild==false) action = beetle->Decide(Left,Front,Right);

	assert(action!=INVALID_NUM);

	//int Res = 0; //whether is the beetle still alive -1==DEAD

	//IDEA: beetle learns himself: if beetle is at the same place for ...

	//he makes the action he decided to do
	switch (action) 
	{
		case A_STEP: 
			if ((beetle->Energy > StepCost)&&(beetle->Energy>WaitCost))
			{
				if (true ==A_Step(x,y,beetle->GetDirection())) // check, whether the step was really made
					beetle->ConsumeEnergy(StepCost);
				else beetle->ConsumeEnergy(WaitCost);
			}
			else beetle->Energy =0;
			break;			
		case A_ROTATERIGHT: 
			if (beetle->Energy > RotCost)
			{ 
				A_RotateRight(beetle);
				beetle->ConsumeEnergy(RotCost);
			}
			else beetle->Energy =0;
			break;
		case A_ROTATELEFT: 
			if (beetle->Energy > RotCost)
			{
				A_RotateLeft(beetle);
				beetle->ConsumeEnergy(RotCost);
			}
			else beetle->Energy =0;
			break;
/*		case A_WAIT:		
			if (beetle->Energy > WaitCost)
			{
				beetle->ConsumeEnergy(WaitCost);
			}
			else beetle->Energy =0;
			break;*/
		case HA_COPULATE:
				//realized beforehead.
			break;
	}

	if (beetle->IsDead()) 
		{	
			beetle->Die();
			Statist.NumBeetles--;
			delete(beetle);	beetle = NULL;CBeetle::AlocBeetles--;
			Grid.SetCellContentAndUpdate(NOTHING,x,y);// even in old grid beetle must be removed - it would be reference to deleted memory
			//Grid.SetCellContent(NOTHING,x,y);//in next grid the beetle is on same position as in old one.
			return;
		}

	//when beetle meets some other beetle2 and didn't create child with beetle2
	// and the beetle is better = has more energy than him, he can learn something from beetle2 according to beetle's learning ability
	int b2_x, b2_y;
	CBeetle * beetle2=NULL;
	if ((newChild==false)&&(Front==BEETLE) && 
		(RandInBound(MAX_LEARN_ABILITY) < beetle->LearnAbility )) // beetles that have higher learnAbility, have higher probability, that they learn something
	{
		Grid.GetNeigborCellCoords(x,y,&b2_x,&b2_y, beetle->Direction);
		Grid.GetCellContent(b2_x,b2_y, &beetle2);
		if (beetle2 != NULL)
		{
			if ((LearningOn)&&(beetle2->Energy > beetle->Energy))
				beetle->LearnFrom(beetle2);
		}
	}


	beetle->Age++; //beetle is now 1 time slice older

	//count only on demand in Env.CountStatistics()
	//add changed features to statistics:
	//Statist.SumAge+=beetle->Age;
	//Statist.SumEnergy+=beetle->Energy;
	//Statist.SumNumChildren+=beetle->NumChildren;

}


int CEnvironment::GetBeetleNeighborCell(int x, int y, char direction, char L_R_F, CBeetle ** beetle)
{
	int x_n,y_n;
	direction = RotateDirection(direction,L_R_F);
	
	Grid.GetNeigborCellCoords(x,y,&x_n,&y_n,direction);
	return Grid.GetCellContent(x_n,y_n, beetle);		
}

/**
* Public method:
* Desc: Realizes one of the beetles actions
* System dependence:
* Usage comments: Called from CEnvironment::MakeBeetleAction()
* @return (Return values - meaning) : true - step was made, false - step was not made
* @param name [ descrip](Parameters - meaning):
* @throws name [descrip](Exceptions - meaning)
*/
bool CEnvironment::A_Step(int oldx, int oldy, char direction)
{
	CBeetle * beetle=NULL;
	Grid.GetCellContent(oldx,oldy,&beetle);
	int x=oldx;
	int y=oldy;
	Grid.GetNeigborCellCoords(oldx,oldy,&x,&y,direction);
	
	//check, whether other beetle has decided to go to same cell sooner:
	if (Grid.GetCellContent(x,y)==BEETLE) return false; // do nothing, the first beetle goes there.
	else if (Grid.GetCellContent(x,y)==WALL) return false;// do nothing, there is a wall
	else
	{		
			//if there is a flower in the Grid, beetle eats it.
			if (Grid.GetCellContent(x,y)==FLOWER) 
			{
				Statist.NumFlowers--;
				beetle->AddEnergy(beetle->EnergyFromFlower());
			}
			//if in this time slice has grown a flower in Grid, but was not in Grid, I cancel its growth
			//if ((Grid.GetCellContent(x,y)==NOTHING) && (Grid.GetCellContent(x,y)==FLOWER))
			//	Statist.NumFlowers--;
			
			Grid.SetCellContentAndUpdate(NOTHING, oldx, oldy);
			Grid.SetCellContentAndUpdate(BEETLE,x,y,beetle);						
	}	
	return true;
}



//Should be called at the end of a time slice.
void CEnvironment::NextTime(void)
{
	/*
	if ((pom==true) && (QFile::exists("`xs"))) 
	{
		pom=false;
		fprintf(stdout,("In NextTime:"+QString::number(Time)+", exists\n").toAscii().data());
	}*/
	if (QFile::exists("`xs")) QFile::remove("`xs");

	//fprintf(stdout,"In: Env::NextTime");
	Statist.NextTime(Time);
	if (Time>0) //If grid was already updated
		Grid.SwitchUpdatedGridToNotUpdated();
	Time++;
	//fprintf(stdout,("NumAloc: "+QString::number(CBeetle::AlocBeetles)+"UpdSymb: "+QString::number(Grid.UpdatedSymbol)+"\n").toAscii().data());
}

bool CEnvironment::PrintEnv(void)
{
	int I,J;
	CBeetle * beetle;
	int what=NOTHING;
	
	fprintf(stdout,"\n");

	//upper line of numbers
	putc(' ',stdout);
	for (I=0;I<Grid.G_Width;I++)
		putc((char)(I%10)+'0',stdout);
	fprintf(stdout,"\n");

	for(J=0;J<Grid.G_Height;J++)
	{
		putc((char)(J%10)+'0',stdout); //left column of numbers
		for(I=0;I<Grid.G_Width;I++)
		{
			what = Grid.GetCellContent(I,J,&beetle);
			if (what==NOTHING) {putc('.',stdout);continue;}
			if (what==FLOWER) {putc('~',stdout);continue;}
			if (what==WALL) {putc('W',stdout);continue;}
			if (what==BEETLE)
			{
				if ((beetle->Age)==0) putc('*',stdout);
				else
				{
					if (beetle->Direction == WEST)putc('<',stdout);
					if (beetle->Direction == NORTH)putc('A',stdout);
					if (beetle->Direction == EAST)putc('>',stdout);
					if (beetle->Direction == SOUTH)putc('V',stdout);
				}
			}
		}
		fprintf(stdout,"     ");
		for(I=0;I<Grid.G_Width;I++)
		{
			what=Grid.GetCellGrowingProbability(I,J);
			if (what==0) putc('.', stdout);
			if ((what>0)&&(what<50)) putc('o', stdout);
			if ((what>=50) && (what<100)) putc('0',stdout);
			if (what>=100) putc('O', stdout);

		}

		fprintf(stdout,"\n");
	}
	fprintf(stdout,"\n");
	
	return true;
}


/**
* Public method <br>
* Description: Loads all files of one environment. <br>
* System dependence: no. (Qt library)<br>
* Usage comments:<br>
* @return true, if the loading was successful (all files found), false otherwise. In both cases the Env is then is state ready for use - but maybe empty.  
* @param fname [Prefix of names of all files, that serve for storing of the evironment. Suffixes are standard, the same for all saved environments.](Parameters - meaning)
* @throws name [descrip](Exceptions - meaning)
* @see reference : adds reference to the "See Also" section. The reference can be any of the following:
*          o HTML tag/text, which is added unmodified
*          o a quoted string (e.g., "Foo Bar"), the contents of which are added unmodified
*          o [project].[ class-name][#member] [text ], which adds a link to the given member in class class-name in project project . If project is omitted, the current entity's project is assumed. If class-name is omitted, the current class is assumed. If member is omitted, the link is to the class-file. If text is omitted, default display text is added, based on the actual link.
* {@link reference } replaced with a reference that is built using the exact same syntax as the @see tag (above). For example:
*/

bool CEnvironment::LoadEnv(char * fname) 
{
	int res = true;
	
	if (fname==0) return false;
	

	//1st part - init environment: Loads map of environment
	if (false==CfgMng.LoadMapFromBmp(&Grid,getMapFileName(fname),&NumFreeCells)) res=false;

	if ((CBeetle::EffImg=CfgMng.LoadEffFromBmp(CBeetle::EFF_Age,getEffFileName(fname))).isNull()) res=false;

	//2nd part - load where flowers are
	if (false==CfgMng.LoadFlwAndOpt(&Grid,&Time,&LearningOn, 
		& FlowerGrowingRatio, &CBeetle::MutationProb, &StepCost,  &RotCost,  &CopulCost, 
		 &WaitCost, getFlowersFileName(fname))) res=false;

	//fprintf(stdout,("\n"+QString::number(Time)).toAscii().data());

	//3rd - load beetles and add them to half finished environment
	if (false==CfgMng.LoadBeetles(&Grid,getBeetlesFileName(fname)))res=false;
	
	//Grid=Grid_Past;

	CountStatistics();
	Statist.LastNumBirths=Statist.NumBirths;
	//4th - load time and time statistics, set Statist.startBuf to (Time+1)%BUF_SIZE
	if (false == Statist.LoadTimeStatist_FromColums(getTimeStatsFileName(fname)))
	{ res=false; }

	IsEmpty=false;

	if (res==false)
	{
		CleanEnv();
		IsEmpty=true;
		return false;
	}

	//QFileInfo mapFInfo(getMapFileName(fname));MapFilePath=mapFInfo.absoluteFilePath();
	//QFileInfo effFInfo(getEffFileName(fname));EffFilePath=effFInfo.absoluteFilePath();
	//QFileInfo beetlesFInfo (getBeetlesFileName(fname));BeetlesFilePath=beetlesFInfo.absoluteFilePath();

	return true;
}

bool CEnvironment::SaveEnv(char * fname)
{
	bool res=true;
	if (false==CfgMng.SaveBeetles(&Grid,getBeetlesFileName(fname)))res = false;
	if (false==CfgMng.SaveFlwAndOpt(&Grid,Time,LearningOn,FlowerGrowingRatio, CBeetle::MutationProb, StepCost, RotCost,CopulCost,WaitCost,getFlowersFileName(fname))) res = false;
	if (false==CfgMng.SaveEffToBmp(getEffFileName(fname))) res =false;

	//1QMessageBox::information(NULL,"MyApp",getMapFileName(fname));

	if (false==CfgMng.SaveMapToBmp(&Grid,getMapFileName(fname)))
	{
		QMessageBox::information(NULL,"MyApp","Bmp map not saved.");
		res=false;
	}

	//save the not saved part of timestats and rename it.
	if (false==Statist.SaveTimeStatist_InColumnsAppend(this->getTimeStatsFileName(fname))) res=false;

	return res;
}

bool CEnvironment::FillEmptyEnvRandomly(int seed, int numBeetles, char * mapFN, char * effFN, bool isStepOnFlower,bool isNoExpectations)
{
	//Grid.SetDefaultGridShape();
	//Grid and Grid now have old or default values.
	//fprintf(stdout, (QString::number(sizeof(CBeetle))+"\n").toAscii().data());
	//First part - init environment: Loads environment without beetles
	if (mapFN==0) mapFN=MAP_BMP_FILE;
	if (false==CfgMng.LoadMapFromBmp(&Grid,mapFN,&NumFreeCells))
	{
		return false;
	}

	//load function of Age and EnergyFromFlower from bmp file
	if (effFN==0) effFN=EFF_BMP_FILE;
	if ((CBeetle::EffImg= CfgMng.LoadEffFromBmp(CBeetle::EFF_Age, effFN)).isNull())
	{
		return false;
	}

	
	//1QMessageBox::information(NULL,"MyApp","Map is loaded"); //ch1

	//Second part - create beetles and add them to half finished environment
	srand( seed);//(unsigned)time( NULL ) );
	int I,J,K;
	CBeetle * beetle;
	int endCycle=0;
	if (numBeetles> (0.9*NumFreeCells))numBeetles=0.9*NumFreeCells;
	if (numBeetles==DEFAULT_NUM_BEETLES) endCycle=(Grid.G_Width*Grid.G_Height)/4;
	//if number of beetles is set, I run cycle many times. cycle stops when number of really placedbeetles== numBeetles
	else endCycle = MAX_INT; 
	//fprintf(stdout,("EndC: "+QString::number(endCycle)+"\n").toAscii().data());
	for (K=0;K<endCycle;K++)
	{
		I=RandInBound(Grid.G_Width);
		J=RandInBound(Grid.G_Height);
		if (Grid.GetCellContent(I,J)==NOTHING)
		{
			beetle=CBeetle::CreateRandomBeetle(isStepOnFlower,isNoExpectations);
			if (Grid.SetCellContentNotUpdate(BEETLE,I,J,beetle))
			{
				Statist.NumBeetles++;
				if ((numBeetles!=DEFAULT_NUM_BEETLES) && (Statist.NumBeetles>=numBeetles))
					break;
			}
			assert(beetle->GetEnergy()>0);
		}
		//fprintf(stdout,"E:%dX:%dY:%d",beetle->GetEnergy(),I,J); //debug info about beetles location

	}

	//1QMessageBox::information(NULL,"MyApp","Beetles are set."); //ch1

	//Grid=Grid_Past;
	Time=0;
	//1QMessageBox::information(NULL,"MyApp","Grid_Past is copied to Grid."); //ch1
	CountStatistics();
	IsEmpty=false;
	//1QMessageBox::information(NULL,"MyApp","Statistics Counted"); //ch1
	return true;
}

//tries agains probability to plant a flower on the x,y.
bool CEnvironment::MakeFlowerGrow(int x, int y)
{
	if (FlowerGrowingRatio==FLOWERGROWINGRATIO_BOTTOM) return false; //no flower can grow regardless of the percentage in the map
	int prob;
	if (FlowerGrowingRatio==FLOWERGROWINGRATIO_TOP) prob=100; //allways a flower grows
	else prob = (int)(CfgMng.FlowerGrowingRatioTable[FlowerGrowingRatio]*(Grid.GetCellGrowingProbability(x,y)));
	if ((Grid.GetCellContent(x,y) == NOTHING) //a beetle might have made a step into this cell
		&&(prob> RandInBound(100))) 
	{
		
		if (true == Grid.SetCellContentAndUpdate(FLOWER,x,y))
		{
			Statist.NumFlowers++;
			return true;
		}
	}
	return false;
}

bool CEnvironment::MakeFlowerDie(int x, int y)
{
	if (!IsFlowersDie) return false; //if dying of flowers is turned off, immediately return.

	int prob = PROB_FLOWER_DIE;
	if ((Grid.GetCellContent(x,y) == FLOWER) //a beetle might have made a step into this cell
		&&(prob> RandInBound(100))) 
	{
		
		if (true == Grid.SetCellContentAndUpdate(NOTHING,x,y))
		{
			Statist.NumFlowers--;
			return true;
		}
	}
	return false;
}

void CEnvironment::A_RotateLeft(CBeetle * beetle)//0,1,2,3 = West, North, East, South
{
	if (beetle->Direction>0) beetle->Direction--;
	else beetle->Direction=3;	
}

void CEnvironment::A_RotateRight(CBeetle * beetle)
{
	if (beetle->Direction<3) beetle->Direction++;
	else beetle->Direction=0;	
}

/**
* Public method:
* Desc: Realises the intention of one beetle to copulate.
* System dependence:
* Usage comments: Used as whole action from beetles brain, contains all checks of conditions.
* @return (Return values - meaning) : true - child(ren) created, false - no copulation
* @param name [descrip](Parameters - meaning):x,y - coordinates of the beetle, who intends to copulate. beetle - the beetle's reference.
* @throws name [descrip](Exceptions - meaning)
*/
bool CEnvironment::A_Copulate(int x, int y, CBeetle * beetle)
{
	CBeetle * beetle2 = NULL;
	int what = GetBeetleNeighborCell(x,y,beetle->Direction,'F', &beetle2);
	if (what != BEETLE) return false;

	//check my conditions
	if (beetle->IsExpectOnPartnerSatisfied(beetle2))
		//check his conditions
	{
		if (beetle2->IsExpectOnPartnerSatisfied(beetle))
		{
			//check if there is a space next to both of beetles( 4 possibile cells)
				int neigh[4][3];//1st column - what, 2nd - x, 3rd - y
				int x2,y2;			
				Grid.GetNeigborCellCoords(x,y,&x2,&y2,beetle->Direction);//get coords of beetle2
				int free_n=0; //number of free cell from the 4 of the neighborhood 

				Grid.GetNeigborCellCoords(x,y,&(neigh[0][1]),&(neigh[0][2]),RotateDirection(beetle->Direction,'L'));
				Grid.GetNeigborCellCoords(x,y,&(neigh[1][1]),&(neigh[1][2]),RotateDirection(beetle->Direction,'R'));
				Grid.GetNeigborCellCoords(x2,y2,&(neigh[2][1]),&(neigh[2][2]),RotateDirection(beetle->Direction,'L'));
				Grid.GetNeigborCellCoords(x2,y2,&(neigh[3][1]),&(neigh[3][2]),RotateDirection(beetle->Direction,'R'));
				
				//fprintf(stdout,("Neigh 0: "+QString::number(neigh[0][1])+" "+QString::number(neigh[0][2])+"\n").toAscii().data());
				//fprintf(stdout,("Neigh 1: "+QString::number(neigh[1][1])+" "+QString::number(neigh[1][2])+"\n").toAscii().data());
				//fprintf(stdout,("Neigh 2: "+QString::number(neigh[2][1])+" "+QString::number(neigh[2][2])+"\n").toAscii().data());
				//fprintf(stdout,("Neigh 3: "+QString::number(neigh[3][1])+" "+QString::number(neigh[3][2])+"\n").toAscii().data());

				//get content of neighbor cells in following step and count the number of free ones
				int I,J;
				for (I=0;I<4;I++)
				{
					neigh[I][0]=Grid.GetCellContent(neigh[I][1],neigh[I][2]);				
					if ((neigh[I][0]==FLOWER) ||(neigh[I][0]==NOTHING)) 
						free_n++;
				}
				
				//if there is no free cell in neighborhood, new beetle cannot be born
				if (free_n== 0 )return false;
				
				//take random one from free neighbors
				int chosenNeighI=-1;
				int rand_n = RandInBound (free_n);

				rand_n++;
				for (J=0;J<4;J++)
					if ((neigh[J][0]==FLOWER) ||(neigh[J][0]==NOTHING)) 
					{
						rand_n--;
						if (rand_n==0)
						{
							chosenNeighI=J;
							break;
						}
					}
				//J is now the index of the chosen neighbor
						
				CBeetle * beetle_child=beetle->CreateChild(beetle2);
				beetle->NumChildren++;
				beetle2->NumChildren++;
				
				//beetles consume energy on creation of a child
				beetle->ConsumeEnergy(beetle->InvInChild);
				beetle2->ConsumeEnergy(beetle2->InvInChild);
				assert(beetle->Energy >0);
				assert(beetle2->Energy >0);
				
				//if there is a flower in the target cell, it must be count out from statistics
				if (Grid.GetCellContent(neigh[chosenNeighI][1],neigh[chosenNeighI][2]) == FLOWER)
					Statist.NumFlowers--;

				//child_beetle is placed into environment
				if (Grid.SetCellContentAndUpdate(BEETLE,neigh[chosenNeighI][1],neigh[chosenNeighI][2],beetle_child))
					return true;
				else 
				{
					//fprintf(stdout,("Error: Child was not placed on neighbor"+ QString::number(chosenNeighI)+", "+QString::number(neigh[chosenNeighI][1])+" "+QString::number(neigh[chosenNeighI][2])+"\n").toAscii().data());
					delete(beetle_child);
					return false;
				}
		
		}
	}

	return false;
}

char CEnvironment::RotateDirection(char direction, char L_R_F)
{
	//there are 4 directions: W=0,N=1,E=2,S=3, so the "right" adds 1 and "left" subtracts 1
	if (L_R_F== 'L') { direction-=1; if (direction<0) direction=3; }
	if (L_R_F== 'R') { direction+=1;direction%=4;}
	//if (L_R_F== 'F') ;
	return direction;
}

/**
* Public method <br>
* Description: Counts Statistics of three kinds: NumFlower, NumBeetles and NumBirths (useful after loading of environment) and counts Sums of features of beetles(necessary before call to Statist->SaveAggrStatistics())<br>
* System dependence: no.<br>
* Usage comments: Two different cases of usage. View description part.<br>
*/

void CEnvironment::CountStatistics(void)
{
	int I,J,what;
	Statist.MakeEmpty();
	CBeetle * beetle=NULL;
	for(I=0;I<Grid.G_Width;I++)
			for(J=0;J<Grid.G_Height;J++)
			{
				what=Grid.GetCellContent(I,J,&beetle);
				if (what==BEETLE)
				{
					Statist.NumBeetles++;
					if (beetle->Age ==0 )Statist.NumBirths++;
					Statist.SumAge+=beetle->Age;
					Statist.SumEnergy+=beetle->Energy;
					Statist.SumHungryThreshold+=beetle->HungryThreshold;
					Statist.SumInvInChild+=beetle->InvInChild;
					Statist.SumLearnAbility+=beetle->LearnAbility;
					Statist.SumNumChildren+=beetle->NumChildren;
				}
				if (what==FLOWER) 
					Statist.NumFlowers++;
				
			}
	Statist.NumSpecies=Statist.FindSpeciesOfBeetles(&Grid);
}
/*
bool CEnvironment::CreateDefaultEnv(void)
{
	Time=0;

	Grid.SetDefaultGridShape() ;

	//Init Grid and Grid (with sizes, flowers probability, walls and beetles)	
	if (false == LoadEnv(DEFAULT_FILE_NAME ))
	{
		fprintf(stdout,"Loading of environment file %s_map.bmp was not successful.",DEFAULT_FILE_NAME);
		exit (EXIT_FAILURE);
	}
	return true;
}*/

char * CEnvironment::getMapFileName(char *fname)
{
	QString qFN(fname); 
	qFN+="_map.bmp";
	return qFN.toAscii().data();
}
char * CEnvironment::getEffFileName(char *fname)
{
	QString qFN(fname); 
	qFN+="_eff.bmp";
	return qFN.toAscii().data();
}
char * CEnvironment::getFlowersFileName(char *fname)
{
	QString  qFN(fname); 
	if (!qFN.contains(".")) 
		qFN+=".abl";
	return qFN.toAscii().data();
}
char * CEnvironment::getBeetlesFileName(char *fname)
{
	QString qFN(fname); 
	qFN+="_btl.txt";
	return qFN.toAscii().data();
}
char * CEnvironment::getTimeStatsFileName(char *fname)
{
	QString qFN(fname); 
	qFN+="_tst.csv";
	return qFN.toAscii().data();
}

bool CEnvironment::CleanEnv()
{
	IsEmpty=true;
	//1QMessageBox::information(NULL,"MyApp","Before cleaning of Grid");
	Grid.CleanGridAndBeetles();
	//1QMessageBox::information(NULL,"MyApp","Grid is cleaned");
	//Alert! I cannot clean beetles here! - they were already deleted in previous function. So I make shallow copy.
	//Grid_Past=Grid;
	//1QMessageBox::information(NULL,"MyApp","Grid past is cleaned");
	Time=0;
	//MapFilePath ="";
	//EffFilePath ="";
	//BeetlesFilePath ="";
	Statist.TotalCleanup();
	return true;
}

void CEnvironment::Make1Update()
{
	//fprintf(stdout,"In: Env::Make1Update");
	int I,J;
	for(I=0;I<Grid.G_Width;I++)
		for(J=0;J<Grid.G_Height;J++)
		{
			//if cell was not updated yet, I update it.
			if ((Grid.IsCellUpdated(I,J))==false)
			{
				if (Grid.GetCellContent(I,J)==BEETLE) MakeBeetleAction(I,J);
				else if (Grid.GetCellContent(I,J)==NOTHING) MakeFlowerGrow(I,J);
				else if (Grid.GetCellContent(I,J)==FLOWER) MakeFlowerDie(I,J);
				//I mark the cell as updated one
				Grid.SetCellUpdated(I,J); 
			}
			//if there is a wall, flower or something bad, do nothing
		}
}

