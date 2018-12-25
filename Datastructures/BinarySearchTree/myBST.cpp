/*
	Ben Sebring
	CPSC 250
	11:00 am class
	Email: bsebring@live.esu.edu
	Description: Driver Program for the BinarySearchTree class
*/

#include "BinarySearchTree.h"
using namespace std;
const int TREE_SIZE = 9;
int main()
{
	// Declaring trees dynamically
	BinarySearchTree *myTree = new BinarySearchTree();
	BinarySearchTree *myTree2 = new BinarySearchTree();

	// initializing the array for BSTsort
	int array[TREE_SIZE] = { 7, 3, 10, 1, 6, 14, 4, 7, 13 };
	cout << "Inserting nodes 7, 3, 10, 1, 6, 14, 7, 13 sequentially" << endl << endl;
	// Inserting the nodes in the proper order
	myTree->insert(myTree->root, 7);
	myTree->insert(myTree->root, 3);
	myTree->insert(myTree->root, 10);
	myTree->insert(myTree->root, 1);
	myTree->insert(myTree->root, 6);
	myTree->insert(myTree->root, 14);
	myTree->insert(myTree->root, 4);
	myTree->insert(myTree->root, 7);
	myTree->insert(myTree->root, 13);

	// Calling inOrder traversal
	cout << "Here are the values in the tree (in-order traversal):\n";
	myTree->inOrder(myTree->root);
	cout << endl << endl;
	// Calling preOrder traversal
	cout << "Here are the values in the tree (pre-order traversal):\n";
	myTree->preOrder(myTree->root);
	cout << endl << endl;
	// Calling postOrder traversal
	cout << "Here are the values in the tree (post-order traversal):\n";
	myTree->postOrder(myTree->root);
	cout << endl << endl;

	// Calling delete 6 and delete 13
	cout << "Deleting 6..." << endl;
	myTree->deleteItem(myTree->root, 6);
	cout << "Deleting 13..." << endl;
	myTree->deleteItem(myTree->root, 13);
	// Calling inOrder traversal
	cout << "\nNow, here are the nodes (in-order traversal):\n";
	myTree->inOrder(myTree->root);
	cout << endl << endl << endl;
	// Checking to see if 14 is in the tree (it should be)
	if (myTree->treeSearch(myTree->root, 14))
		cout << "\nYes, 14 is in the binary tree" << endl << endl;
	else
		cout << "\nNo, 14 is not in the tree." << endl << endl;

	// Calling min
	cout << "The minimum value in the tree is " << myTree->min(myTree->root) << endl << endl;
	// calling BSTsort on a different tree
	cout << "BST Sort: the result of BST Sort for node values is: \n";
	myTree2->BSTsort(myTree2->root, array, TREE_SIZE);
	cout << endl;

	// Clearing dynamically allocated memory for trees.
	delete myTree, myTree2;

	system("pause");
	return 0;
}