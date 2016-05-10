/*
 * Daniel Vazquez
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

	void print_puzzle(Puzzle& puzzle);

};

#endif
