/*
Header file for the BinarySearchTree class
*/
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>

class BinarySearchTree
{
private:
	struct TreeNode
	{
		int info;
		TreeNode * left;
		TreeNode * right;
	};

public:
	TreeNode * root;

	BinarySearchTree();
	~BinarySearchTree();
	void insert(TreeNode *& tree, int item);
	bool treeSearch(TreeNode *node, int key);
	void deleteItem(TreeNode*& tree, int item);
	void deleteNode(TreeNode *& tree);
	void getInorderSuccessor(TreeNode* tree, int& item);
	void preOrder(TreeNode *tree);
	void inOrder(TreeNode *tree);
	void postOrder(TreeNode *tree);
	bool empty() const;
	int min(TreeNode * root);
	void BSTsort(TreeNode* tree, int array[], int size);
};
#endif