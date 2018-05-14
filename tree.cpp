/* Author: Nick Nesbit
 * Date: 2/16/2018
 * CS4300: Project 1
 * Missionaries and Cannibals: tree.cpp
 */

#include "tree.h"

/***************************
 * Tree()                  *
 ***************************/
Tree::Tree() {
	root = NULL;
	count = 0;
}

/****************************
 * ~Tree()                  *
 ****************************/
Tree::~Tree() {
	destroySubTree(root);
}

/*********************************************
 * destroySubTree(TreeNode*)                 *
 *********************************************/
void Tree::destroySubTree(TreeNode *nodePtr) {
	//Recursivley delete nodes
	if (nodePtr) {
		if (nodePtr->children[0])
			destroySubTree(nodePtr->children[0]);
		if (nodePtr->children[1])
			destroySubTree(nodePtr->children[1]);
		if (nodePtr->children[2])
			destroySubTree(nodePtr->children[2]);
		if (nodePtr->children[3])
			destroySubTree(nodePtr->children[3]);
		if (nodePtr->children[4])
			destroySubTree(nodePtr->children[4]);
		//printf("Node %p deleted at depth %d: <%d,%d,%d>\n", nodePtr, nodePtr->depth, nodePtr->state[0], nodePtr->state[1], nodePtr->state[2]);
		delete nodePtr;
	}
}

/**************************************************
 * startDLS(int[3], int[3], int)                  *
 **************************************************/
Tree::TreeNode * Tree::startDLS(int startState[3], int goalState[3],
		int limit) {
	//Create the and insert the root node
	TreeNode *start;
	start = makeNode(startState, 0);
	insertNode(root, start, start->depth);

	//Call the recursive depth limitied search
	return recurDLS(start, goalState, limit);
}

/**************************************************
 * recurDLS(TreeNode*, int[3], int)               *
 **************************************************/
Tree::TreeNode * Tree::recurDLS(TreeNode *currentNode, int goalState[3],
		int limit) {
	//If goal found
	if (goalFound(currentNode->state, goalState) == true) {
		//Push the current state onto the goal stack
		goal.push(currentNode->state);
		//Return currentNode
		return currentNode;
	}

	//Return Node if depth limit reached
	if (limit <= 0)
		return NULL;

	//Define the possible actions
	static int actions[5][3] = { { 1, 0, 1 }, { 2, 0, 1 }, { 0, 1, 1 }, { 0, 2,
			1 }, { 1, 1, 1 } };

	//Array for the state of a child node
	int childState[3] = { 0, 0, 0 };

	//TreeNode objects for a child node and resulting node
	TreeNode *childNode = NULL;
	TreeNode *resultNode = NULL;

	//Muliplier for actions
	int mult = 0;

	//Determine the multiplier
	if (currentNode->depth % 2 == 0)
		mult = -1;
	else
		mult = 1;

	//Iterate over number of actions
	for (int j = 0; j < 5; j++) {
		//Iterate over number of state varibales
		for (int k = 0; k < 3; k++) {
			//Set the child state equal to the current state plus some action
			childState[k] = currentNode->state[k] + mult * actions[j][k];
		}
		//Check if the child state is valid
		if (validState(childState) == true) {
			//Create a new node and insert it into tree
			childNode = makeNode(childState, currentNode->depth + 1);
			insertNode(currentNode, childNode, childNode->depth);

			//Recursivley call the DLS using the new childNode and decrementing the limit
			resultNode = recurDLS(childNode, goalState, limit - 1);

			//Check if goal is found
			if (resultNode != NULL) {
				//Push the current state on the goal stack
				goal.push(currentNode->state);
				//Return the current node
				return currentNode;
			}
		}
	}
	return NULL;
}

/******************************************
 * makeNode(int[3], int)                  *
 ******************************************/
Tree::TreeNode * Tree::makeNode(int state[3], int depth) {
	//Create a new node
	TreeNode *newNode;
	newNode = new TreeNode;

	//Set the state
	newNode->state[0] = state[0];
	newNode->state[1] = state[1];
	newNode->state[2] = state[2];

	//Set the depth and index
	newNode->depth = depth;
	newNode->index = count;
	count++;

	//Initialize the children
	for (int i = 0; i < 5; i++)
		newNode->children[i] = NULL;

	//printf("%p\n", newNode);

	//Return the new node
	return newNode;
}

/*******************************************************
 * insertNode(TreeNode*&, TreeNode*&, int)             *
 *******************************************************/
void Tree::insertNode(TreeNode *&nodePtr, TreeNode *&newNode, int depth) {
	//Recursivley insert a node to the tree
	if (nodePtr == NULL) {
		nodePtr = newNode;
		//printf("Search node: %p, Depth: %d, State: <%d,%d,%d>\n", nodePtr, nodePtr->depth, nodePtr->state[0], nodePtr->state[1], nodePtr->state[2]);
	} else if (nodePtr->children[0] == NULL)
		insertNode(nodePtr->children[0], newNode, ++depth);
	else if (nodePtr->children[1] == NULL)
		insertNode(nodePtr->children[1], newNode, ++depth);
	else if (nodePtr->children[2] == NULL)
		insertNode(nodePtr->children[2], newNode, ++depth);
	else if (nodePtr->children[3] == NULL)
		insertNode(nodePtr->children[3], newNode, ++depth);
	else if (nodePtr->children[4] == NULL)
		insertNode(nodePtr->children[4], newNode, ++depth);
}

/***************************************
 * validState(int[3])                  *
 ***************************************/
bool Tree::validState(int state[3]) {

	//Check if a state is invalid

	if (((state[0] < state[1]) && (state[0] != 0))
			|| ((state[0] > state[1]) && (state[0] != 3)) || ((state[0] > 4))
			|| ((state[1] > 4)) || ((state[0] < 0)) || ((state[1] < 0)))
		return false;

	return true;
}

/*********************************************
 * goalFound(int[3], int[3])                 *
 *********************************************/
bool Tree::goalFound(int state[3], int goal[3]) {
	//Check if a state is equal to the goal state

	for (int i = 0; i < 3; i++)
		if (state[i] != goal[i])
			return false;

	return true;
}

/***********************************
 * getNumNodes()                   *
 ***********************************/
int Tree::getNumNodes() {
	//Return number of nodes in tree
	return count;
}

/**********************************
 * displayGoal()                  *
 **********************************/
void Tree::displayGoal() {
	//Pop the goal stack until it is empty
	while (!goal.empty()) {
		printf("<%d,%d,%d>\n", goal.top()[0], goal.top()[1], goal.top()[2]);
		goal.pop();
	}
}

tree::tree() {
	// TODO Auto-generated constructor stub

}

tree::~tree() {
	// TODO Auto-generated destructor stub
}

