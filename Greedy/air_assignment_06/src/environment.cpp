/*
 * Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 6
 *
 * env.cpp
 * */

#include "environment.hpp"
#include "agent.hpp"

#include <iostream>
#include <stdlib.h>
#include <map>
#include <time.h>

Environment::Environment() :
		puzzle(8, std::vector<int>(8, 0)) {

}

void Environment::run() {

	string cont = "1";
	string solver = "1";
	string heuristic = "1";

	while (cont == "1") {
		cout << "8-Puzzle Solver: " << endl;
		cout << "Select heuristic: " << endl;
		cout << "(1) Misplaced tiles (2) Manhattan distance" << endl;
		cin >> heuristic;

		generate_puzzle();
		print_puzzle();
		Agent anAgent(puzzle, solver, heuristic);
		anAgent.run();

		cout << "Search again: " << endl;
		cout << "(1) Yes (2) No " << endl;
		cin >> cont;
	}

}

void Environment::generate_puzzle() {
	std::map<int, int> numbers;
	int rand_number;
	bool inserted = false;
	srand((unsigned) time(NULL));

	int array[] = { 0, 5, 3, 4, 2, 7, 8, 6, 1 };
	int index = 0;
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			inserted = false;
			puzzle[rows][cols] = array[index++];
		}
	}

}

void Environment::print_puzzle() {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}

