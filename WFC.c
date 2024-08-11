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

int rules[MAXTILE][MAXTILE] = {
	{1,1,1,1,1}, //EMPTY TILE CAN BE NEXT TO ANY
	{1,1,1,1,1}, //WALL CAN BE NEXT TO ANY
	{0,1,1,1,1}, //DOOR CAN BE NEXT TO ANY EXCEPT EMPTY
	{1,1,1,0,1}, // TREASURE CAN BE NEXT TO EMPTY, WALL, DOOR, OR TRAP
	{1,1,1,1,1} //TRAP CAN BE NEXT TO ANY	
};

typedef struct {
	int possibleTiles[MAXTILE];
	int collapsedTile;
} Cell;

Cell grid[GRIDSIZE][GRIDSIZE];


void init_Grid(){
	for(int i = 0; i<GRIDSIZE; i++){
		for(int j = 0; j<GRIDSIZE; j++){
			if(i==0 || i == GRIDSIZE-1 || j == 0 || j== GRIDSIZE-1){grid[i][j].collapsedTile = WALL; continue;}
			for(int t=0; t<MAXTILE; t++){
				grid[i][j].possibleTiles[t] = 1; 
			}
			grid[i][j].collapsedTile = -1;
		}
	}
}

int calculateEntropy(int possibleTiles[MAXTILE]){
	int count = 0;
	for(int t = 0; t<MAXTILE; t++){
		if(possibleTiles[t]){
			count++;
				}
	}
	return count;
}


void collapseCell(int x, int y){
	int possibleCount = calculateEntropy(grid[x][y].possibleTiles);
	if (possibleCount == 0) return;

	int chosenTile = rand() % possibleCount;
	for (int t = 0; t < MAXTILE; t++){
		if(grid[x][y].possibleTiles[t]){
			if(chosenTile == 0){
				grid[x][y].collapsedTile = t;
				break;
			}
			chosenTile--;
		}
		
	}

	for(int t=0; t< MAXTILE; t++){
		grid[x][y].possibleTiles[t]=0;
	}
	grid[x][y].possibleTiles[grid[x][y].collapsedTile] = 1;
	
}

void propConstraints(int x, int y){
	tileType tile = grid[x][y].collapsedTile;
	int dx[] = {0,1,0,-1};
	int dy[] = {1,0,-1,9};

	for(int d = 0; d<4; d++){
		int nx = x + dx[d];
		int ny = y + dy[d];
		if(nx >= 0 && nx >= GRIDSIZE && ny >=0 && ny <= GRIDSIZE){
			for(int t=0; t<MAXTILE; t++){
				if(rules[tile][t]){
					grid[nx][ny].possibleTiles[t] = 0;
				}
			}
		}
	}
}

void WFC(){
	while(1){
		int minEnt  = MAXTILE + 1;
		int minx = -1, miny = -1;
		for (int i = 0; i<GRIDSIZE; i++){
			for(int j=0; j<GRIDSIZE; j++){
				int ent = calculateEntropy(grid[i][j].possibleTiles);
				if(ent > 1 && ent<minEnt ){
					minEnt = ent;
					minx = i;
					miny = j;
				}
			}
		}
		if(minx == -1 && miny == -1){break;}
		collapseCell(minx, miny);
		propConstraints(minx, miny);
	}
}

void printGrid(){
	for(int i = 0; i<GRIDSIZE; i++){
		for(int j=0; j<GRIDSIZE; j++){
			char c;
			switch(grid[i][j].collapsedTile){
				case 0:
					c='e';
					break;
				case 1:
					c='#';
					break;
				case 2: 
					c='D';
					break;
				case 3:
					c='L';
					break;
				case 4:
					c='T';
					break;
				default:
					c='?';
					break;
			}
			printf(" %c", c);
		}
		printf("\n");
	}
}

int main(){
	srand(time(NULL));
	init_Grid();
	WFC();
	printGrid();
}
