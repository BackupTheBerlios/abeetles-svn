#pragma once
#include "Beetle.h"


/**
* Desc: Abstraction of the Grid of the Environment
* System dependence: no
* Interface: Shows grid as a normal matrix [0..G_Width][0..G_Height] and stores information about what is in cells
*	and about features of the cells(=flower growing probability) references to beetles. Masks two layers of the grid.
* Usage comments:
* Relations to other classes: Used by Environment for Grid_Past and Grid_next
*/
class CGrid
{
public:
	CGrid(void);
	~CGrid(void);

	//attributes
	public:
	int G_Width; //Grid[G_FirstIndex+G_Width][G_FirstIndex+G_Height][0]is the bottom right corner of the grid
	int G_Height;
	protected:	
	//Three-layered grid:
		//1st layer: what is actualy where
		//2nd layer: beetles references
		//3rd layer: probability of growth of flowers
	int GridMatrix [G_WIDTH_MAX][G_HEIGHT_MAX][3] ;
	int G_FirstIndex; //Grid[G_FirstIndex][G_FirstIndex][0]is the top left corner of the grid


	//methods
	public:
	int GetCellContent(int x, int y, CBeetle ** beetle_ref=NULL);//returns, if BEETLE/FLOWER/WALL/ is in the cell of the grid
	int GetCellGrowingProbability (int x, int y);

	bool SetCellContent(int what /* BEETLE/FLOWER/NOTHING */,int x, int y,CBeetle * beetle=NULL); //soft changes - from environment
	bool SetCellGrowingProbability (int probability,int x, int y);
	
	bool SetCellContent_Init(int what /* BEETLE/FLOWER/NOTHING/WALL */,int x, int y,CBeetle * beetle=NULL );//hard changes - from CfgManager
	bool SetGridShape(int FI,int W,int H);

	bool GetNeigborCellCoords(int x, int y, int * n_x,int * n_y, char direction);

	protected:	
	int WestBorder(void);
	int NorthBorder(void);
	int EastBorder(void);
	int SouthBorder(void);
};
