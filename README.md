# Wave Function Collapse (WFC) Implementation

This is an example implementation of Wave Function Collapse, primarily intended for use in my C-Based Text Adventure Game. The WFC algorithm is a procedural generation technique that implements constraint solving to procedurally generate (in this case) a 2D grid layout. 

## Grid Layout
The grid generated is a 10x10 2D array where each cell generated cal be represented by one of the following tile types:

- **EMPTY** ('e'): An empty space.
- **WALL*** ('#'): A wall that defines boundaries or obstacles.
- **DOOR** ('D'): A door.
- **TREASURE** ('L'): A tile representing a treasure room.
- **TRAP** ('T'): A Trap.

Each tile is constrained by what other tiles it can be adjecent to. This is defined in the "rules" array.

## FIles
- **WFC.c**: The Main implementation file containing the WFC algorithm and helper functions.  
- **WFC.h**: The header file to include in implementations.   
- **Makefile**: A file containing the gcc command to make the executable.  
- **WFC**: The executable that shows a test version of the WFC algorithm.  

## Functions  
  
- `void init_Grid()`: Initializes the grid, setting boundary cells to `WALL` and making every other cell possible to contain any tile type.  
- `int calculateEntropy(int possibleTiles[MAXTILE])`: Calculates the entropy of a cell, which is the number of possible tiles it can collapse into.  
- `void collapseCell(int x, int y)`: Collapses a cell into a single tile based on its entropy and sets the cell to that tile. 
- `void propConstraints(int x, int y)`: Propagates constraints to neighboring cells after a cell is collapsed, updating their possible tile states based on the rules.  
- `void WFC()`: The main Wave Function Collapse algorithm, which iteratively finds the cell with the lowest entropy, collapses it, and propagates constraints until the entire grid is collapsed.  
- `void printGrid()`: Prints the final grid layout to the console, using characters to represent different tile types.  
  
## Usage
  
1. Compile the code to an executable either using `make` or a c compiler:  
   ```sh
   gcc -o wfc wfc.c
2. Run the executable:  
   ```sh
   ./wfc

## Example Output  
  
```sh
 # # # # # # # # # #
 # L D e e L T T L #
 # T # # e e # L D #
 # # L T T e # # e #
 # T # D T e T D L #
 # L T L # L T # L #
 # D D L D # L D D #
 # # # L T e T T T #
 # D L e T D D D e #
 # # # # # # # # # #
```
  
In this example, walls (#), doors (D), treasures (L), traps (T), and empty spaces (e) are distributed across the grid according to the constraints defined in the rules.
