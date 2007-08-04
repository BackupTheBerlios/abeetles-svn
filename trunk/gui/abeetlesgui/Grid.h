#pragma once
#include "Beetle.h"


/**
* Desc: Abstraction of the Grid of the Environment
* System dependence: no
* Interface: Shows grid as a normal matrix [0..G_Width][0..G_Height] and stores information about what is in cells
*	and about features of the cells(=flower growing probability) references to beetles. Masks two layers of the grid.
* Usage comments:
* Relations to other classes: Used by Environment for Grid
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
		//4th layer: symbol if the cell is already updated or not
	//Beware! indexes are picture-like, not matrix-like! -> Grid[col][row]!!
	int GridMatrix [G_WIDTH_MAX+ (2* G_FIRST_INDEX_MAX)][G_HEIGHT_MAX+(2* G_FIRST_INDEX_MAX)][4] ;
	int G_FirstIndex; //Grid[G_FirstIndex][G_FirstIndex][0]is the top left corner of the grid

public:
	int UpdatedSymbol;
	int NotUpdatedSymbol;


	//methods
	public:
	bool IsCellUpdated(int x,int y);
	bool SetCellUpdated(int x,int y);
	bool SwitchUpdatedGridToNotUpdated();

	int GetCellContent(int x, int y, CBeetle ** beetle_ref=0);//returns, if BEETLE/FLOWER/WALL/ is in the cell of the grid
	int GetCellGrowingProbability (int x, int y);

	bool SetCellContentAndUpdate(int what /* BEETLE/FLOWER/NOTHING */,int x, int y,CBeetle * beetle=0); //soft changes - from environment
	bool SetCellContentNotUpdate(int what /* BEETLE/FLOWER/NOTHING */,int x, int y,CBeetle * beetle=0); //soft changes - from environment

	bool SetCellGrowingProbability (int probability,int x, int y);
	
	bool SetCellContent_Init(int what /* BEETLE/FLOWER/NOTHING/WALL */,int x, int y,CBeetle * beetle=0 );//hard changes - from CfgManager
	bool SetGridShape(int FI,int W,int H);
	void SetDefaultGridShape();
	void CleanGridAndBeetles();

	bool GetNeigborCellCoords(int x, int y, int * n_x,int * n_y, char direction);

	protected:	
	int WestBorder(void);
	int NorthBorder(void);
	int EastBorder(void);
	int SouthBorder(void);
};
