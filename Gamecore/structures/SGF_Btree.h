/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#ifndef _S_G_F_Binary_Tree_h_
#define _S_G_F_Binary_Tree_h_

#include "../exceptions/all.h"
#include "../util/SGF_Debug.h"
using namespace std;
namespace SGF {

// Este código teve como base o seguinte tutorial:
// http://www.bogotobogo.com/cplusplus/binarytree.php
/**
 * \class CBinaryTree
 *
 * \ingroup SGF_Data_Structures
 *
 * \brief Arvore Binária de Busca Genérica
 *
 * \ note este código foi adaptado e alterado da seguinte base :http://www.bogotobogo.com/cplusplus/binarytree.php
 * \ note ItemType deve ter implementado os operadores de atribuição "=" ">" e "<" para este template funcionar
 * \ note  Código não testado!!!!
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 14 de Janeiro de 2012
 */


template <class ItemType>
struct TreeNode
 {
    TreeNode(const ItemType &_data):
    data(_data), left(NULL),right(NULL),parent(NULL){}
    TreeNode():left(NULL),right(NULL),parent(NULL){}
    ItemType data;
    TreeNode<ItemType> *left;
    TreeNode<ItemType> *right;
    TreeNode<ItemType> *parent;
};

template <class ItemType>
class CBinaryTree {
public:
	CBinaryTree():
	main_root(NULL),
	isItemNotFoundSetted(false),
	subtree(false){};
	//The job of the class destructor is to delete all the nodes, and free up memory as usual.
	 //The clear() function is called just as in the previous data structure implementations. However, this operation is only performed if the object is a main tree. If the object is a subtree that points to the nodes of a larger tree, it will be deleted when the main tree itself is deleted. Attempting to delete the data in the memory associated with the subtree after it has already been deleted by the main tree will have unpredictable results.
	 virtual ~CBinaryTree()
	 {
		if(!subtree)
		   clear(); //delete all nodes
	 };
	CBinaryTree(ItemType item):
	main_root(NULL),
	isItemNotFoundSetted(false),
	subtree(false){
			newTreeNode(item);
	};

void setItemNotFound(ItemType key)
{
	ITEM_NOT_FOUND=key;
	isItemNotFoundSetted=true;
}

ItemType lookUpItem(ItemType key)
{
	if(!this->isItemNotFoundSetted) {

		Debug::debug(Debug::error,__FUNCTION__) << "ITEN_NOT_FOUND Not Initialized. Initialize it before using this method" << endl;
		throw CGeneralError("ITEN_NOT_FOUND Not Initialized. Initialize it before using this method",__FUNCTION__,__LINE__);

	}
		TreeNode<ItemType> *node= lookUp(main_root,key);
		if(node) return node->data;
		else return ITEM_NOT_FOUND;
};

TreeNode<ItemType>* lookUp(ItemType key)
{
	return lookUp(main_root,key);
};
TreeNode<ItemType>* lookUp(TreeNode<ItemType> *node, ItemType key)
{
	if(node == NULL) return node;

	if(node->data == key) return node;
	else {
		if(node->data < key)
			return lookUp(node->right, key) ;
		else
			return lookUp(node->left, key);
	}
};

TreeNode<ItemType>* leftMost()
{
	return leftMost(main_root);
};

TreeNode<ItemType>* leftMost(TreeNode<ItemType> *node)
{
	if(node == NULL) return NULL;
	while(node->left != NULL)
		node = node->left;
	return node;
};

TreeNode<ItemType>* rightMost()
{
	return rightMost(main_root);
};

TreeNode<ItemType>* rightMost(TreeNode<ItemType> *node)
{
	if(node == NULL) return NULL;
	while(node->right != NULL)
		node = node->right;
	return node;
};

TreeNode<ItemType> *newTreeNode(ItemType data)
{
	TreeNode<ItemType> *node = new TreeNode<ItemType>(data);
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	if(main_root==NULL) main_root = node;
	return node;
};

TreeNode<ItemType>* insertTreeNode(ItemType data)
{
	return insertTreeNode(main_root,data);
};


TreeNode<ItemType>* insertTreeNode(TreeNode<ItemType> *node, ItemType data)
{
	static TreeNode<ItemType> *p=NULL;
	TreeNode<ItemType> *retNode;

	//if(node != NULL) p = node;

	if(node == NULL)  { // deve ser o primeiro nó da árvore
	    retNode = newTreeNode(data);
	    retNode->parent = p;
	    if (main_root==NULL) main_root=retNode;
		return retNode;
	}
	if(data <= node->data ) {
		p = node;
		node->left = insertTreeNode(node->left,data);
	}
	else {
		p = node;
		node->right = insertTreeNode(node->right,data);
	}
	return node;
};
//! retorna verdadeiro se a árvore for uma Binary Search Tree
bool isBST()
{
	return isBST(main_root);
};

//return true if is a BST
bool isBST(TreeNode<ItemType> *node)
{
     static ItemType lastData;
     if(node == NULL) return false;

      if((lastData =findMinValue) == ITEM_NOT_FOUND) return false;
      else {
	 
	  isBST(node->left);

	  /* check if the given tree is BST */
	  if(lastData < node->data)
		  lastData = node->data;
	  else {
		  return false;
	  }

	  isBST(node->right);
	  return true;
	}
};

ItemType findMinValue() {
  if (treeSize()==0) return ITEM_NOT_FOUND;
  else {
    TreeNode<ItemType> * node = main_root;
    if (node ==NULL) return ITEM_NOT_FOUND;
    ItemType value1 = main_root->data;
    ItemType value2 = main_root->data;
    if (value1==ITEM_NOT_FOUND) return ITEM_NOT_FOUND;
    value1 = findMin(node->left, value1);
    value2 = findMin(node->right, value2);
    return (value1 <= value2 ? value1:value2);
  }
}

ItemType findMin(TreeNode<ItemType> * node, ItemType value1) {
  if (node ==NULL) return ITEM_NOT_FOUND;
  if (value1== ITEM_NOT_FOUND) return ITEM_NOT_FOUND;
  ItemType value2 = node->data;
  if (value2== ITEM_NOT_FOUND) return ITEM_NOT_FOUND;
  return (value1 <= value2 ? value1:value2);
}

int treeSize()
{
	if(main_root == NULL) return 0;
	else
		return treeSize(main_root);
};

int treeSize(TreeNode<ItemType> *node)
{
	if(node == NULL) return 0;
	else
		return treeSize(node->left) + 1 + treeSize(node->right);
};

int maxDepth()
{
	return maxDepth(main_root);
}

int maxDepth(TreeNode<ItemType> *node)
{
	if(node == NULL || (node->left == NULL && node->right == NULL)) return 0;

	int leftDepth = maxDepth(node->left);
	int rightDepth = maxDepth(node->right);

	return leftDepth > rightDepth ?
				leftDepth + 1 : rightDepth + 1;
};

int minDepth()
{
	return minDepth(main_root);
};

int minDepth(TreeNode<ItemType> *node)
{
	if(node == NULL || (node->left == NULL && node->right == NULL)) return 0;

	int leftDepth = minDepth(node->left);
	int rightDepth = minDepth(node->right);

	return leftDepth < rightDepth ?
				leftDepth + 1 : rightDepth + 1;
};

bool isBalanced()
{
	return isBalanced(main_root);
}

bool isBalanced(TreeNode<ItemType> *node)
{
	if(maxDepth(node)-minDepth(node) <= 1)
		return true;
	else
		return false;
};

/* CBinaryTree Minimum */
TreeNode<ItemType>* minTree()
{
	return minTree(main_root);
};

//retorna o elemento Mais à esqueda da àrvore
TreeNode<ItemType>* minTree(TreeNode<ItemType> *node)
{
	if(node == NULL) return NULL;
	while(node->left)
		node = node -> left;
	return node;
};

/* CBinaryTree Maximum */
//retorna o elemento Mais à direita da àrvore
TreeNode<ItemType>* maxTree()
{
	return maxTree(main_root);
}

TreeNode<ItemType>* maxTree(TreeNode<ItemType> *node)
{
	while(node->right)
		node = node -> right;
	return node;
};

/* In Order Successor - a node which has the next higher key */
TreeNode<ItemType> *succesorInOrder(TreeNode<ItemType> *node)
{
	/* if the node has right child, seccessor is CBinaryTree-Minimum */
	if(node->right != NULL) return minTree(node->right);

	TreeNode<ItemType> *y = node->parent;
	while(y != NULL && node == y->right) {
		node = y;
		y = y->parent;
	}
	return y;
};

/* In Order Predecessor - a node which has the next lower key */
TreeNode<ItemType> *predecessorInOrder(TreeNode<ItemType> *node)
{
	/* if the node has left child, predecessor is CBinaryTree-Maximum */
	if(node->left != NULL) return maxTree(node->left);

	TreeNode<ItemType> *y = node->parent;
	/* if it does not have a left child,
	predecessor is its first left ancestor */
	while(y != NULL && node == y->left) {
		node = y;
		y = y->parent;
	}
	return y;
};

TreeNode<ItemType> *lowestCommonAncestor(TreeNode<ItemType> *p, TreeNode<ItemType> *q)
{
	return lowestCommonAncestor(main_root,p,q);

}
TreeNode<ItemType> *lowestCommonAncestor(TreeNode<ItemType> *root, TreeNode<ItemType> *p, TreeNode<ItemType> *q)
{
	TreeNode<ItemType> *left, *right;
	if(root == NULL) return NULL;
	if(root->left == p || root->left == q
		|| root->right == p || root->right == q) return root;
	else {
		left = lowestCommonAncestor(root->left,p,q);
		right = lowestCommonAncestor(root->right, p,q);
		if(left && right)
			return root;
		else
			return (left) ? left : right;
	}
};
void clear()
{
clear(main_root);
};
void clear(TreeNode<ItemType> *node)
{
	if(node != NULL) {
		clear(node->left);
		clear(node->right);
		delete node;
	}
};
/* print tree in order */
/* 1. Traverse the left subtree.
   2. Visit the root.
   3. Traverse the right subtree.
*/
void printTreeInOrder()
{
	printTreeInOrder(main_root);
}
void printTreeInOrder(TreeNode<ItemType> *node)
{
	
	if(node == NULL) return;

	printTreeInOrder(node->left);
	cout << node->data << " ";
	printTreeInOrder(node->right);
};

/* print tree in postorder*/
/* 1. Traverse the left subtree.
   2. Traverse the right subtree.
   3. Visit the root.
*/

void printTreePostOrder()
{
	printTreePostOrder(main_root);
}
void printTreePostOrder(TreeNode<ItemType> *node)
{
	if(node == NULL) return;

	printTreePostOrder(node->left);
	printTreePostOrder(node->right);
	cout << node->data << " ";
};

/* print in preorder */
/* 1. Visit the root.
   2. Traverse the left subtree.
   3. Traverse the right subtree.
*/

void printTreePreOrder()
{
	printTreePreOrder(main_root);
}
void printTreePreOrder(TreeNode<ItemType> *node)
{
	if(node == NULL) return;

	cout << node->data << " ";
	printTreePreOrder(node->left);
	printTreePreOrder(node->right);
};

/* printing array */
void printThisPath(int path[], int n)
{
	for(int i = 0; i < n; i++)
		cout << (ItemType)path[i] << " ";
	cout << endl;
};

/* recursion routine to find path */
void pathFinder(TreeNode<ItemType> *node, int path[], int pathLength)
{
	if(node == NULL) return;
	path[pathLength++] = node->data;

	/* Leaf node is the end of a path.
	   So, let's print the path */
	if(node->left == NULL && node->right == NULL)
		printThisPath(path, pathLength);
	else {
		pathFinder(node->left, path, pathLength);
		pathFinder(node->right, path, pathLength);
	}
};

/*printing all paths :
Given a binary tree, print out all of its root-to-leaf
paths, one per line. Uses a recursive helper to do the work. */

void printAllPaths()
{
	printAllPaths(main_root);
}
void printAllPaths(TreeNode<ItemType> *root)
{
	int path[100];
	pathFinder(root,path,0);
};

bool matchTree(TreeNode<ItemType> *r1, TreeNode<ItemType> *r2)
{
	/* Nothing left in the subtree */
	if(r1 == NULL && r2 == NULL)
		return true;
	/* Big tree empty and subtree not found */
	if(r1 == NULL || r2 == NULL)
		return false;
	/* Not matching */
	if(r1->data != r2->data)
		return false;
	return (matchTree(r1->left, r2->left) &&
			matchTree(r1->right, r2->right));
};

bool subTree(TreeNode<ItemType> *r1, TreeNode<ItemType> *r2)
{
	/*Big tree empty and subtree not found */
	if(r1 == NULL)
		return false;
	if(r1->data == r2->data)
		if(matchTree(r1, r2)) return true;
	return (subTree(r1->left, r2) || subTree(r1->right, r2));
};

bool isSubTree( TreeNode<ItemType> *r2)
{
	return isSubTree(main_root,r2);
};

bool isSubTree(TreeNode<ItemType> *r1, TreeNode<ItemType> *r2)
{
	/* Empty tree is subtree */
	if(r2 == NULL)
		return true;
	else
		return subTree(r1, r2);
};

/* change a tree so that the roles of the left
and right hand pointers are swapped at every node */
void mirror()
{
	mirror(main_root);
};

void mirror(TreeNode<ItemType> *r)
{
	if(r == NULL) return;

	TreeNode<ItemType> *tmp;
	mirror(r->left);
	mirror(r->right);

	/* swap pointers */
	tmp = r->right;
	r->right = r->left;
	r->left = tmp;
};

/* create a new tree from a sorted array */
TreeNode<ItemType> *addToBST(ItemType arr[], int start, int end)
{
	if(end < start) return NULL;
	int mid = (start + end)/2;

	TreeNode<ItemType> *r = new TreeNode<ItemType>;
	r->data = arr[mid];
	r->left = addToBST(arr, start, mid-1);
	r->right = addToBST(arr, mid+1, end);
	return r;
};

TreeNode<ItemType> *createMinimalBST(ItemType arr[], int size)
{
	return addToBST(arr,0,size-1);
};

// The IsEmpty() function works by evaluating main_root. If there aren't any nodes in the tree, main_root points to NULL.
bool isEmpty() const
	 {
		return (main_root == NULL);
	 };
/* Breadth first traversal using queue */
void BreadthFirstTraversal(TreeNode<ItemType> *root)
{
	if (root == NULL) return;
	deque <TreeNode<ItemType> *> queue;
	queue.push_back(root);

	while (!queue.empty()) {
		TreeNode<ItemType> *p = queue.front();
		cout << p->data << " ";
		queue.pop_front();

		if (p->left != NULL)
			queue.push_back(p->left);
		if (p->right != NULL)
			queue.push_back(p->right);
	}
	cout << endl;
};

/* find n-th max node from a tree */
void NthMax()
{
	NthMax(main_root);
};
void NthMax(TreeNode<ItemType>* t)
{
	static int n_th_max = 5;
	static int num = 0;
	if(t == NULL) return;
	NthMax(t->right);
	num++;
	if(num == n_th_max)
		cout << n_th_max << "-th maximum data is " << t->data << endl;
	NthMax(t->left);
};

/* Converting a BST into an Array */

void TreeToArray(int a[]){
	TreeToArray(main_root,a);
};

void TreeToArray(TreeNode<ItemType> *node, int a[]){
	static int pos = 0;

	if(node){
		TreeToArray(node->left,a);
		a[pos++] = node->data;
		TreeToArray(node->right,a);
      }
};

private:

	TreeNode<ItemType> *main_root;
	bool subtree;
	ItemType ITEM_NOT_FOUND;
	bool isItemNotFoundSetted;
};

} //end SGF
#endif
