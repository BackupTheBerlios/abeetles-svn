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



CfgManager::CfgManager(void)
{
}

CfgManager::~CfgManager(void)
{
}



bool CfgManager::LoadCfgFile(char* cfg_filename)
{
	//proprietary solution
	CBeetle::EnergyMax_C=50;
	CBeetle::LastId=0;
	//later: LoadCfgFile():
	return true;
	/*
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
	return 0;*/
}

bool CfgManager::LoadGridShape(int * G_FirstIndex,int * G_Width, int * G_Height)
{
	*G_FirstIndex=1;
	*G_Width = 30;
	*G_Height =30;
	return true;
}





/**
* Protected method
* Desc:  Loads bmp file of environment and fills the grid's first layer according to it. Only environ without beetles.
* System dependence: windows specific (windows.h)
* Usage comments: 
* @return (Return values - meaning) :
* @param name [ descrip](Parameters - meaning):
* @throws name [descrip](Exceptions - meaning)
*/
//
bool CfgManager::LoadMapFromBmp(CGrid * grid, char * filename)
{
//1. Read the bmp file
	QImage * img = new QImage (filename);
	QMessageBox::information(NULL,"MyApp","Bmp map,"+QString::number(img->width())+", "+QString::number(img->height()));
	if ((img==NULL)||(img->width()< grid->G_Width) ||( img->height()< grid->G_Height))
	{
		QMessageBox::information(NULL,"MyApp","No bmp map or bmp map too small - expected: "+QString::number( grid->G_Width)+", "+QString::number(grid->G_Height));
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
			
			color = img->pixel(J,I);
			if (QColor::fromRgb(color) == CFG_CLR_WALL)
				grid->SetCellContent_Init(WALL,I,J);			
			else 
			{
				grid->SetCellContent_Init(NOTHING,I,J);
				grid->SetCellGrowingProbability(0,I,J);
				if ((qRed(color)==0)&&(qBlue(color)==0)&&(qGreen (color)>= CFG_CLR_FLOWER_BOTTOM) && (qGreen (color)<= CFG_CLR_FLOWER_TOP))
					grid->SetCellGrowingProbability(FlowerProbabilityFromColor(qGreen (color)),I,J);
			}
		}
	}

	return true;
}

int CfgManager::FlowerProbabilityFromColor(int greenNum)
{	
	int pom=greenNum-CFG_CLR_FLOWER_BOTTOM;
	return (((pom*100)/(CFG_CLR_FLOWER_TOP - CFG_CLR_FLOWER_BOTTOM)));
}

bool CfgManager::SaveBeetles(CGrid * grid,char * filename)
{
	FILE * btlFile;
	CBeetle * beetle;
	int err;
	int I,J,K,L,M,N;	
	
	if (NULL==(btlFile= fopen(filename,"w"))) 
	{
		printf("%d",errno);
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
bool CfgManager::LoadBeetles(CGrid * grid, char * filename)
{
	CBeetle * beetle=NULL;

	FILE * btlFile;
	int err;
	if (NULL==(btlFile= fopen(filename,"r"))) 
	{
		printf("%d",errno);
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
		beetle=new CBeetle();
							
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
		
		if (false==grid->SetCellContent(BEETLE,x,y,beetle))
		{
			printf("Beetle %d could not be placed into Grid([%d,%d] is out of grid or there is a wall).\n",I,x,y);
			delete beetle;
		}
		J++;
	}
	fclose(btlFile);

	if (ok==false)
	{
		printf("File %s was not read correctly.\n",btlFile);
		return false;
	}

	return true;
}


bool CfgManager::LoadEnergyFromFlowerFromBmp(int EFF_Age [EFF_BMP_X], char * filename)
{
//1. Read the bmp file
	QImage * img = new QImage (filename);
	//QMessageBox::information(NULL,"MyApp","Bmp map,"+QString::number(img->width())+", "+QString::number(img->height()));
	if ((img==NULL)||(img->width()< EFF_BMP_X) ||( img->height()< EFF_BMP_Y))
	{
		QMessageBox::information(NULL,"MyApp","No bmp map or bmp map too small - expected: width - "+QString::number(EFF_BMP_X)+", height - "+ QString::number(EFF_BMP_Y));
		return false;
	}

//2.Fill EnergyFromFlower array with information from the image
	QRgb color;	
	int I,J;

	//for the sake of the printf in lines, this reads in the direction of columns from bottom up.
	for (I=0;I<EFF_BMP_X;I++)	
	{	
		for (J=EFF_BMP_Y-1;J>=0;J--)
		{
			if (!(img->valid(I,J))) 
			{
				//QMessageBox::information(NULL,"MyApp","Not valid I,J");
				continue; //if the I,J is not valid withing img
			}
			color = img->pixel(I,J); 
			if (QColor::fromRgb(color) == QColor("black"))
			{
				EFF_Age[I]=EFF_BMP_Y - J-1;
				//QMessageBox::information(NULL,"MyApp","EFF: "+QString::number(EFF_BMP_Y - J-1));
				continue;
			}
		}
	}


	return true;
}



