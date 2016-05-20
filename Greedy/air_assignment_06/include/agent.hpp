/*
 * Daniel Vazquez, Kiran Vasudev, Patrick Nagel
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 6
 *
 * agent.hpp
 * */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include <string>
#include <utility> 

#define NUM_COLS 3
#define NUM_ROWS 3

using namespace std;

typedef vector<vector<int> > Puzzle;

class Agent {
public:
	Agent(Puzzle puzzle, string solver, string heuristic);
	~Agent();

	void run();

private:

	vector<vector<int> > puzzle;

	string solver;
	string heuristic;

	void greedy_search(string heuristic);

	int misplaced_tiles(Puzzle puzzle);
	int manhattan_distance(Puzzle puzzle);

	//methods used for misplaced tiles
	int countMisplaced(int elementsInArray[], int size); //returns the number of misplaced tiles
	int indexOfZero(int tiles[], int size);
	void swapValues(int tiles[], int childPosition, int zeroPosition);


	// The following three methods are needed for the Manhattan distance part.
	int getSumOfDistances(int tilesInPuzzle[]);
	int findZeroTile(int tilesInPuzzle[]);
	int getNewDistanceToGoal(int indexOfTile, int indexOfZero, int tilesInPuzzle[]);

	void print_puzzle(Puzzle& puzzle);

};

#endif
