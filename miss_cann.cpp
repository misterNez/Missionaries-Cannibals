/* Author: Nick Nesbit
 * Date: 2/16/2018
 * CS4300: Project 1
 * Missionaries and Cannibals: miss_cann.cpp
 */

#include "tree.h"

//Start of program.
int main() {
	//Static variables:
	static int startState[3] = {3, 3, 1};
	static int goalState[3] = {0, 0, 0};
	static int maxDepth = 0;
	static bool found = false;

	//Iterative deepening loop starts here.
	while (maxDepth < 12 && !found) {

		//Create a new Tree object.
		Tree *tree;
		tree = new Tree();

		//Perform a depth-limited search with the current max depth.
		if (tree->startDLS(startState, goalState, maxDepth) != NULL) {
			//If solution found:
			found = true;
			printf("Depth Search %d: Goal found: %d nodes searched.\n", maxDepth, tree->getNumNodes());
			tree->displayGoal();
		}
		else
			//If solution not found:
			printf("Depth Search %d: Goal not found: %d nodes searched.\n", maxDepth, tree->getNumNodes());

		//Delete the tree.
		delete tree;

		printf("\n");

		//Increment max depth.
		maxDepth++;
	}
	//End of iterative deepening loop.

	return 0;
}
//End of program.
