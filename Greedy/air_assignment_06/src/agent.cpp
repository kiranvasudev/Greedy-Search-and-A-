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
#include <queue>
#include <algorithm>

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

int Agent::misplaced_tiles(Puzzle puzzle) {
	//TODO
}

int Agent::manhattan_distance(Puzzle puzzle) {

	int previousIndexOfZero = 0;
	int indexOfZero;
	int tilesInPuzzle[9];

	int index = 0;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			tilesInPuzzle[index++] = puzzle[row][column];
		}
	}

	// variable for sum of distances
	int sumOfDistances = getSumOfDistances(tilesInPuzzle);

	// variables to save the difference between current and possible new state
	int diffRight;
	int diffLeft;
	int diffUp;
	int diffDown;

	int indexRight;
	int indexLeft;
	int indexUp;
	int indexDown;

	int min;
	int minIndex;

	int neighbors[4];

	Puzzle tmpPuzzle(8, std::vector<int>(8, 0));

	int iteration = 0;
	while (sumOfDistances != 0) {
		// resets the values for current iteration
		diffRight = -1;
		diffLeft = -1;
		diffUp = -1;
		diffDown = -1;

		indexRight = -1;
		indexLeft = -1;
		indexUp = -1;
		indexDown = -1;

		indexOfZero = findZeroTile(tilesInPuzzle);

		if (indexOfZero == 0) {
			indexRight = 1;
			indexDown = 3;

			if (previousIndexOfZero != 1) {
				diffRight = getNewDistanceToGoal(1, 0, tilesInPuzzle);
			}

			if (previousIndexOfZero != 3) {
				diffDown = getNewDistanceToGoal(3, 0, tilesInPuzzle);
			}

		}
		if (indexOfZero == 1) {
			indexLeft = 0;
			indexRight = 2;
			indexDown = 4;

			if (previousIndexOfZero != 0) {
				diffLeft = getNewDistanceToGoal(0, 1, tilesInPuzzle);
			}

			if (previousIndexOfZero != 2) {
				diffRight = getNewDistanceToGoal(2, 1, tilesInPuzzle);
			}

			if (previousIndexOfZero != 4) {
				diffDown = getNewDistanceToGoal(4, 1, tilesInPuzzle);
			}
		}
		if (indexOfZero == 2) {
			indexLeft = 1;
			indexDown = 5;

			if (previousIndexOfZero != 1) {
				diffLeft = getNewDistanceToGoal(1, 2, tilesInPuzzle);
			}

			if (previousIndexOfZero != 5) {
				diffDown = getNewDistanceToGoal(5, 2, tilesInPuzzle);
			}
		}

		if (indexOfZero == 3) {
			indexUp = 0;
			indexRight = 4;
			indexDown = 6;

			if (previousIndexOfZero != 0) {
				diffUp = getNewDistanceToGoal(0, 3, tilesInPuzzle);
			}

			if (previousIndexOfZero != 4) {
				diffRight = getNewDistanceToGoal(4, 3, tilesInPuzzle);
			}

			if (previousIndexOfZero != 6) {
				diffDown = getNewDistanceToGoal(6, 3, tilesInPuzzle);
			}
		}
		if (indexOfZero == 4) {
			indexLeft = 3;
			indexUp = 1;
			indexRight = 5;
			indexDown = 7;

			if (previousIndexOfZero != 3) {
				diffLeft = getNewDistanceToGoal(3, 4, tilesInPuzzle);
			}
			if (previousIndexOfZero != 1) {
				diffUp = getNewDistanceToGoal(1, 4, tilesInPuzzle);
			}

			if (previousIndexOfZero != 5) {
				diffRight = getNewDistanceToGoal(5, 4, tilesInPuzzle);
			}

			if (previousIndexOfZero != 7) {
				diffDown = getNewDistanceToGoal(7, 4, tilesInPuzzle);
			}
		}
		if (indexOfZero == 5) {
			indexLeft = 4;
			indexUp = 2;
			indexDown = 8;

			if (previousIndexOfZero != 4) {
				diffLeft = getNewDistanceToGoal(4, 5, tilesInPuzzle);
			}

			if (previousIndexOfZero != 2) {
				diffUp = getNewDistanceToGoal(2, 5, tilesInPuzzle);
			}

			if (previousIndexOfZero != 8) {
				diffDown = getNewDistanceToGoal(8, 5, tilesInPuzzle);
			}
		}

		if (indexOfZero == 6) {
			indexUp = 3;
			indexRight = 7;

			if (previousIndexOfZero != 3) {
				diffUp = getNewDistanceToGoal(3, 6, tilesInPuzzle);
			}

			if (previousIndexOfZero != 7) {
				diffRight = getNewDistanceToGoal(7, 6, tilesInPuzzle);
			}

		}
		if (indexOfZero == 7) {
			indexLeft = 6;
			indexUp = 4;
			indexRight = 8;

			if (previousIndexOfZero != 6) {
				diffLeft = getNewDistanceToGoal(6, 7, tilesInPuzzle);
			}
			if (previousIndexOfZero != 4) {
				diffUp = getNewDistanceToGoal(4, 7, tilesInPuzzle);
			}

			if (previousIndexOfZero != 8) {
				diffRight = getNewDistanceToGoal(8, 7, tilesInPuzzle);
			}

		}
		if (indexOfZero == 8) {
			indexLeft = 7;
			indexUp = 5;

			if (previousIndexOfZero != 7) {
				diffLeft = getNewDistanceToGoal(7, 8, tilesInPuzzle);
			}

			if (previousIndexOfZero != 5) {
				diffUp = getNewDistanceToGoal(5, 8, tilesInPuzzle);
			}

		}

		neighbors[0] = diffLeft;
		neighbors[1] = diffUp;
		neighbors[2] = diffRight;
		neighbors[3] = diffDown;

		min = sumOfDistances;
		minIndex = -1;
		for (int i = 0; i < 4; i++) {
			if (neighbors[i] != -1 && neighbors[i] < min) {
				min = neighbors[i];
				minIndex = i;
			}
		}

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

		sumOfDistances = getSumOfDistances(tilesInPuzzle);

		previousIndexOfZero = indexOfZero;

		iteration++;
	}
	cout << "Iterations " << iteration << endl;
	cout << "Success" << endl;

	index = 0;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			tmpPuzzle[row][column] = tilesInPuzzle[index++];
		}
	}

	print_puzzle(tmpPuzzle);
}

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

int Agent::getDistanceToGoal(int newPossiblePosition, int tile) {
	int distance;
	int row;
	int column;

	if (newPossiblePosition == 0) {
		row = 0;
		column = 0;
	}
	if (newPossiblePosition == 1) {
		row = 0;
		column = 1;
	}
	if (newPossiblePosition == 2) {
		row = 0;
		column = 2;
	}
	if (newPossiblePosition == 3) {
		row = 1;
		column = 0;
	}
	if (newPossiblePosition == 4) {
		row = 1;
		column = 1;
	}
	if (newPossiblePosition == 5) {
		row = 1;
		column = 2;
	}
	if (newPossiblePosition == 6) {
		row = 2;
		column = 0;
	}
	if (newPossiblePosition == 7) {
		row = 2;
		column = 1;
	}
	if (newPossiblePosition == 8) {
		row = 2;
		column = 2;
	}

	int current_value = tile;
	if (current_value == 1) {
		distance += abs(0 - row) + abs(0 - column);
	}
	if (current_value == 2) {
		distance += abs(0 - row) + abs(1 - column);
	}
	if (current_value == 3) {
		distance += abs(0 - row) + abs(2 - column);
	}
	if (current_value == 4) {
		distance += abs(1 - row) + abs(0 - column);
	}
	if (current_value == 5) {
		distance += abs(1 - row) + abs(1 - column);
	}
	if (current_value == 6) {
		distance += abs(1 - row) + abs(2 - column);
	}
	if (current_value == 7) {
		distance += abs(2 - row) + abs(0 - column);
	}
	if (current_value == 8) {
		distance += abs(2 - row) + abs(1 - column);
	}

	return distance;
}

int Agent::findZeroTile(int tilesInPuzzle[]) {
	for (int i = 0; i < 9; i++) {
		if (tilesInPuzzle[i] == 0) {
			return i;
		}
	}
}

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
}

void Agent::print_puzzle(Puzzle& puzzle) {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}

