/*
 * Daniel Vazquez, Kiran Vasudev, Patrick Nagel
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 6
 *
 * agent.cpp
 * */
#include "agent.hpp"
#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
#include <stack>

#define INFINITY 999

Agent::Agent(Puzzle puzzle, string solver, string heuristic) :
		puzzle(puzzle), solver(solver), heuristic(heuristic) {

}

Agent::~Agent() {

}

void Agent::run() {

	if (solver == "1") {
		cout << "Greedy Search" << endl;
		if (heuristic == "1") {
			cout << "Heuristic: Misplaced tiles" << endl;
		}

		else {
			cout << "Heuristic: Manhattan distance" << endl;
		}
		greedy_search(heuristic);
	}

}

//counts the number of misplaced tiles
int Agent::countMisplaced(int elementsInArray[],int size) {
	int count = 0;
	for(int i = 0; i< size; i++)
		if(elementsInArray[i] != i+1)
			count ++;

	return count;
}

//returns the coordinates of 0 in the puzzle
int Agent::indexOfZero(int tiles[], int size) {
	int position;
	for (int i = 0; i< size; i++)
			if (tiles[i] == 0){
				position = i;
				break;
			}
	return position;
}

//swaps the values in the puzzle
void Agent::swapValues(int tiles[], int childPosition, int zeroPosition){
	int temp;
	temp = tiles[childPosition];
	tiles[childPosition] = tiles[zeroPosition];
	tiles[zeroPosition] = temp;
}

int checkMin(int a, int b, int c, int d){
	if(a<b && a<c && a<d)
		return a;
	if(b<c && b<d && b<a)
		return b;
	if(c<d && c<a && c<b)
		return c;
	if(d<a && d<b && d<c)
		return d;
}

int *copyValues(int a[], int b[],int size){
	for(int i = 0; i< size; i++)
		b[i] = a[i];
	return b;
}

int Agent::tempSwapCount(int arr[], int size, int move, int zeroPos){
	int tempElements[9], moveValue;

	//copying the elements to another array
	//tempElements = copyValues(arr, tempElements, size);
	for(int i = 0; i< size; i++)
			tempElements[i] = arr[i];
	//swapping the values for the move
	swapValues(tempElements, move, zeroPos);
	//calculating the number of misplaced tiles after swapping
	moveValue = Agent::countMisplaced(tempElements, size);

	return moveValue;
}


int Agent::misplaced_tiles(Puzzle puzzle) {
//TODO
//returns the number of misplaced tiles
	cout << "0,0 - " << puzzle[0][0] << endl;
	cout << "0,1 - " << puzzle[0][1] << endl;

	//Holds the current elements in an array and is used for swapping
	int elements[9];

	//the goals from these positions
	int upMove, downMove, leftMove, rightMove;

	//values of the moves
	int rightMoveValue, upMoveValue, leftMoveValue, downMoveValue;

	//stores the last visited index
	int lastVisited,misplacedNumber;
	//gets the position of element 0
	int posOfZero, iterationNumber = 0;

	//Result will be printed to this puzzle
	Puzzle result(8, std::vector<int>(8, 0)), temp(8, std::vector<int>(8, 0));

	//populate the array with all elements of the puzzle
	int index = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			elements[index++] = puzzle[i][j];

	//gets initial number of misplaced tiles
	misplacedNumber = countMisplaced(elements, index);

	//run loop until all the elements have reached their respective positions

	while (iterationNumber < 1000) {

		int posOfZero = indexOfZero(elements, index);

		switch (posOfZero) {
		case 0:
			downMove = 3;
			rightMove= 1;

			if (lastVisited != downMove) {
				downMoveValue = tempSwapCount(elements, index, downMove, posOfZero);
			}

			if (lastVisited != rightMove) {
				rightMoveValue = tempSwapCount(elements, index, rightMove, posOfZero);
			}

			if(rightMove <= downMove)
				swapValues(elements, rightMove, posOfZero);
			else if(downMove < rightMove)
				swapValues(elements, downMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;
		case 1:
			leftMove = 0;
			downMove = 4;
			rightMove = 2;

			if (lastVisited != downMove)
				downMoveValue = tempSwapCount(elements, index, downMove, posOfZero);

			if (lastVisited != rightMove)
				rightMoveValue = tempSwapCount(elements, index, rightMove, posOfZero);

			if (lastVisited != leftMove)
				leftMoveValue = tempSwapCount(elements, index, leftMove, posOfZero);

			if ((rightMoveValue <= downMoveValue)&&(rightMoveValue <= leftMoveValue))
				swapValues(elements, rightMove, posOfZero);

			else if ((downMoveValue <= rightMoveValue)&&(downMoveValue <= leftMoveValue))
				swapValues(elements, downMove, posOfZero);

			else if((leftMoveValue <= downMoveValue)&&(leftMoveValue <= rightMoveValue))
				swapValues(elements, leftMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;
		case 2:
			leftMove = 1;
			rightMove = 5;

			if (lastVisited != rightMove) {
				rightMoveValue = tempSwapCount(elements, index, rightMove, posOfZero);
			}

			if (lastVisited != leftMove) {
				leftMoveValue = tempSwapCount(elements, index, leftMove, posOfZero);
			}

			if (leftMove <= rightMove)
				swapValues(elements, leftMove, posOfZero);

			else if (rightMove < leftMove)
				swapValues(elements, rightMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;
		case 3:
			upMove =0;
			rightMove = 4;
			downMove = 6;

			if (lastVisited != upMove)
				upMoveValue = tempSwapCount(elements, index, upMove, posOfZero);

			if (lastVisited != rightMove)
				rightMoveValue = tempSwapCount(elements, index, rightMove, posOfZero);

			if (lastVisited != downMove)
				downMoveValue = tempSwapCount(elements, index, downMove, posOfZero);

			if ((rightMoveValue <= downMoveValue) && (rightMoveValue <= upMoveValue))
				swapValues(elements, rightMove, posOfZero);

			else if ((upMoveValue <= rightMoveValue) && (upMoveValue <= downMoveValue))
				swapValues(elements, upMove, posOfZero);

			else if ((downMoveValue <= rightMoveValue) && (downMoveValue <= upMoveValue))
				swapValues(elements, downMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;
		case 4:
			upMove =1;
			rightMove = 5;
			leftMove = 3;
			downMove= 7;

			if (lastVisited != upMove)
				upMoveValue = tempSwapCount(elements, index, upMove, posOfZero);

			if (lastVisited != rightMove)
				rightMoveValue = tempSwapCount(elements, index, rightMove,posOfZero);

			if (lastVisited != downMove)
				downMoveValue = tempSwapCount(elements, index, downMove,posOfZero);

			if (lastVisited != leftMove)
				leftMoveValue = tempSwapCount(elements, index, leftMove,posOfZero);

			if ((rightMoveValue <= downMoveValue)&& (rightMoveValue < upMoveValue)&& (rightMoveValue < leftMoveValue))
				swapValues(elements, rightMove, posOfZero);

			else if ((upMoveValue < rightMoveValue)&& (upMoveValue < downMoveValue)&& (upMoveValue < leftMoveValue))
				swapValues(elements, upMove, posOfZero);

			else if ((downMoveValue < rightMoveValue)&& (downMoveValue < upMoveValue)&& (downMoveValue < leftMoveValue))
				swapValues(elements, downMove, posOfZero);

			else if((leftMoveValue < downMoveValue)&&(leftMoveValue < rightMoveValue)&&(leftMoveValue < upMoveValue))
							swapValues(elements, leftMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;

		case 5:
			upMove = 2;
			downMove = 8;
			leftMove = 4;

			if (lastVisited != upMove)
				upMoveValue = tempSwapCount(elements, index, upMove, posOfZero);

			if (lastVisited != leftMove)
				leftMoveValue = tempSwapCount(elements, index, leftMove,posOfZero);

			if (lastVisited != downMove)
				downMoveValue = tempSwapCount(elements, index, downMove,posOfZero);

			if ((leftMoveValue <= downMoveValue)&& (leftMoveValue <= upMoveValue))
				swapValues(elements, leftMove, posOfZero);

			else if ((upMoveValue <= leftMoveValue)&& (upMoveValue <= downMoveValue))
				swapValues(elements, upMove, posOfZero);

			else if ((downMoveValue <= leftMoveValue)&& (downMoveValue <= upMoveValue))
				swapValues(elements, downMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;

		case 6:
			upMove = 3;
			rightMove = 7;

			if (lastVisited != rightMove) {
				rightMoveValue = tempSwapCount(elements, index, rightMove,posOfZero);
			}

			if (lastVisited != upMove) {
				upMoveValue = tempSwapCount(elements, index, upMove,posOfZero);
			}

			if (upMove <= rightMove)
				swapValues(elements, upMove, posOfZero);

			else if (rightMove < upMove)
				swapValues(elements, rightMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;

		case 7:
			upMove =4;
			leftMove = 6;
			rightMove = 8;

			if (lastVisited != upMove)
				upMoveValue = tempSwapCount(elements, index, upMove, posOfZero);

			if (lastVisited != leftMove)
				leftMoveValue = tempSwapCount(elements, index, leftMove,posOfZero);

			if (lastVisited != rightMove)
				rightMoveValue = tempSwapCount(elements, index, rightMove,posOfZero);

			if ((leftMoveValue <= rightMoveValue)&& (leftMoveValue <= upMoveValue))
				swapValues(elements, leftMove, posOfZero);

			else if ((upMoveValue <= rightMoveValue)&& (upMoveValue <= leftMoveValue))
				swapValues(elements, upMove, posOfZero);

			else if ((rightMoveValue <= leftMoveValue)&& (rightMoveValue <= upMoveValue))
				swapValues(elements, rightMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;

		case 8:
			upMove = 5;
			leftMove = 7;

			if (lastVisited != leftMove) {
				leftMoveValue = tempSwapCount(elements, index, leftMove, posOfZero);
			}

			if (lastVisited != upMove) {
				upMoveValue = tempSwapCount(elements, index, upMove, posOfZero);
			}

			if (upMove <= leftMove)
				swapValues(elements, upMove, posOfZero);

			else if (leftMove < upMove)
				swapValues(elements, leftMove, posOfZero);

			misplacedNumber = countMisplaced(elements, index);

			break;
		default:
			break;
		}

		cout << "Result: " <<endl;
		for(int i=0;i<index;i++)
			cout<<elements[i];

		cout << "Iterations " << iterationNumber++ << endl;

		cout << "--------------------------------------------------------"<<endl;
	}


		// The goal is reached. Now the array, which was used for computation, will be translated back to a puzzle.
		index = 0;
		/*for (int row = 0; row < 3; row++) {
		 for (int column = 0; column < 3; column++) {
		 result[row][column] = checkList[index++];
		 }
		 }*/

		// Prints the final puzzle...
		//print_puzzle(result);
		// and the amount of iterations.

	}


int Agent::manhattan_distance(Puzzle puzzle) {

	// The following variable (previousIndexOfZero) is needed to avoid backward steps.
	int previousIndexOfZero = 0;

	// The index of the zero tile is of great significance. It indicates the possible moves.
	int indexOfZero;


	//The following variable will be used to save the values of the 8-puzzle in an array. ...
	int tilesInPuzzle[9];

	//... In the follwing for loop the puzzle will be translated, going from left to right, row by row.
	int index = 0;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			tilesInPuzzle[index++] = puzzle[row][column];
		}
	}

	// Variable for the sum of distances. The distance is called Manhattan distance.
	int sumOfDistances = getSumOfDistances(tilesInPuzzle);

	/* Variables for the potential distances after moving into the chosen direction.
	 * The directions are mentioned in the name of each variable.*/
	int distanceRight;
	int distanceLeft;
	int distanceUp;
	int distanceDown;

	/* As important as the distances of each tile, are the index of the values inside.
	 * After evaluating which potential distance is the most suitablel, the tile which goes with it has to be swapped
	 * with the zero tile. Thus the index of the tile is needed.*/
	int indexRight;
	int indexLeft;
	int indexUp;
	int indexDown;

	// The following array saves the (max) four neighbors of the zero tile.
	int neighbors[4];

	/* To evaluate which neighbor of the zero tile would give an improvement, they have to be compared to each other.
	 * The following variables are used to save the min-value and the index of the tile.*/
	int min;
	int minIndex;

	/* The following puzzle variable will be used at the end of the algorithm to show the final result.
	 * To make it possible the array, which is used in the meantime, will be translated back to a puzzle.*/
	Puzzle resultPuzzle(8, std::vector<int>(8, 0));

	// The variable iteration counts how many movements are needed to achive the goal.
	int iteration = 0;

	// The while-loop iterates until the result of the heuristic function will be zero and the goal is reached.
	while (sumOfDistances != 0) {

		/* For each loop the following values will be reseted.
		 * Their starting values are values, which cannot appear out of algorithm.
		 * If a tile has (for example) no left tile. The values of the correspondig variable will stay -1
		 * and it will be ignored for a movement.*/
		distanceRight = -1;
		distanceLeft = -1;
		distanceUp = -1;
		distanceDown = -1;

		indexRight = -1;
		indexLeft = -1;
		indexUp = -1;
		indexDown = -1;

		// Where is the zero tile?
		indexOfZero = findZeroTile(tilesInPuzzle);

		/* Depending on the position of zero there are just certain moves possible.
		 * The following lines check each possibility.*/
		if (indexOfZero == 0) {
			indexRight = 1;
			indexDown = 3;

			/* These if-clauses check if the zero tile has been at the position before.
			 * If so, they will not be considered in the iteration. That means, that after the initial iteration
			 * there is always one less possible move.*/
			if (previousIndexOfZero != 1) {
				distanceRight = getNewDistanceToGoal(1, 0, tilesInPuzzle);
			}

			if (previousIndexOfZero != 3) {
				distanceDown = getNewDistanceToGoal(3, 0, tilesInPuzzle);
			}

		}
		if (indexOfZero == 1) {
			indexLeft = 0;
			indexRight = 2;
			indexDown = 4;

			if (previousIndexOfZero != 0) {
				distanceLeft = getNewDistanceToGoal(0, 1, tilesInPuzzle);
			}

			if (previousIndexOfZero != 2) {
				distanceRight = getNewDistanceToGoal(2, 1, tilesInPuzzle);
			}

			if (previousIndexOfZero != 4) {
				distanceDown = getNewDistanceToGoal(4, 1, tilesInPuzzle);
			}
		}
		if (indexOfZero == 2) {
			indexLeft = 1;
			indexDown = 5;

			if (previousIndexOfZero != 1) {
				distanceLeft = getNewDistanceToGoal(1, 2, tilesInPuzzle);
			}

			if (previousIndexOfZero != 5) {
				distanceDown = getNewDistanceToGoal(5, 2, tilesInPuzzle);
			}
		}

		if (indexOfZero == 3) {
			indexUp = 0;
			indexRight = 4;
			indexDown = 6;

			if (previousIndexOfZero != 0) {
				distanceUp = getNewDistanceToGoal(0, 3, tilesInPuzzle);
			}

			if (previousIndexOfZero != 4) {
				distanceRight = getNewDistanceToGoal(4, 3, tilesInPuzzle);
			}

			if (previousIndexOfZero != 6) {
				distanceDown = getNewDistanceToGoal(6, 3, tilesInPuzzle);
			}
		}
		if (indexOfZero == 4) {
			indexLeft = 3;
			indexUp = 1;
			indexRight = 5;
			indexDown = 7;

			if (previousIndexOfZero != 3) {
				distanceLeft = getNewDistanceToGoal(3, 4, tilesInPuzzle);
			}
			if (previousIndexOfZero != 1) {
				distanceUp = getNewDistanceToGoal(1, 4, tilesInPuzzle);
			}

			if (previousIndexOfZero != 5) {
				distanceRight = getNewDistanceToGoal(5, 4, tilesInPuzzle);
			}

			if (previousIndexOfZero != 7) {
				distanceDown = getNewDistanceToGoal(7, 4, tilesInPuzzle);
			}
		}
		if (indexOfZero == 5) {
			indexLeft = 4;
			indexUp = 2;
			indexDown = 8;

			if (previousIndexOfZero != 4) {
				distanceLeft = getNewDistanceToGoal(4, 5, tilesInPuzzle);
			}

			if (previousIndexOfZero != 2) {
				distanceUp = getNewDistanceToGoal(2, 5, tilesInPuzzle);
			}

			if (previousIndexOfZero != 8) {
				distanceDown = getNewDistanceToGoal(8, 5, tilesInPuzzle);
			}
		}

		if (indexOfZero == 6) {
			indexUp = 3;
			indexRight = 7;

			if (previousIndexOfZero != 3) {
				distanceUp = getNewDistanceToGoal(3, 6, tilesInPuzzle);
			}

			if (previousIndexOfZero != 7) {
				distanceRight = getNewDistanceToGoal(7, 6, tilesInPuzzle);
			}

		}
		if (indexOfZero == 7) {
			indexLeft = 6;
			indexUp = 4;
			indexRight = 8;

			if (previousIndexOfZero != 6) {
				distanceLeft = getNewDistanceToGoal(6, 7, tilesInPuzzle);
			}
			if (previousIndexOfZero != 4) {
				distanceUp = getNewDistanceToGoal(4, 7, tilesInPuzzle);
			}

			if (previousIndexOfZero != 8) {
				distanceRight = getNewDistanceToGoal(8, 7, tilesInPuzzle);
			}

		}
		if (indexOfZero == 8) {
			indexLeft = 7;
			indexUp = 5;

			if (previousIndexOfZero != 7) {
				distanceLeft = getNewDistanceToGoal(7, 8, tilesInPuzzle);
			}

			if (previousIndexOfZero != 5) {
				distanceUp = getNewDistanceToGoal(5, 8, tilesInPuzzle);
			}

		}

		// After getting all the potential distances of the neighbors, the values will saved in an array. ...
		neighbors[0] = distanceLeft;
		neighbors[1] = distanceUp;
		neighbors[2] = distanceRight;
		neighbors[3] = distanceDown;

		// ... Then the smallest of them, which also smaller than the current distance,  will be searched.
		min = sumOfDistances;
		minIndex = -1;
		for (int i = 0; i < 4; i++) {
			if (neighbors[i] != -1 && neighbors[i] < min) {
				min = neighbors[i];
				minIndex = i;
			}
		}

		/* If there is no smaller potential distance than the current distance,
		 * the smallest possible is the best candidate.*/
		if (minIndex == -1) {
			for(int i = 0; i < 4; i++) {
				if (neighbors[i] != -1) {
					min = neighbors[i];
					minIndex = i;
					break;
				}
			}
			if (minIndex != 3) {
				for (int i = 0; i < 4; i++) {
					if (neighbors[i] != -1 && neighbors[i] < min) {
						minIndex = i;
					}
				}
			}
		}

		// The following lines are responsible for swapping the zero tile with its new position.
		if (minIndex == 0) {
			tilesInPuzzle[indexOfZero] = tilesInPuzzle[indexLeft];
			tilesInPuzzle[indexLeft] = 0;
		}

		if (minIndex == 1) {
			tilesInPuzzle[indexOfZero] = tilesInPuzzle[indexUp];
			tilesInPuzzle[indexUp] = 0;
		}

		if (minIndex == 2) {
			tilesInPuzzle[indexOfZero] = tilesInPuzzle[indexRight];
			tilesInPuzzle[indexRight] = 0;
		}

		if (minIndex == 3) {
			tilesInPuzzle[indexOfZero] = tilesInPuzzle[indexDown];
			tilesInPuzzle[indexDown] = 0;
		}

		// Updates the distance after the iteration. Is the goal already reached?
		sumOfDistances = getSumOfDistances(tilesInPuzzle);

		// Update for the zero index history.
		previousIndexOfZero = indexOfZero;

		// Increaments the amount of iterations.
		iteration++;
	}

	// The goal is reached. Now the array, which was used for computation, will be translated back to a puzzle.
	index = 0;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			resultPuzzle[row][column] = tilesInPuzzle[index++];
		}
	}

	// Prints the final puzzle...
	print_puzzle(resultPuzzle);

	// and the amount of iterations.
	cout << "Iterations " << iteration << endl;
}

/* This method is used to check the result of the heuristic function after a potential move.
 * During an iteration it is executed for every possible move. */
int Agent::getNewDistanceToGoal(int indexOfTile, int indexOfZero,
		int tilesInPuzzle[]) {
	int tilesInPuzzleNew[9];
	for (int i = 0; i < 9; i++) {
		tilesInPuzzleNew[i] = tilesInPuzzle[i];
	}
	int tmp = tilesInPuzzleNew[indexOfTile];
	tilesInPuzzleNew[indexOfTile] = tilesInPuzzleNew[indexOfZero];
	tilesInPuzzleNew[indexOfZero] = tmp;

	return getSumOfDistances(tilesInPuzzleNew);
}

// This method looks for the index of the zero tile
int Agent::findZeroTile(int tilesInPuzzle[]) {
	for (int i = 0; i < 9; i++) {
		if (tilesInPuzzle[i] == 0) {
			return i;
		}
	}
}

/* This method represents actually the heuristic function for the Manhattan distance appraoch.
 * It sums up the distances of each tile to their final destination. */
int Agent::getSumOfDistances(int tilesInPuzzle[]) {
	int sumOfDistances = 0;

	int row;
	int column;

	for (int i = 0; i < 9; i++) {
		if (i == 0) {
			row = 0;
			column = 0;
		}
		if (i == 1) {
			row = 0;
			column = 1;
		}
		if (i == 2) {
			row = 0;
			column = 2;
		}
		if (i == 3) {
			row = 1;
			column = 0;
		}
		if (i == 4) {
			row = 1;
			column = 1;
		}
		if (i == 5) {
			row = 1;
			column = 2;
		}
		if (i == 6) {
			row = 2;
			column = 0;
		}
		if (i == 7) {
			row = 2;
			column = 1;
		}
		if (i == 8) {
			row = 2;
			column = 2;
		}

		int current_value = tilesInPuzzle[i];
		if (current_value == 1) {
			sumOfDistances += abs(0 - row) + abs(0 - column);
		}
		if (current_value == 2) {
			sumOfDistances += abs(0 - row) + abs(1 - column);
		}
		if (current_value == 3) {
			sumOfDistances += abs(0 - row) + abs(2 - column);
		}
		if (current_value == 4) {
			sumOfDistances += abs(1 - row) + abs(0 - column);
		}
		if (current_value == 5) {
			sumOfDistances += abs(1 - row) + abs(1 - column);
		}
		if (current_value == 6) {
			sumOfDistances += abs(1 - row) + abs(2 - column);
		}
		if (current_value == 7) {
			sumOfDistances += abs(2 - row) + abs(0 - column);
		}
		if (current_value == 8) {
			sumOfDistances += abs(2 - row) + abs(1 - column);
		}
	}
	return sumOfDistances;
}

void Agent::greedy_search(string heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.
	if (heuristic == "1") {
		misplaced_tiles(puzzle);
	} else {
		manhattan_distance(puzzle);
	}
//>>>>>>> 6d5901b7df3359309f7a29160e3025157c10e35f
}

void Agent::print_puzzle(Puzzle& puzzle) {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}

