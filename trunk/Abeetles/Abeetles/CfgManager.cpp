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
bool CfgManager::GetGridInit(CGrid * Grid)
{
	int FI,W,H;
	if (false==LoadGridShape(&FI,&W,&H)) return false;
	if (false==Grid->SetGridShape(FI,W,H)) return false;

	//First part - init environment: Loads environment without beetles
	LoadEnvironmentFromBmp(Grid);


	//Second part - load beetles and add them to half finished environment
	CBeetle * beetle=NULL;

	FILE * btlFile;
	errno_t err;
	if ((err= fopen_s(&btlFile,"Beetle.txt","r"))!=0) 
		printf("%d",err);

	/*
	for (I=0;I< (FirstIndex+Width+1);I++)
		for (J=0;J< (FirstIndex+Height+1);J++)
			if (Grid[I][J][0]==BEETLE)
			{
				LoadNextBeetle(btlFile,beetle);
				Grid[I][J][1]=(int)beetle;
			}*/
	int I = 0;
	while (!feof(btlFile))
	{
		beetle=new CBeetle();
		LoadNextBeetle(btlFile,beetle);
		Grid->SetCellContent(BEETLE,I,0,beetle);		
		I++;
	}
	fclose(btlFile);

	
	return true;
}

int CfgManager::LoadBeetleCfgFile(void)
{
	char VarName[25];
	int VarValue=0;
	errno_t err;
	int I;
	FILE * pConfigFile;
	if ((err= fopen_s(&pConfigFile,"BeetleCfg.txt","r"))!=0) 
		return err;
	for (I=0;I<NUMOPTVARIABLES;I++)
	{
		fscanf_s(pConfigFile,"%s=%d\n",VarName,&VarValue);
		if ( strcmp(VarName,"EnergyMax_C") == 0) CBeetle::EnergyMax_C=VarValue;
		else CBeetle::EnergyMax_C=50;

	}
	return 0;
}

bool CfgManager::LoadGridShape(int * G_FirstIndex,int * G_Width, int * G_Height)
{
	*G_FirstIndex=1;
	*G_Width = 15;
	*G_Height =15;
	return true;
}

bool CfgManager::GetOptionsInit(void)
{
	//proprietary solution
	CBeetle::EnergyMax_C=50;
	//later: LoadBeetleCfgFile();
	return true;
}

bool CfgManager::LoadNextBeetle(FILE * file, //file opened for reading
								CBeetle* beetle)
{
	char  VarName[20];
	int VarValue=0;
	int I;
		
	//reading of file using fscanf_s function
	/*remarks:
		1.One white-space character in the format matches any number (including 0) and combination of white-space characters in the input.
	*/
		fscanf_s(file," ---------- ");
    fscanf_s(file," Age = %d ; ",&VarValue);
    beetle->Age=VarValue;
    fscanf_s(file," Brain = ");
    for (I=0;I<127;I++)
    {
      fscanf_s(file," %d ,",&VarValue);
      beetle->SetBrain(I,VarValue);
    }
    fscanf_s(file," %d ; ",&VarValue);
    beetle->SetBrain(127,VarValue);
    fscanf_s(file," Direction = %d ; ",&VarValue);
    beetle->Direction=VarValue;
    fscanf_s(file," Energy = %d ; ",&VarValue);
    beetle->Energy=VarValue;
    fscanf_s(file," ExpectOnPartner = ");
    for (I=0;I<4;I++)
    {
      fscanf_s(file," %d , ",&VarValue);
      beetle->ExpectOnPartner[I][0]=VarValue;
      fscanf_s(file," %d ; ",&VarValue);
      beetle->ExpectOnPartner[I][1]=VarValue;
    }
    fscanf_s(file," HungryThreshold = %d ; ",&VarValue);
    beetle->HungryThreshold=VarValue;
    fscanf_s(file," InvInChild = %d ; ",&VarValue);
    beetle->InvInChild=VarValue;
    fscanf_s(file," LearnAbility = %d ; ",&VarValue);
    beetle->LearnAbility=VarValue;

		fscanf_s(file," ---------- ");
	
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
bool CfgManager::LoadEnvironmentFromBmp(CGrid * Grid)
{
//1. Read the bmp file
	//In windows any image must be connected with a device context, so as to read individual pixels
	HDC hDC = CreateCompatibleDC(0);
	if (hDC==0) printf("chyba DC\n"); //chyba

	
	wchar_t * name= ENV_BMP_FILE ;// function LoadImage needs a unicode string!
	printf("%s\n", name);

	HBITMAP hBitmap= (HBITMAP) LoadImage(NULL,//HINSTANCE hinst
								name,	//file name - as UNICODE string !!!!
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
			//printf("(%d,%d,%d) ",GetRValue(colorRef),GetGValue(colorRef),GetBValue(colorRef));
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
	return ((GetGValue(colorRef)-bottom_g)/(top_g - bottom_g));
}