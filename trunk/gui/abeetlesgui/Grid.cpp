#include "StdAfx.h"
#include "Grid.h"
#include "defines.h"
#include <assert.h>
#include <QMessageBox>

CGrid::CGrid(void)
{
	int I,J;
	G_Width=DEFAULT_GRID_WIDTH;
	G_Height=DEFAULT_GRID_HEIGHT;
	G_FirstIndex=1;
	//init all Grid to zero values.. all the allocated memory, not only within default grid and height!
	for (I=0;I<(G_WIDTH_MAX+ (2* G_FIRST_INDEX_MAX));I++ )//((2*G_FirstIndex)+G_Width);I++)
		for (J=0;J<(G_HEIGHT_MAX+ (2* G_FIRST_INDEX_MAX));J++ )//((2*G_FirstIndex)+G_Height);J++)
		{
			GridMatrix[I][J][0]=NOTHING;
			GridMatrix[I][J][1]=0;
			GridMatrix[I][J][2]=0;
		}
	//1QMessageBox::information(NULL,"Grid","Grid is in constructor");
}


CGrid::~CGrid(void)
{
	/*
	int I,J;
	for (I=0;I< ((2*G_FirstIndex)+G_Width);I++)
			for (J=0;J< ((2*G_FirstIndex)+G_Height);J++)
			{
				if (GridMatrix[I][J][0]==BEETLE) delete ((CBeetle*)GridMatrix[I][J][1]);	
			}
	*/			
}

/**
* Public method:GetCellContent
* Desc: Returns id of content of the cell and if there is a beetle, it returns pointer to it.
* System dependence: no
* Usage comments:
* @return (Return values - meaning) : id of content of a cell - see defines.h
* @param name [ descrip](Parameters - meaning): x,y - coords of the cell in Grid, we are interested in. beetle_ref - reference to reference to a beetle, where the reference of found beetle is placed, if there is a beetle in [x,y] cell
* @throws name [descrip](Exceptions - meaning)
*/
int CGrid::GetCellContent(int x, int y, CBeetle** beetle_ref)
{
	if ((x<0) ||(x>=(G_Width))||(y<0)||(y>=(G_Height))) return 0;

	//if beetle_ref is specified so as to put reference to the beetle into it.
	if (GridMatrix [x+G_FirstIndex][y+G_FirstIndex][0] == BEETLE)
		if (beetle_ref!=NULL)
			*beetle_ref = (CBeetle*)GridMatrix [x+G_FirstIndex][y+G_FirstIndex][1];
	//--debug:
	if (GridMatrix [x+G_FirstIndex][y+G_FirstIndex][0]==NOTHING) 
	{
		assert (GridMatrix [x+G_FirstIndex][y+G_FirstIndex][1]==NULL);
	}

	return GridMatrix [x+G_FirstIndex][y+G_FirstIndex][0];


}

int CGrid::GetCellGrowingProbability(int x, int y)
{
	if ((x<0) ||(x>=(G_Width))||(y<0)||(y>=(G_Height))) return 0;
	else return GridMatrix [x+G_FirstIndex][y+G_FirstIndex][2] ;
}

bool CGrid::SetCellContent(int what,int x, int y, CBeetle * beetle )
{
	//x and y must be within borders
	if ((x<0) ||(x>=(G_Width))||(y<0)||(y>=(G_Height))) return false;
	//'what' must be beetle, flower or nothing
	if ((what!=BEETLE) &&(what!=NOTHING)&&(what!=FLOWER)) return false;
	//wall cannot be changed in this soft setCellContent function
	if (GridMatrix [x+G_FirstIndex][y+G_FirstIndex][0]==WALL) return false;
	//if cell is gonna be changed to beetle, beetle_ref must be pointed to a beetle 
	if (what==BEETLE) 
	{
		if (beetle == NULL) return false;
		else
			GridMatrix [x+G_FirstIndex][y+G_FirstIndex][1]=(int)beetle;
	}
	else
		GridMatrix [x+G_FirstIndex][y+G_FirstIndex][1]=NULL;//if here was a ref to beetle, I have to delete it.
		
	GridMatrix [x+G_FirstIndex][y+G_FirstIndex][0]=what;
	return true;
}

bool CGrid::SetCellGrowingProbability(int probability,int x, int y)
{
	if ((x<0) ||(x>=(G_Width))||(y<0)||(y>=(G_Height))) return false;

	if ((probability<0) || (probability>100)) return false;

	//probability can be set to any cell, even to the wall - it causes nothing then
	GridMatrix [x+G_FirstIndex][y+G_FirstIndex][2] = probability;
	return true;
}

bool CGrid::SetCellContent_Init(int what/* BEETLE/FLOWER/NOTHING/WALL */,int x, int y, CBeetle * beetle)
{
	//x and y must be within borders
	if ((x<0) ||(x>=(G_Width))||(y<0)||(y>=(G_Height))) return false;
	//'what' must be beetle, flower or nothing
	if ((what!=BEETLE) &&(what!=NOTHING)&&(what!=FLOWER)&&(what!=WALL)) return false;

	//if cell is gonna be changed to beetle, beetle_ref must be pointed to a beetle 
	if (what==BEETLE) 
	{
		if (beetle == NULL) return false;
		else
			GridMatrix [x+G_FirstIndex][y+G_FirstIndex][1]=(int)beetle;
	}
	else
		GridMatrix [x+G_FirstIndex][y+G_FirstIndex][1]=NULL; //if here was a ref to beetle, I have to delete it.
		
	GridMatrix [x+G_FirstIndex][y+G_FirstIndex][0]=what;
	return true;
}

void CGrid::SetDefaultGridShape()
{
	G_FirstIndex=1;
	G_Width = DEFAULT_GRID_WIDTH;
	G_Height =DEFAULT_GRID_HEIGHT;	
}

bool CGrid::SetGridShape(int FI,int W,int H)
{
	if ((W+(2*FI)<G_WIDTH_MIN) || (W+(2*FI)>G_WIDTH_MAX)) return false;
	if ((H+(2*FI)<G_HEIGHT_MIN) || (H+(2*FI)>G_HEIGHT_MAX)) return false;
	
	G_Width=W;
	G_Height=H;
	G_FirstIndex=FI;
	return true;
}

/**
* Public method <br>
* Desc: Puts zero to all cells of matrix of the grid and delete beetles. Beware, beetles are cleaned after one clean of Grid<br>
* System dependence:no<br>
* Usage comments:<br>
*/

void CGrid::CleanGridAndBeetles()
{
	int I,J;
	for (I=0;I< ((2*G_FirstIndex)+G_Width);I++)
			for (J=0;J< ((2*G_FirstIndex)+G_Height);J++)
			{
				if (GridMatrix[I][J][0]==BEETLE) delete ((CBeetle*)GridMatrix[I][J][1]);
				GridMatrix[I][J][0]=NOTHING;
				GridMatrix[I][J][1]=0;
				GridMatrix[I][J][2]=0;
			}
	G_Width=DEFAULT_GRID_WIDTH;
	G_Height=DEFAULT_GRID_HEIGHT;
	G_FirstIndex=1;
}


/**
* Public method:
* Desc: Returns coords of the neighbor cell in chosen E/N/W/S direction
* System dependence:no
* Usage comments:
* @return (Return values - meaning) : if input direction is not correct, it returns false, true otherwise.
* @param name [ descrip](Parameters - meaning): x,y - coords of the original cell. n_x, n_y - references to the obtained coords of the neighbor cell. direction = id of the point of the compass - EAST, NORTH, WEST, SOUTH - see defines.h
* @throws name [descrip](Exceptions - meaning)
* Remarks:ZKONTROLUJ!!!
*/
bool CGrid::GetNeigborCellCoords(int x, int y, int * n_x,int * n_y, char direction)
{

	switch (direction)
	{
	case WEST:
		if (x==0) x=WestBorder();
			else x=x-1;
		break;
	case NORTH:
		if (y==0) y=NorthBorder();
			else y=y-1;
		break;
	case EAST:
		if (x==G_Width-1) x=EastBorder();
			else x=x+1;
		break;
	case SOUTH:
		if (y==G_Height-1) y=SouthBorder();
			else y=y+1;
		break;
	default:
		return false;
	}
	*n_x=x;
	*n_y=y;

return true;
}

int CGrid::WestBorder(void)
{
	return G_Width-1;
}

int CGrid::NorthBorder(void)
{
	return G_Height-1;
}

int CGrid::EastBorder(void)
{
	return 0;
}

int CGrid::SouthBorder(void)
{
	return 0;
}
