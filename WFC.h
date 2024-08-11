#ifndef WFC_H
#define WFC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRIDSIZE 10

typedef enum{
	EMPTY,
	WALL,
	DOOR,
	TREASURE,
	TRAP,
	MAXTILE
} tileType;

typedef struct{
	int possibleTiles[MAXTILE];
	int collapsedTile;
} Cell;

//Globals

extern Cell grid[GRIDSIZE][GRIDSIZE];
extern int rules [MAXTILE][MAXTILE];

//functions
void init_grid(void);
int calculateEntropy(int possibleTiles[MAXTILE]);
void collapseCell(int x, int y);
void propConstraints(int x, int y);
void WFC(void);
void printGrid(void);

#endif
