#include "StdAfx.h"
#include "CfgManager.h"
#include "defines.h"
#include "Beetle.h"
#include "Environment.h"
#include "Grid.h"
#include <string.h>
//#include <windows.h>
//#include <direct.h>
//#include <winuser.h>
#include <QtGui>
#include <QList>
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include "COneRun.h"


extern bool IsScript;

CfgManager::CfgManager(void)
{
	FlowerGrowingRatioTable[0]=-1;
	FlowerGrowingRatioTable[1]=0.1; 
	FlowerGrowingRatioTable[2]=0.4; 
	FlowerGrowingRatioTable[3]=0.7;
	FlowerGrowingRatioTable[4]=1;
	FlowerGrowingRatioTable[5]=1.5;
	FlowerGrowingRatioTable[6]=2;
	FlowerGrowingRatioTable[7]=5;
	FlowerGrowingRatioTable[8]=-2;
}

CfgManager::~CfgManager(void)
{
}


/*
bool CfgManager::LoadCfgFile(char* cfg_filename)
{
	//proprietary solution
	CBeetle::EnergyMax_C=50;
	CBeetle::LastId=0;
	//later: LoadCfgFile():
	return true;
	
	char VarName[25];
	int VarValue=0;
	int err;
	int I;
	FILE * pConfigFile;
	if ((err= fopen(&pConfigFile,cfg_filename,"r"))!=0) 
		return err;
	for (I=0;I<NUMOPTVARIABLES;I++)
	{
		fscanf(pConfigFile,"%s=%d\n",VarName,&VarValue);
		if ( strcmp(VarName,"EnergyMax_C") == 0) CBeetle::EnergyMax_C=VarValue;
		else CBeetle::EnergyMax_C=50;

	}
	return 0;
}*/






/**
* Public method
* Desc:  Loads bmp file of environment sets width and height and fills the grid's first layer according to it. Only environ without beetles.<br>
* System dependence: OS:no, lib: qt <br>
* Usage comments: 
* @return (true - if loaded, false if not successful. The content of the Grid stays then unchanged.)<br>
* @param grid [Reference to the grid object]<br>
* @param filename [Complete name of the file of the grid. Can have any extension. Checked only for bmp.]<br>
*/
//
bool CfgManager::LoadMapFromBmp(CGrid * grid, QString filename, int * numFreeCells )
{
	return LoadMapFromBmp(grid, filename.toAscii().data(),numFreeCells);
}
bool CfgManager::LoadMapFromBmp(CGrid * grid, char * filename, int * numFreeCells)
{
	int pom=0;

//1. Read the bmp file
	QImage * img = new QImage (filename);
	//1QMessageBox::information(NULL,"MyApp","Bmp map,"+QString::number(img->width())+", "+QString::number(img->height()));
	if (img==NULL)
	{
		if (IsScript)fprintf(stdout, ("No file "+QString::fromAscii(filename)+" found.\n").toAscii().data());
		else QMessageBox::information(NULL,"MyApp","No file "+QString::fromAscii(filename)+" found."); 
		return false;
	}
	if ((img->width()<= G_WIDTH_MAX) && (img->width()>= G_WIDTH_MIN) && (img->height()<= G_HEIGHT_MAX)&&(img->height()>= G_HEIGHT_MIN))
	{
		grid->G_Width = img->width();
		grid->G_Height = img->height();
	}
	else
	{
		if (IsScript) fprintf(stdout, ("Bitmap "+QString::fromAscii(filename)+" has not correct size. Correct size is from "+QString::number(G_WIDTH_MIN)+"x"+QString::number(G_HEIGHT_MIN)+" to "+QString::number(G_WIDTH_MAX)+"x"+QString::number(G_HEIGHT_MAX)+".\n").toAscii().data());
		QMessageBox::information(NULL,"MyApp","Bitmap "+QString::fromAscii(filename)+" has not correct size. Correct size is from "+QString::number(G_WIDTH_MIN)+"x"+QString::number(G_HEIGHT_MIN)+" to "+QString::number(G_WIDTH_MAX)+"x"+QString::number(G_HEIGHT_MAX)+".");
		return false;
	}
//2.Fill grid with information from the image
	
	QRgb color;	
	int I,J;

	//for the sake of the printf in lines, this reads in the direction of lines, not columns
	for (J=0;J< (grid->G_Height);J++)	
	{	
		for (I=0;I<(grid->G_Width);I++)
		{
			if (!(img->valid(I,J))) 
			{
				//QMessageBox::information(NULL,"MyApp","Not valid I,J");
				continue; //if the I,J is not valid withing img
			}
			
			color = img->pixel(I,J);
			if (QColor::fromRgb(color) == CFG_CLR_WALL)
				grid->SetCellContent_Init(WALL,I,J);			
			else 
			{
				grid->SetCellContent_Init(NOTHING,I,J);
				pom++;
				grid->SetCellGrowingProbability(0,I,J);
				if ((qRed(color)==0)&&(qBlue(color)==0)&&(qGreen (color)>= CFG_CLR_FLOWER_BOTTOM) && (qGreen (color)<= CFG_CLR_FLOWER_TOP))
					grid->SetCellGrowingProbability(FlowerProbabilityFromColor(qGreen (color)),I,J);
			}
		}
		
	}
	//fprintf(stdout,QString::number(pom).toAscii().data());
	*numFreeCells=pom;
	return true;
}

bool CfgManager::SaveEffToBmp(QString filename)
{
	return SaveEffToBmp(filename.toAscii().data());
}

bool CfgManager::SaveEffToBmp(char * filename)
{
	return CBeetle::EffImg.save(filename,"bmp");
}

bool CfgManager::SaveMapToBmp(CGrid * grid, QString filename)
{
	return SaveMapToBmp(grid,filename.toAscii().data());
}

bool CfgManager::SaveMapToBmp(CGrid * grid, char * filename)
{
	QImage img(grid->G_Width,grid->G_Height,QImage::Format_RGB32);
	int I,J;

	for (I=0;I<grid->G_Width;I++)
		for (J=0;J<grid->G_Height;J++)
		{
			if (grid->GetCellContent(I,J) == WALL) 
				img.setPixel(I,J,(CFG_CLR_WALL).rgb()); //qRgb(189, 149, 39)
			else 
				img.setPixel(I,J,qRgb(	0,
										ColorFromFlowerProbability(grid->GetCellGrowingProbability(I,J)),
										0));
		}
	return img.save(filename,"bmp");
}



int CfgManager::FlowerProbabilityFromColor(int greenNum)
{	
	int pom=greenNum-CFG_CLR_FLOWER_BOTTOM;
	return (((pom*100)/(CFG_CLR_FLOWER_TOP - CFG_CLR_FLOWER_BOTTOM)));
}

/**
* Public method <br>
* Description: Inverse function to {@link #FlowerProbabilityFromColor}<br>
* System dependence: no<br>
* Usage comments:<br>
* @return (Integer value is number of green 0-255 in RGB system) 
* @param prob [ Probability of growth of flower, 0-100.]
*/
int CfgManager::ColorFromFlowerProbability(int prob)
{
	return (prob*(CFG_CLR_FLOWER_TOP - CFG_CLR_FLOWER_BOTTOM))/100 + CFG_CLR_FLOWER_BOTTOM;
}


bool CfgManager::SaveBeetles(CGrid * grid,QString filename)
{
	return SaveBeetles(grid,filename.toAscii().data());
}
bool CfgManager::SaveBeetles(CGrid * grid,char * filename)
{
	FILE * btlFile;
	CBeetle * beetle;
	//int err;
	int I,J,K,L,M,N;	
	

	if (NULL==(btlFile= fopen(filename,"w"))) 
	{
		if(IsScript) fprintf(stdout,("Saving of file " + QString::fromAscii(filename) + " was not successful.").toAscii().data());
		else QMessageBox::information(NULL,"Error","Saving of file " + QString::fromAscii(filename) + " was not successful.");
		return false;
	}

	for (J=0;J<grid->G_Height;J++)
		for (I=0;I<grid->G_Width;I++)
			if (grid->GetCellContent(I,J,&beetle)== BEETLE)
			{
				fprintf(btlFile," ---------- \n");
				fprintf(btlFile,"Id=%d;\n",beetle->Id);
				fprintf(btlFile,"Age=%d;\n",beetle->Age);
				fprintf(btlFile,"Brain=%d",beetle->Brain [0][0][0][0]);
				for (M=0;M<BRAIN_D1;M++)
					for(N=0;N<BRAIN_D2;N++)
						for(K=0;K<BRAIN_D3;K++)
							for(L=0;L<BRAIN_D4;L++)
								if (!((M==0)&&(N==0)&&(K==0)&&(L==0)))
									fprintf(btlFile,",%d",beetle->Brain [M][N][K][L]);
				fprintf(btlFile,";\n");
				fprintf(btlFile,"Direction=%d;\n",beetle->Direction);
				fprintf(btlFile,"Energy=%d;\n",beetle->Energy);
				fprintf(btlFile,"ExpectOnPartner=%d",beetle->ExpectOnPartner[0]);
				for (M=1;M<EXPECT_ON_PARTNER_D;M++)
						fprintf(btlFile,",%d",beetle->ExpectOnPartner[M]);
				fprintf(btlFile,";\n");
				fprintf(btlFile,"HungryThreshold=%d;\n",beetle->HungryThreshold);
				fprintf(btlFile,"InvInChild=%d;\n",beetle->InvInChild);
				fprintf(btlFile,"LearnAbility=%d;\n",beetle->LearnAbility);
				fprintf(btlFile,"NumChildren=%d;\n",beetle->NumChildren);
				fprintf(btlFile,"x=%d;\n",I);
				fprintf(btlFile,"y=%d;\n",J);

			}
	fprintf(btlFile," ---------- \n");
	
	fclose(btlFile);
	return true;
}
bool CfgManager::LoadBeetles(CGrid * grid, QString filename)
{
	return LoadBeetles(grid,filename.toAscii().data());
}
bool CfgManager::LoadBeetles(CGrid * grid, char * filename)
{
	CBeetle * beetle=NULL;

	FILE * btlFile;
	//int err;
	if (! QFile::exists(QString::fromAscii(filename)))
	{
		if(IsScript) fprintf(stdout,("File "+QString::fromAscii(filename)+" does not exist.").toAscii().data());
		else QMessageBox::information(NULL,"Error","File " + QString::fromAscii(filename) + " does not exist.");
		return false;

	}
	if (NULL==(btlFile= fopen(filename,"r"))) 
	{
		if(IsScript) fprintf(stdout,("Loading of file of beetles "+QString::fromAscii(filename)+" was not successful.").toAscii().data());
		else QMessageBox::information(NULL,"MyApp","Loading of file of beetles "+QString::fromAscii(filename)+" was not successful."); 
		return false;
	}

	//reading of btlFile using fscanf function
		/*remarks:
			1.One white-space character in the format matches any number (including 0) and combination of white-space characters in the input.
		*/
	int I,J = 0;
	int x,y;
	int VarValue=0;
	//char  VarName[20];
	bool ok=true;

	while (!feof(btlFile))
	{
		beetle=new CBeetle();CBeetle::AlocBeetles++;
							
		fscanf(btlFile," ---------- ");
		if (0==fscanf(btlFile," Id = %d ; ",&VarValue)) {ok=false;break;};
				beetle->Id=VarValue;
		if (0==fscanf(btlFile," Age = %d ; ",&VarValue)) {ok=false;break;};
		beetle->Age=VarValue;
		fscanf(btlFile," Brain = ");
		for (I=0;I<127;I++)
		{
		  if (0==fscanf(btlFile," %d ,",&VarValue)) {ok=false;break;};
		  beetle->SetBrain(I,VarValue);
		}
		if (0==fscanf(btlFile," %d ; ",&VarValue)) {ok=false;break;};
		beetle->SetBrain(127,VarValue);
		if (0==fscanf(btlFile," Direction = %d ; ",&VarValue)) {ok=false;break;};
		beetle->Direction=VarValue;
		if (0==fscanf(btlFile," Energy = %d ; ",&VarValue)) {ok=false;break;};
		beetle->Energy=VarValue;
		fscanf(btlFile," ExpectOnPartner = ");
		for (I=0;I<EXPECT_ON_PARTNER_D-1;I++)
		{
		  if (0==fscanf(btlFile," %d , ",&VarValue)) {ok=false;break;};
		  beetle->ExpectOnPartner[I]=VarValue;		  
		}
		if (0==fscanf(btlFile," %d ; ",&VarValue)) {ok=false;break;};
		beetle->ExpectOnPartner[EXPECT_ON_PARTNER_D-1]=VarValue;		
		if (0==fscanf(btlFile," HungryThreshold = %d ; ",&VarValue)) {ok=false;break;};
		beetle->HungryThreshold=VarValue;
		if (0==fscanf(btlFile," InvInChild = %d ; ",&VarValue)) {ok=false;break;};
		beetle->InvInChild=VarValue;
		if (0==fscanf(btlFile," LearnAbility = %d ; ",&VarValue)) {ok=false;break;};
		beetle->LearnAbility=VarValue;
		if (0==fscanf(btlFile," NumChildren = %d ; ",&VarValue)) {ok=false;break;};
		beetle->NumChildren=VarValue;
		if (0==fscanf(btlFile," x = %d ; ",&x)) {ok=false;break;};		
		if (0==fscanf(btlFile," y = %d ; ",&y)) {ok=false;break;};		
		fscanf(btlFile," ---------- ");
		
		if (false==grid->SetCellContentNotUpdate(BEETLE,x,y,beetle))
		{
			if(IsScript) fprintf(stdout,("Beetle "+QString::number(I)+" could not be placed into Grid(["+QString::number(x)+","+QString::number(y)+"] is out of grid or there is a wall).\n").toAscii().data());
			else QMessageBox::information(NULL,"MyApp","Beetle "+QString::number(I)+" could not be placed into Grid(["+QString::number(x)+","+QString::number(y)+"] is out of grid or there is a wall).\n"); 

			delete beetle;CBeetle::CBeetle::AlocBeetles--;
		}
		J++;
	}
	fclose(btlFile);

	if (ok==false)
	{
		if(IsScript) fprintf(stdout,("File "+QString::fromAscii(filename)+" was not read correctly.\n").toAscii().data());
		else QMessageBox::information(NULL,"Error","File "+QString::fromAscii(filename)+" was not read correctly.\n"); 

		return false;
	}

	return true;
}

bool CfgManager::LoadFlwAndOpt(CGrid * grid, int *time, bool *learningOn, 
	int* flowerGrowingRatio, int * mutationProb, int *stepCost, int *rotCost, int *copulCost, 
	int *waitCost, QString filename)
{
	return LoadFlwAndOpt(grid,  time,  learningOn, 
	 flowerGrowingRatio, mutationProb, stepCost,  rotCost, copulCost, 
	waitCost,  filename.toAscii().data());

}
//bool CfgManager::LoadFlwAndOpt(CGrid * grid, char * filename)
bool CfgManager::LoadFlwAndOpt(CGrid * grid,int *time, bool *learningOn, 
	int* flowerGrowingRatio, int * mutationProb, int *stepCost, int *rotCost, int *copulCost, 
	int *waitCost,char * filename)
{
	int x,y;
	QFile flwFile (filename);
	 if (!flwFile.open(QIODevice::ReadOnly | QIODevice::Text))
	 {
		if(IsScript) fprintf(stdout,("Loading of file of flowers "+QString::fromAscii(filename)+" was not successful.\n").toAscii().data());
		else QMessageBox::information(NULL,"Error","Loading of file of flowers "+QString::fromAscii(filename)+" was not successful.\n"); 

         return false;
	 }
	
		
	int I=-1;
	while (!flwFile.atEnd())
	{
		QByteArray line = flwFile.readLine();
		line.truncate(line.indexOf(";"));
		I++;
		if(I==0) {*time=line.toInt();/*fprintf(stdout,("\n"+QString::number(*time)).toAscii().data());*/continue;}
		if(I==1) {*learningOn=line.toInt();continue;}
		if(I==2) {*flowerGrowingRatio=line.toInt();continue;}
		if(I==3) {*mutationProb=line.toInt();continue;}
		if(I==4) {*stepCost=line.toInt();continue;}
		if(I==5) {*rotCost=line.toInt();continue;}
		if(I==6) {*copulCost=line.toInt();continue;}
		if(I==7) {*waitCost=line.toInt();continue;}
		
		x=(line.left(line.indexOf(","))).toInt(); 
		y=(line.right(line.size()-line.indexOf(",")-1)).toInt(); 
		grid->SetCellContentNotUpdate(FLOWER,x,y);
	}
	return true;
}

bool CfgManager::SaveFlwAndOpt(CGrid * grid,int time, bool learningOn, 
	int flowerGrowingRatio, int mutationProb, int stepCost, int rotCost, int copulCost, 
	int waitCost,QString filename)
{
	return SaveFlwAndOpt(grid, time,  learningOn, 
	 flowerGrowingRatio, mutationProb, stepCost,  rotCost, copulCost, 
	waitCost,filename.toAscii().data());
}
//bool CfgManager::SaveFlwAndOpt(CGrid * grid,char * filename)
bool CfgManager::SaveFlwAndOpt(CGrid * grid,int time, bool learningOn, 
	int flowerGrowingRatio, int mutationProb, int stepCost, int rotCost, int copulCost, 
	int waitCost, char * filename)
{
	int I,J;
	QFile flwFile (filename);
	if (!flwFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		if(IsScript) fprintf(stdout,("Saving of file "+QString::fromAscii(filename)+" was not successful.\n").toAscii().data());
		else QMessageBox::information(NULL,"Error","Saving of file "+QString::fromAscii(filename)+" was not successful.\n"); 

         return false;
	}
	
	QTextStream out(&flwFile);
	out << time<<";"<< "\n"; 
	out << learningOn<<";"<< "\n"; 
	out << flowerGrowingRatio<<";"<< "\n"; 
	out << mutationProb<<";"<< "\n"; 
	out << stepCost<<";"<< "\n"; 
	out << rotCost<<";"<< "\n"; 
	out << copulCost<<";"<< "\n"; 
	out << waitCost<<";"<< "\n"; 

	

	for (I=0;I<grid->G_Width;I++)
		for (J=0;J<grid->G_Height;J++)
			if (grid->GetCellContent(I,J) == FLOWER)
				out << I<<","<<J<<";"<< "\n"; 

	return true;
}


QImage CfgManager::LoadEffFromBmp(int EFF_Age [EFF_BMP_X], QString filename) //, QImage img)
{
		//QMessageBox::information(NULL,"MyApp","4");

	return LoadEffFromBmp(EFF_Age , filename.toAscii().data()) ;
}
QImage CfgManager::LoadEffFromBmp(int EFF_Age [EFF_BMP_X], char * filename) //, QImage img)
{
	//QMessageBox::information(NULL,"MyApp","3");
//1. Read the bmp file
	QImage img (filename);
	//img.load(filename);
	int width; int height;
	
	//QMessageBox::information(NULL,"MyApp","Bmp map,"+QString::number(img.width())+", "+QString::number(img.height()));
	if (img.isNull())
	{
		if(IsScript) fprintf(stdout,("No eff bmp, expected bmp: width - "+QString::number(EFF_BMP_X)+", height - "+ QString::number(EFF_BMP_Y)+"\n").toAscii().data());
		else QMessageBox::information(NULL,"Error","No eff bmp, expected bmp: width - "+QString::number(EFF_BMP_X)+", height - "+ QString::number(EFF_BMP_Y)); 

		return QImage();
	}
	img.width()< EFF_BMP_X ? width=img.width() : width=EFF_BMP_X ;
	img.height()< EFF_BMP_Y ? height=img.height() : height=EFF_BMP_Y;

//2.Fill EnergyFromFlower array with information from the image
	QRgb color;	
	int I,J;

	//for the sake of the printf in lines, this reads in the direction of columns from bottom up.
	for (I=0;I<width;I++)	
	{	
		for (J=height-1;J>=0;J--)
		{
			if (!(img.valid(I,J))) 
			{
				//QMessageBox::information(NULL,"MyApp","Not valid I,J");
				continue; //if the I,J is not valid withing img
			}
			color = img.pixel(I,J); 
			if (QColor::fromRgb(color) == QColor("black"))
			{
				EFF_Age[I]=height - J-1;
				//QMessageBox::information(NULL,"MyApp","EFF: "+QString::number(EFF_BMP_Y - J-1));
				continue;
			}
		}
	}
	 
	
	//CBeetle::EffImg=img;
	//QMessageBox::information(NULL,"MyApp","Is eff img");
	//image = img;
	

	return img;
}

QList<COneRun*> CfgManager::LoadScript(QString scriptFN)
{
	QString err;
	QList <COneRun *>list;
	COneRun* oneRun = NULL;
	QFile scrFile (scriptFN);
	if (!scrFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		if(IsScript) fprintf(stdout,("Opening of file "+scriptFN+" was not successful.\n").toAscii().data());
		else QMessageBox::information(NULL,"Error","Opening of file "+scriptFN+" was not successful."); 

		return list;
	}

	QByteArray line;
	QByteArray pom;
	int i;

	int timeArray[50]; 

	while (!scrFile.atEnd()) 
	{
         line = scrFile.readLine();
         if (line.startsWith("run"))
		 {
			 //previous oneRun is added to QList
			 if (oneRun) 
			 {
				 if (!err.isNull()) 
				 {
					 fprintf(stdout,("Errors parsing script, run "+oneRun->DirName+" is not correct: \n"+err.trimmed()+"\n").toAscii().data());
					 delete(oneRun);
				 }
				 else
					list.append(oneRun);
				 oneRun=NULL;
			 }

			 if (!oneRun) oneRun= new COneRun();
			 if (false==oneRun->setDirName(line.right(line.size()-line.indexOf("=")-1).trimmed()))
				 err+="Directory "+line.right(line.size()-line.indexOf("=")-1).trimmed()+" was not created.\n";
		 }
		 //if no oneRun exists, I search for next line beginning with "run"
		 if (!oneRun) continue;

		 if (line.startsWith("map")) //map=mapa.bmp
			 if ( false == oneRun->setMapFN(line.right(line.size()-line.indexOf("=")-1).trimmed()) )
				err+=("File of map "+line.right(line.size()-line.indexOf("=")-1).trimmed()+" not found.\n");

		 if (line.startsWith("eff"))//eff=energyfce.bmp
			  if (false==oneRun->setEffFN(line.right(line.size()-line.indexOf("=")-1).trimmed()))
				  err+=("File of energy from flowers "+line.right(line.size()-line.indexOf("=")-1).trimmed()+" not found.\n");

		 if (line.startsWith("beetles"))//beetles=random,200,50
		 {
			 pom = line.right(line.size()-line.indexOf("=")-1).trimmed();
			 
			 if (! oneRun->setBeetlesFN(pom)) // is it an existing filename?
			 {
				 if (pom.startsWith("random"))	//or is it description of random start?
				 {
					 pom = pom.right(pom.size()-pom.indexOf(",")-1).trimmed();
					 oneRun->setRandom(pom.left(pom.indexOf(",")).trimmed().toInt(),pom.right(pom.size()-pom.indexOf(",")-1).trimmed().toInt());
				 }
				 else
				 {
					 //chyba, nepodarilo se precist
				 }
			 }
		 }
		
		 if(line.startsWith("mutationprob"))
		 {
			pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			oneRun->setMutationProb(pom.toInt());
		 }
		 if (line.startsWith("costs")) //costs=1,1,2,2
		 {
			 pom = line.right(line.size()-line.indexOf("=")-1).trimmed();
			 QByteArray poms[3];
			 for (i=0;i<3;i++) 
			 {
				 poms[i]=pom.left(pom.indexOf(",")).trimmed();
				 pom=pom.right(pom.size()-pom.indexOf(",")-1).trimmed();
			 }
			 oneRun->setCostsOfActions(poms[0].toInt(),poms[1].toInt(),poms[2].toInt(), pom.toInt());
		 }

		 if (line.startsWith("endtime"))
		 {
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setEndTime(pom.toInt());
		 }
		 if (line.startsWith("nolearning"))
		 {			 
			 oneRun->setLearningOn(false);
		 }
		 if (line.startsWith("nosteponflower"))
		 {			 
			 oneRun->setIsStepOnFlower(false);
		 }
		if (line.startsWith("noflowersdie"))
		{			 
		 oneRun->setIsFlowersDie(false);
		}
		if (line.startsWith("randomexpectations"))
		{			 
		 oneRun->setIsNoExpectations(false);
		}
		 if (line.startsWith("aggrstatfn"))
		 {
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setAggrStatFN(pom);
		 }
		if (line.startsWith("histstatfn"))
		 {
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setHistStatFN(pom);
		 }
		if (line.startsWith("timestatfn"))
		 {
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setTimeStatFN(pom);
		 }
		if (line.startsWith("envfn"))
		 {
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setEnvFN(pom);
		 }
		if(line.startsWith("savetimeaggrreg"))
		{
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setSaveTimeAggrReg(pom.toInt());

		}
		if(line.startsWith("savetimehistreg"))
		{
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setSaveTimeHistReg(pom.toInt());
		}
		if(line.startsWith("savetimeenvreg"))
		{
			 pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			 oneRun->setSaveTimeEnvReg(pom.toInt());
		}
		if(line.startsWith("savetimesaggr"))
		{
			pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			i=0;
			timeArray[i]=-1;
			while (pom.contains(","))
			{
				timeArray[i]=pom.left(pom.indexOf(",")).trimmed().toInt();
				pom=pom.right(pom.size()-pom.indexOf(",")-1).trimmed();
				i++;
				timeArray[i]=-1;
				if (i==49) break; //so as not to overflow the size of the array
			}
			if(! pom.trimmed().isNull())
			{
				timeArray[i]=pom.trimmed().toInt();
				timeArray[i+1]=-1;
			}
			oneRun->setSaveTimesAggr(timeArray);
		}
		if(line.startsWith("savetimeshist"))
		{
			pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			i=0;
			timeArray[i]=-1;
			while (pom.contains(","))
			{
				timeArray[i]=pom.left(pom.indexOf(",")).trimmed().toInt();
				pom=pom.right(pom.size()-pom.indexOf(",")-1).trimmed();
				i++;
				timeArray[i]=-1;
				if (i==49) break; //so as not to overflow the size of the array
			}
			if(! pom.trimmed().isNull())
			{
				timeArray[i]=pom.trimmed().toInt();
				timeArray[i+1]=-1;
			}
			oneRun->setSaveTimesHist(timeArray);
		}
		if(line.startsWith("savetimesenv"))
		{
			pom = (line.right(line.size()-line.indexOf("=")-1).trimmed());
			i=0;
			timeArray[i]=-1;
			while (pom.contains(","))
			{
				timeArray[i]=pom.left(pom.indexOf(",")).trimmed().toInt();
				pom=pom.right(pom.size()-pom.indexOf(",")-1).trimmed();
				i++;
				timeArray[i]=-1;
				if (i==49) break; //so as not to overflow the size of the array
			}
			if(! pom.trimmed().isNull())
			{
				timeArray[i]=pom.trimmed().toInt();
				timeArray[i+1]=-1;
			}
			oneRun->setSaveTimesEnv(timeArray);
		}

     }
		
	 if (oneRun) 
	 {
		 if (!err.isNull()) 
		 {
			 fprintf(stdout,("Errors parsing script, run "+oneRun->DirName+" is not correct: \n"+err.trimmed()+"\n").toAscii().data());
			 delete(oneRun);
		 }
		 else
			list.append(oneRun);
		 oneRun=NULL;
		 
	 }

	
	 return list;
}


