 /*
	 Ben Sebring
	 CPSC 250
	 11:00 am class
	 Email: bsebring@live.esu.edu
	 Description: Implementation file for the BinarySearchTree class 
 */

#include "BinarySearchTree.h"
using namespace std;
const int TREE_SIZE = 9;

// Constructor that sets root to NULL
BinarySearchTree::BinarySearchTree()
{
	root = NULL;
}

// Destructor method that deletes the root pointer
BinarySearchTree::~BinarySearchTree()
{
	delete root;
}

/********************************************************
void BinarySearchTree::insert(TreeNode *& tree, int item)
Parameters:
	TreeNode *& tree: reference to a TreeNode pointer (root to start)
	int item: the integer value to be inserted 
		into a TreeNode
Description: By using recursion, this function
	determines the proper location to place a value into the tree.
Return: none, void function
********************************************************/
void BinarySearchTree::insert(TreeNode *& tree, int item)
{
	//Base case, or proper location for item
	if (tree == NULL)
	{// If there is no node, make one, set left and right to null, and info to item
		tree = new TreeNode;
		tree->info = item;
		tree->left = NULL;
		tree->right = NULL;
	}
	else if (item < tree->info)
	{
		// Go to the left if item < info
		insert(tree->left, item);
	}
	else
	{
		// Go to the right if item > info
		insert(tree->right, item);
	}
}

/********************************************************
bool BinarySearchTree::treeSearch(TreeNode *node, int key)
Parameters:
	TreeNode *node: TreeNode pointer (root to start)
	int key: the value to search for
Description: Recursively searches the tree for key
	Base case:
		node == NULL or key == node->info
Return: True/False depending if key is in the tree
********************************************************/
bool BinarySearchTree::treeSearch(TreeNode *node, int key)
{
	if (node == NULL)
	{// The item is not there if the tree is empty
		return false;
	}
	else if (key == node->info)
	{// Return true if item is found
		return true;
	}
	else if (key < node->info)
	{// Go to the left if item < info
		return treeSearch(node->left, key);
	}
	else
	{// Go to the right if item > info
		return treeSearch(node->right, key);
	}

}

/********************************************************
void BinarySearchTree::deleteItem(TreeNode*& tree, int item)
Parameters:
	TreeNode*& tree: reference to a TreeNode pointer
	int item: item to be deleted
Description: Searches the tree for item recursively and 
	calls deleteNode, to remove it; 
	base case is:
		treeSearch == false
Return: none, void
********************************************************/
void BinarySearchTree::deleteItem(TreeNode*& tree, int item)
{
	if (treeSearch(tree, item))
	{
		if (tree->info == item)
			deleteNode(tree); // Delete the node
		else if (tree->info > item)
			deleteItem(tree->left, item); // Go left
		else
			deleteItem(tree->right, item); // Go right
	}
}

/********************************************************
void BinarySearchTree::deleteNode(TreeNode *& tree)
Parameters:
	TreeNode *& tree:  reference to a TreeNode pointer
Description: Deletes a node while maintaining BST properties
Return: none, void
********************************************************/
void BinarySearchTree::deleteNode(TreeNode *& tree)
{
	if (!tree->left && !tree->right)
	{// N has no children
		// Break the link (delete node N)
		tree = NULL;
	}
	else if ((tree->left && !tree->right) || (!tree->left && tree->right))
	{ // N has 1 child
		if (tree->left)
		{
			// make C the left child of P
			tree->info = tree->left->info;
			tree->left = NULL;
		}
		else // N is a right child
		{
			// make C the right child of P
			tree->info = tree->right->info;
			tree->right = NULL;
		}
	}
	else
	{ // N has 2 Children
		// find the left most node in the right subtree of tree
		getInorderSuccessor(tree, tree->info);
	}

}

/********************************************************
void BinarySearchTree::getInorderSuccessor(TreeNode* tree, int& item)
Parameters:
	TreeNode* tree: TreeNode pointer
	int& item: item to replace
Description: finds the next largest number in the tree
Return: none, void
********************************************************/
void BinarySearchTree::getInorderSuccessor(TreeNode* tree, int& item)
{
	if (tree->right)
		item = min(tree->right);
}

/********************************************************
void BinarySearchTree::preOrder(TreeNode *tree)
Parameters:
	TreeNode *tree: TreeNode pointer
Description: preOrder(root, left,right) traversal 
	of a tree
Return: none, void
********************************************************/
void BinarySearchTree::preOrder(TreeNode *tree)
{
	if (tree != NULL)
	{
		cout << tree->info << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}

}

/********************************************************
void BinarySearchTree::inOrder(TreeNode *tree)
Parameters:
	TreeNode *tree: TreeNode pointer
Description: inOrder traversal, returns the values in ascending order
Return: none, void
********************************************************/
void BinarySearchTree::inOrder(TreeNode *tree)
{
	if(tree != NULL)
	{
		inOrder(tree->left);
		cout << tree->info << " ";
		inOrder(tree->right);
	}
}

/********************************************************
void BinarySearchTree::postOrder(TreeNode *tree)
Parameters:
	TreeNode *tree: TreeNode pointer
Description: postOrder(left,right, root) traversal
	of a tree
Return: none, void
********************************************************/
void BinarySearchTree::postOrder(TreeNode *tree)
{
	if (tree != NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->info << " ";
	}
}

/********************************************************
bool BinarySearchTree::empty() const
Parameters: none
Description: Checks to see if the tree is empty
Return: True if tree is empty, false otherwise 
********************************************************/
bool BinarySearchTree::empty() const
{
	if (root == NULL)
		return true;
	else
		return false;
}

/********************************************************
int BinarySearchTree::min(TreeNode * root)
Parameters: 
	TreeNode * root: TreeNode Pointer
Description: Recursively finds the min value
	in a tree
Return: the minimum value of the tree
********************************************************/
int BinarySearchTree::min(TreeNode * root)
{
	while (root->left)
		root = root->left;
	return root->info;
}

/********************************************************
void BinarySearchTree::BSTsort(TreeNode* &tree, int A[], int size)
Parameters:
	TreeNode* tree: reference to a TreeNode pointer
	int A[]: an array of integers
	int size: size of the array
Description: Sorts an array or integers into a tree
	using insert
Return: none, void
********************************************************/
void BinarySearchTree::BSTsort(TreeNode* tree, int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		insert(tree, array[i]);
	}
	inOrder(tree);
}