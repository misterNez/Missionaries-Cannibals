/* Author: Nick Nesbit
 * Date: 2/16/2018
 * CS4300: Project 1
 * Missionaries and Cannibals: tree.h
 */

#ifndef TREE_H_
#define TREE_H_

#include <cstddef>
#include <cstdio>
#include <stack>

//Define Tree class structure:
class Tree {
	//Private:
private:
	//Define the tree node structure:
	struct TreeNode {
		int index;					//Unique ID for node.
		int depth;					//Depth of node.
		int state[3];				//State description
		TreeNode *children[5];		//Five possible child nodes.
	};

	//Class variables:
	TreeNode *root;				//Root of search tree.
	int count;					//Keep track of current node number
	std::stack<int *> goal;		//A stack to store the goal path.

	//Tree member functions:
	TreeNode * recurDLS(TreeNode *, int[3], int);
	TreeNode * makeNode(int[3], int);
	void insertNode(TreeNode *&, TreeNode *&, int);
	void destroySubTree(TreeNode *);
	bool goalFound(int[3], int[3]);
	bool validState(int[3]);

	//Public:
public:
	//Tree constructor:
	Tree();

	//Tree destructor:
	~Tree();

	//Tree mutator functions:
	TreeNode * startDLS(int[3], int[3], int);

	//Tree accessor functions:
	int getNumNodes();
	void displayGoal();
};

class tree {
public:
	tree();
	virtual ~tree();
};
#endif

