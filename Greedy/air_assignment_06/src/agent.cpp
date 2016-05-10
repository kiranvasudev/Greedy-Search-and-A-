/*
 * Daniel Vazquez
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
		greedy_search (heuristic);
	}

}

int Agent::misplaced_tiles(Puzzle puzzle) {
	//TODO

}

int Agent::manhattan_distance(Puzzle puzzle) {
	//TODO
}

void Agent::greedy_search(string heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.

}

void Agent::print_puzzle(Puzzle& puzzle) {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}

