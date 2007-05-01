#include "StdAfx.h"
#include "CfgManager.h"
#include "defines.h"
#include "Beetle.h"
#include "Environment.h"
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
bool CfgManager::GetGridInit(int Grid [20][20][2]/*3D array*/, int FirstIndex,int Width, int Height)
{

	//First part - init environment: Loads environment with "places" for beetles
	//LoadEnvironmentFromBmp(Grid,Width, Height, FirstIndex);
	//instead of reading of files is here for the timebeing this: Empty environment 

	int I,J,K;
	//init all Grid.. include borders!
	for (I=0;I< (FirstIndex+Width+1);I++)
		for (J=0;J< (FirstIndex+Height+1);J++)
			for (K=0;K<2;K++)
				Grid[I][J][K]=0;
	


	//Second part - load beetles and add them to half finished environment

	FILE * btlFile;
	errno_t err;
	if ((err= fopen_s(&btlFile,"Beetle.txt","r"))!=0)
	{
		printf("%d",err);
		exit;
	}
/*
	for (I=0;I< (FirstIndex+Width+1);I++)
		for (J=0;J< (FirstIndex+Height+1);J++)
			if (Grid[I][J][0]==BEETLE)
			{
				LoadNextBeetle(btlFile,beetle);
				Grid[I][J][1]=(int)beetle;
			}*/
I=1;
CBeetle * beetle=NULL; 
	
	while (!feof(btlFile))
	{
		beetle= new CBeetle();
		LoadNextBeetle(btlFile,beetle);
		Grid[I][1][0]=BEETLE;
		Grid[I][1][1]=(int)beetle;
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

bool CfgManager::GetGridShape(int * G_FirstIndex,int * G_Width, int * G_Height)
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
      fscanf(file," %d ,",&VarValue);
      beetle->SetBrain(I,VarValue);
    }
    fscanf(file," %d ; ",&VarValue);
    beetle->SetBrain(127,VarValue);
    fscanf_s(file," Direction = %d ; ",&VarValue);
    beetle->Direction=VarValue;
    fscanf_s(file," Energy = %d ; ",&VarValue);
    beetle->Energy=VarValue;
    fscanf_s(file," ExpectOnPartner = ");
    for (I=0;I<4;I++)
    {
      fscanf(file," %d , ",&VarValue);
      beetle->ExpectOnPartner[I][0]=VarValue;
      fscanf(file," %d ; ",&VarValue);
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


//windows specific function to load bmp file of environment
int CfgManager::LoadEnvironmentFromBmp(int Grid  [20][20][2] ,int G_x, int G_y,int G_FI)
{
	HDC hDC = CreateCompatibleDC(0);
	if (hDC==0) printf("chyba DC\n"); //chyba

	wchar_t * name= ENV_BMP_FILE ;
	printf("%s\n", name);

	HBITMAP hBitmap= (HBITMAP) LoadImage(NULL,					//HINSTANCE hinst
								name,	//file name
								IMAGE_BITMAP,	//type of loaded result
								G_x,
								G_y,
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
	}


	SelectObject ( hDC, hBitmap );
	
	int I,J;
	for (I=0;I< (G_FI+G_x+1);I++)
		for (J=0;J< (G_FI+G_y+1);J++)	
		{
			Grid[I][J][0]=0;
			Grid[I][J][1]=0;
		}

	COLORREF colorRef = GetPixel(	hDC,    // handle to DC
									1,  // x-coordinate of pixel
									1   // y-coordinate of pixel
								);
	DeleteObject(hBitmap);

	printf("Picture[1,1]=%X\n",colorRef);
	colorRef = GetPixel(	hDC,    // handle to DC
									0,  // x-coordinate of pixel
									0   // y-coordinate of pixel
								);
	printf("Picture[0,0]=%X\n",colorRef);

	return 0;
}
