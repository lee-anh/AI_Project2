# AI_Project2
In this project, the Sudoku Problem is framed as a Constraint Satisfation Problem. The agent uses a backtracking search, minimum remaining values, least constraining values, and forward checking for optimal performance. 

## Program Design

<img width="787" alt="image" src="https://user-images.githubusercontent.com/57470135/211123651-af44c256-ef19-44f8-a501-7b5eadf1ebf6.png">

- `main.cpp` is the file that drives the experiments
- `Control` is the class that represents the agent. It takes the configuration passed by main.cpp and runs the experiment accordingly. Backtracking search, AC-3, minimum remaining values (MRV) heuristic, least constraining value (LCV) heuristic, and forward checking all live here. 
- `Puzzle` represents the sudoku board. It is made up of Tiles. 
- `Tiles` represent each cell on a sudoku board. Each tile has a string id, a num (the number, if assigned, 0, if not), and a possible domain. 
- `CSP` is the constraint map. There is a key, value pair for every tile. The string id for the tiles are the keys and the values are a vector of Constraints that the key tile is linked to. 
- `Constraint` is a virtual interface 
- `BinaryArc` completes the virtual Constraint interface. The Binary Arc represents a not equals constraint on Tiles. 
- `Sum` also can complete the virtual Constraint interface. The Sum represents a sum constraint on Tiles as seen in Killer sudoku 
- `Alldiff`  represents the classic sudoku constraint of the tiles of the row, cols, and boxes, being unique, respectively. It does not complete the Constraint interface because the Alldiffs are converted to BinaryArcs by the CSP
- `Checker` ensures that the solution proposed by the agent meets the constraints on a standard and overlapping sudoku puzzles, or matches the given solution for the killer sudoku puzzles. 

## User Manual
To run the program with the current configuration listed in main.cpp, simply run `make` from the project root. 
There are also 3 make commands that run the three puzzle types with relatively fast configurations 
```
make standard	 // runs the 10 standard sudoku puzzles 
make overlap 		// runs the 10 overlap sudoku puzzles 
make killer 		// runs the 10 killer sudoku puzzles 
```


To configure the experiment in main.cpp you can manipulate the following booleans and enum to specify how you want to run the project 
```
 bool useAc3 = true;
 bool useMinRemainingValues = true;  
 bool useLeastConstrainingValues = true;
 bool useForwardChecking = false;
 puzzleType type = OVERLAP; // either STANDARD, OVERLAP, or KILLER
```

To clean the project, run `make clean` 
To add new puzzles, add a txt file to the ./Sudoku directory. 
A standard puzzle was encoded like this, where each tile was separated by spaces and each row in the puzzle has its own row too. 
```
0 0 0 0 1 0 0 2 0
0 0 3 4 0 5 0 0 6
0 0 7 0 0 6 0 0 1
6 0 4 0 5 1 0 8 0
0 2 0 0 4 0 0 7 0 
0 8 0 3 9 0 5 0 4
5 0 0 1 0 0 4 0 0 
1 0 0 2 0 7 6 0 0 
0 9 0 0 8 0 0 0 0 
```

Tripledoku puzzles were also encoded in a visually similar way to how the puzzle looks, where - was used to indicate buffer space. 
```
2 4 1 9 3 5 0 0 7 - - - - - - 
0 7 8 6 2 0 9 0 4 - - - - - - 
0 6 0 4 7 8 2 1 0 - - - - - -
6 2 0 7 1 4 5 8 9 0 6 0 - - -  
9 0 4 5 0 2 0 7 1 0 8 0 - - -  
7 0 5 8 9 3 4 2 6 0 0 0 - - -  
8 0 2 0 4 0 7 9 0 0 0 2 0 4 0 
0 9 6 2 0 0 1 0 0 0 9 0 5 7 2
0 5 0 3 8 9 6 4 2 5 7 1 3 8 9 
- - - 6 2 1 9 5 0 3 4 0 0 2 1
- - - 9 3 8 2 6 4 0 0 7 9 0 8
- - - 4 7 5 0 1 3 9 2 0 4 5 7
- - - - - - 5 7 0 2 6 0 8 0 4
- - - - - - 4 8 0 7 1 5 2 6 3
- - - - - - 0 0 0 4 8 9 7 1 5
```

Killer sudoku puzzles were encoded like the standard puzzle, except the txt file looked like this: 
```
// puzzle
// empty line
// puzzle solution 
// empty line
// one line for each sum cage
```

The cages were encoded as the tile numbers, 0…80. These were later translated into coordinates for the tileId by the agent. 

Data is outputted to a running log file for each puzzle type in the log folder. 

