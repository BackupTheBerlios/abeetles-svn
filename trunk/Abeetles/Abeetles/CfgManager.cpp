#include "StdAfx.h"
#include "CfgManager.h"
#include "defines.h"
#include "Beetle.h"
#include "Environment.h"
#include "Grid.h"
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <winuser.h>




CfgManager::CfgManager(void)
{
}

CfgManager::~CfgManager(void)
{
}


// reads init content of environment from files Env_cfg.bmp and AdamBeetles.txt
//functionality removed to Env.LoadEnv()
/*
bool CfgManager::GetGridInit(CGrid * grid)
{
	int FI,W,H;
	if (false==LoadGridShape(&FI,&W,&H)) return false;
	if (false==Grid->SetGridShape(FI,W,H)) return false;

	//First part - init environment: Loads environment without beetles
	LoadMapFromBmp(grid,MAP_BMP_FILE);


	//Second part - load beetles and add them to half finished environment
	
	LoadBeetles(grid,"Beetle.txt");

	return true;
}
*/

int CfgManager::LoadCfgFile(char* cfg_filename)
{
	//proprietary solution
	CBeetle::EnergyMax_C=50;
	//later: LoadCfgFile():
	return true;
	/*
	char VarName[25];
	int VarValue=0;
	errno_t err;
	int I;
	FILE * pConfigFile;
	if ((err= fopen_s(&pConfigFile,cfg_filename,"r"))!=0) 
		return err;
	for (I=0;I<NUMOPTVARIABLES;I++)
	{
		fscanf_s(pConfigFile,"%s=%d\n",VarName,&VarValue);
		if ( strcmp(VarName,"EnergyMax_C") == 0) CBeetle::EnergyMax_C=VarValue;
		else CBeetle::EnergyMax_C=50;

	}
	return 0;*/
}

bool CfgManager::LoadGridShape(int * G_FirstIndex,int * G_Width, int * G_Height)
{
	*G_FirstIndex=1;
	*G_Width = 15;
	*G_Height =15;
	return true;
}



/*
//functionality removed to LoadBeetles()
bool CfgManager::LoadNextBeetle(FILE * btlFile, //file opened for reading
								CBeetle* beetle)
{
	char  VarName[20];
	int VarValue=0;
	int I;
		
	//reading of btlFile using fscanf_s function
	//remarks:
	//	1.One white-space character in the format matches any number (including 0) and combination of white-space characters in the input.
	//
		fscanf_s(btlFile," ---------- ");
    fscanf_s(btlFile," Age = %d ; ",&VarValue);
    beetle->Age=VarValue;
    fscanf_s(btlFile," Brain = ");
    for (I=0;I<127;I++)
    {
      fscanf_s(btlFile," %d ,",&VarValue);
      beetle->SetBrain(I,VarValue);
    }
    fscanf_s(btlFile," %d ; ",&VarValue);
    beetle->SetBrain(127,VarValue);
    fscanf_s(btlFile," Direction = %d ; ",&VarValue);
    beetle->Direction=VarValue;
    fscanf_s(btlFile," Energy = %d ; ",&VarValue);
    beetle->Energy=VarValue;
    fscanf_s(btlFile," ExpectOnPartner = ");
    for (I=0;I<4;I++)
    {
      fscanf_s(btlFile," %d , ",&VarValue);
      beetle->ExpectOnPartner[I][0]=VarValue;
      fscanf_s(btlFile," %d ; ",&VarValue);
      beetle->ExpectOnPartner[I][1]=VarValue;
    }
    fscanf_s(btlFile," HungryThreshold = %d ; ",&VarValue);
    beetle->HungryThreshold=VarValue;
    fscanf_s(btlFile," InvInChild = %d ; ",&VarValue);
    beetle->InvInChild=VarValue;
    fscanf_s(btlFile," LearnAbility = %d ; ",&VarValue);
    beetle->LearnAbility=VarValue;
	fscanf_s(btlFile," x = %d ; ",&VarValue);
	fscanf_s(btlFile," y = %d ; ",&VarValue);

	fscanf_s(btlFile," ---------- ");
	
	return true;
}
*/

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
bool CfgManager::LoadMapFromBmp(CGrid * Grid, wchar_t * filename)
{
//1. Read the bmp file
	//In windows any image must be connected with a device context, so as to read individual pixels
	HDC hDC = CreateCompatibleDC(0);
	if (hDC==0) printf("chyba DC\n"); //chyba

	
	//wchar_t * filename= MAP_BMP_FILE ;// function LoadImage needs a unicode string!
	printf("%s\n", filename);

	HBITMAP hBitmap= (HBITMAP) LoadImage(NULL,//HINSTANCE hinst
								filename,	//file name - as UNICODE string !!!!
								IMAGE_BITMAP,	//type of loaded result
								Grid->G_Width, 
								Grid->G_Height,
								LR_LOADFROMFILE
							);
	
	if (hBitmap == 0) 
	{
		printf("Chyba hBitmap load env_cfg\n");
		DWORD Err=GetLastError();
		//char Buffer [256];
		LPTSTR lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,NULL,Err,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0, NULL);
		printf("%s\n",lpMsgBuf);
		LocalFree(lpMsgBuf);
		return false;
	}

	//Ataching of image with DeviceContext
	SelectObject ( hDC, hBitmap );

	//TODO: check, if picture is at least as big as the grid !!

//2.Fill Grid with information from the image
	COLORREF colorRef;
	int I,J;

	//for the sake of the printf in lines, this reads in the direction of lines, not columns
	for (J=0;J< (Grid->G_Height);J++)	
	{	
		for (I=0;I<(Grid->G_Width);I++)
		{
			colorRef = GetPixel(hDC, I, J); //(DC, x-coordinate of pixel, y-coordinate of pixel)
			printf("(%d,%d,%d) ",GetRValue(colorRef),GetGValue(colorRef),GetBValue(colorRef));
			if (colorRef == CFG_CLR_WALL)
				Grid->SetCellContent_Init(WALL,I,J);			
			else if ((colorRef>= CFG_CLR_FLOWER_BOTTOM) && (colorRef<= CFG_CLR_FLOWER_TOP))
			{
				Grid->SetCellContent_Init(NOTHING,I,J);
				Grid->SetCellGrowingProbability(FlowerProbabilityFromColor(colorRef),I,J);
			}
			else Grid->SetCellContent_Init(NOTHING,I,J);
		}
		printf("\n");
	}


	DeleteObject(hBitmap);
	return true;
}

int CfgManager::FlowerProbabilityFromColor(COLORREF colorRef)
{
	BYTE top_g =GetGValue (CFG_CLR_FLOWER_TOP);
	BYTE bottom_g =GetGValue (CFG_CLR_FLOWER_BOTTOM);
	BYTE pom=(GetGValue(colorRef)-bottom_g);
	return (((pom*100)/(top_g - bottom_g)));
}

bool CfgManager::SaveBeetles(CGrid * grid,char * filename)
{
	FILE * btlFile;
	CBeetle * beetle;
	errno_t err;
	int I,J,K,L,M,N;	

	if ((err= fopen_s(&btlFile,filename,"w"))!=0) 
	{
		printf("%d",err);
		return false;
	}

	for (J=0;J<grid->G_Height;J++)
		for (I=0;I<grid->G_Width;I++)
			if (grid->GetCellContent(I,J,&beetle)== BEETLE)
			{
				fprintf(btlFile," ---------- \n");
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
				fprintf(btlFile,"ExpectOnPartner=");
				for (M=0;M<EXPECT_ON_PARTNER_D1;M++)
						fprintf(btlFile,"%d,%d;",beetle->ExpectOnPartner[M][0],beetle->ExpectOnPartner[M][1]);
				fprintf(btlFile,"\n");
				fprintf(btlFile,"HungryThreshold=%d;\n",beetle->HungryThreshold);
				fprintf(btlFile,"InvInChild=%d;\n",beetle->InvInChild);
				fprintf(btlFile,"LearnAbility=%d;\n",beetle->LearnAbility);
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
	errno_t err;
	if ((err= fopen_s(&btlFile,filename,"r"))!=0) 
	{
		printf("%d",err);
		exit;
	}

	//reading of btlFile using fscanf_s function
		/*remarks:
			1.One white-space character in the format matches any number (including 0) and combination of white-space characters in the input.
		*/
	int I,J = 0;
	int x,y;
	int VarValue=0;
	char  VarName[20];
	bool ok=true;

	while (!feof(btlFile))
	{
		beetle=new CBeetle();
							
		fscanf_s(btlFile," ---------- ");
		if (0==fscanf_s(btlFile," Age = %d ; ",&VarValue)) {ok=false;break;};
		beetle->Age=VarValue;
		fscanf_s(btlFile," Brain = ");
		for (I=0;I<127;I++)
		{
		  if (0==fscanf_s(btlFile," %d ,",&VarValue)) {ok=false;break;};
		  beetle->SetBrain(I,VarValue);
		}
		if (0==fscanf_s(btlFile," %d ; ",&VarValue)) {ok=false;break;};
		beetle->SetBrain(127,VarValue);
		if (0==fscanf_s(btlFile," Direction = %d ; ",&VarValue)) {ok=false;break;};
		beetle->Direction=VarValue;
		if (0==fscanf_s(btlFile," Energy = %d ; ",&VarValue)) {ok=false;break;};
		beetle->Energy=VarValue;
		fscanf_s(btlFile," ExpectOnPartner = ");
		for (I=0;I<4;I++)
		{
		  if (0==fscanf_s(btlFile," %d , ",&VarValue)) {ok=false;break;};
		  beetle->ExpectOnPartner[I][0]=VarValue;
		  if (0==fscanf_s(btlFile," %d ; ",&VarValue)) {ok=false;break;};
		  beetle->ExpectOnPartner[I][1]=VarValue;
		}
		if (0==fscanf_s(btlFile," HungryThreshold = %d ; ",&VarValue)) {ok=false;break;};
		beetle->HungryThreshold=VarValue;
		if (0==fscanf_s(btlFile," InvInChild = %d ; ",&VarValue)) {ok=false;break;};
		beetle->InvInChild=VarValue;
		if (0==fscanf_s(btlFile," LearnAbility = %d ; ",&VarValue)) {ok=false;break;};
		beetle->LearnAbility=VarValue;
		if (0==fscanf_s(btlFile," x = %d ; ",&x)) {ok=false;break;};		
		if (0==fscanf_s(btlFile," y = %d ; ",&y)) {ok=false;break;};		
		fscanf_s(btlFile," ---------- ");
		
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
		exit;
	}

	return true;
}
