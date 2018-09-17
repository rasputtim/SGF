#ifndef _S_G_F_Binary_Tree_h
#define _S_G_F_Binary_Tree_h

/*

Binary Trees

 Binary trees are different from the three previous structures we have covered before. Lists, stacks, and queues were all linear structures, that is, the elements in them were logically following each other.

 A binary tree structure contains a root node, which is the first in the structure. The root points to one or two other nodes, its left and right children. The root is considered to be a parent of these two nodes. Each child is also a sub-tree, since it can have one or two children of its own. If a node has no children, it is referred to as a leaf node.

 Each node in the tree also has a level associated with it. The root node is at level 0, and increases with each row of nodes below the root.

 Binary trees have many different basic implementations. An array implementation is often times used, where every level must be completely filled. In larger trees, this can be a very big waste of space. For our demonstration, we will create a generic class using dynamic memory allocation. This particular implementation was created by the author using a mixture of possible approaches. It is very effective in explaining the concepts behind binary trees.

 The binary tree class gives the programmer complete control over the tree. Nodes may be removed and inserted into any location in the list. The class allows the user to traverse the tree by keeping a current pointer, just as in the linked list class. The programmer can then use the functions left(), right(), and parent() to move from one node to another. The class also allows the user to display the tree in in-order, post-order, and pre-order. The "order" refers to how the nodes are displayed. For instance, in pre-order, a node's value is displayed, then the value of its left child, followed by the right child. In the case of in-order, the node's value is displayed between the value of its left and right child. In post order, the node's children are displayed before it. The implementation for the binary tree class is displayed below. Although it may look intimidating at first, the code is very easy to follow. The purpose and code behind each function is explained following the definition. You will note, most functions are programmed using recursion. Since each node is actually a tree within itself, using recursion is the easiest approach

 Many books make a class for a single node, and use it to implement the tree. However, we will separate the structure for each node and the entire tree to conserve overhead processing time. Each time a node is created, much less time and memory is used than when a whole tree structure is made. Each node will store a value, and pointers to its children and parent. These will be used and modified by the general tree class.
 */

 #include "../exceptions/all.h"

using namespace std;
namespace SGF {

/**
 * \class CBinaryTree
 *
 * \ingroup SGF_Data_Structures
 * 
 * \brief Arvore Binária de Busca Genérica
 *
 * \ note este código foi adaptado e alterado da seguinte base :http://library.thinkquest.org/C005618/text/heaps.htm
 * \ note ItemType deve ter implementado o operador assignment para este template funcionar
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 14 de Janeiro de 2012
 */
// BinarySearchTree class
        //
        // CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // ItemType find( x )   --> Return item that matches x
        // ItemType findMin( )  --> Return smallest item
        // ItemType findMax( )  --> Return largest item
        // boolean isEmpty( )     --> Return true if empty; else false
		// boolean isFull( )      --> Return true if full; else false
        // void clear( )          --> Remove all items
        // void displayInorder(TreeNode<ItemType>*) const;
		// void displayPreorder(TreeNode<ItemType>*) const;
		// void displayPostorder(TreeNode<ItemType>*) const;


// ver também: http://www.cplusplus.happycodings.com/Data-Structures-and-Algorithm-Analysis-in-C++/code44.html
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
	//friend class CBinaryTree<ItemType>;
	//friend class CBinarySearchTree<ItemType>;
 };
#define RIGHT 0;
#define LEFT 1;
 template <class ItemType>
 class CBinaryTree
 {


 public:
     //create empty tree with default root node which has no value. set current to main root node.
     //The first constructor simply sets the main_root and current data members to NULL, since the tree has no nodes. 
	 //A new tree is made, therefore it is not part of a larger tree object, and the subtree value is set accordingly.
	 // Construtor com o Item não Achado
	 explicit CBinaryTree( const ItemType & notFound ):
	 ITEM_NOT_FOUND( notFound ),
	 main_root(NULL),
	 current(NULL),
	 subtree(false){};
	 //create new tree with passed node as the new main root. set current to main root. if the second parameter is 0, the new object simply points to the node of the original tree. If the second parameter is 1, a new copy of the subtree is created, which the object points to.
     //The second constructor accepts a pointer to a node, and creates a new tree object with the node that is passed acting as the new tree's main root. current is then set to the main root. 
	 //The second parameter specifies whether the new subtree object points directly to the original tree's nodes (the root and its decedents), or creates a copy of the subtree and is thus a new tree. 
	 //The subtree variable specifies if the subtree points directly to the original tree's nodes. 
	 //As you will later find out, this is important in the class destructor.
	 CBinaryTree(TreeNode<ItemType>* root, int op)
	 {
		if(op = 0)
		{
		   main_root = root;
		   current = root;
		   subtree = true;
		}
		else
		{
		   main_root = CopyTree(root,NULL);
		   current = main_root;
		   subtree = false;
		}
	 };
	//The job of the class destructor is to delete all the nodes, and free up memory as usual. 
	 //The clear() function is called just as in the previous data structure implementations. However, this operation is only performed if the object is a main tree. If the object is a subtree that points to the nodes of a larger tree, it will be deleted when the main tree itself is deleted. Attempting to delete the data in the memory associated with the subtree after it has already been deleted by the main tree will have unpredictable results.
	 virtual ~CBinaryTree()
	 {
		if(!subtree)
		   clear(); //delete all nodes
	 };

		/**
         * Deep copy.
         */
        const CBinaryTree<ItemType> & operator=( const CBinaryTree<ItemType> & copy )
        {
            if( this != &copy )
            {
                clear( );
                CopyTree( copy.main_root, getRoot() );
            }
            return *this;
        };

		/**
         * Soft Copy constructor.
		 * TODO: Fazê-lo threadSafe
         */
        CBinaryTree( const CBinaryTree<ItemType> & copy ) :
          main_root( NULL ), ITEM_NOT_FOUND( copy.ITEM_NOT_FOUND )
        { 
            *this = copy;
        };

		

    //insert new node as child of current. 0=left 1=right
    //The insert() function creates a new node as a child of current. The first parameter is a value for the new node, and the second parameter is an integer indicating what child the new node will become. A value of 0 indicates that the new node will be a left child of current, whereas a value of 1 indicates the new node will be a right child. If a node already exists in the location that programmer wishes to insert it, that node adopts the value passed to insert(). If the tree does not have any nodes, the second parameter is disregarded, and a main root is created.
	virtual  void insert(const ItemType &item,int pos) //insert as child of current 0=left 1=right. if item already exists, replace it
	 {
		assert(!isFull());
		//if the tree has no nodes, make a root node, disregard pos.
		if(main_root == NULL)
		{
		   main_root = new TreeNode<ItemType>;
		   main_root->data = item;
		   main_root->left = NULL;
		   main_root->right = NULL;
		   main_root->parent = NULL;
		   current = main_root;
		   return; //node created, exit the function
		}

		if(pos == 0) //new node is a left child of current
		{
		   if(current->left != NULL) //if child already exists, replace value
			  (current->left)->data = item;
		   else
		   {
			  current->left = new TreeNode<ItemType>;
			  current->left->data = item;
			  current->left->left = NULL;
			  current->left->right = NULL;
			  current->left->parent = current;
		   }
		}
		else //new node is a right child of current
		{
		   if(current->right != NULL) //if child already exists, replace value
			  (current->right)->data = item;
		   else
		   {
			  current->right = new TreeNode<ItemType>;
			  current->right->data = item;
			  current->right->left = NULL;
			  current->right->right = NULL;
			  current->right->parent = current;
		   }
		}
	 };
	
	
	//The remove() function removes the subtree referenced to by root, as well as the root node itself. 
	//Depending on whether it was a left or right child, the left or right pointer of the parent is set to NULL. 
	//The function uses recursion to perform the necessary operation on all nodes of the subtree. 
	// We must start with the nodes on the lowest level, and work our way up. 
	//If we were to delete the top level nodes first, we would loose the link the lower levels.
	//deletes a node and its subtree
	 virtual void remove(TreeNode<ItemType>* root)
	 {
		if(root == NULL) //base case - if the root doesn't exist, do nothing
		   return;
		remove(root->left); //perform the remove operation on the nodes left subtree first
		remove(root->right); //perform the remove operation on the nodes right subtree first
		if(root->parent == NULL) //if the main root is being deleted, main_root must be set to NULL
		   main_root = NULL;
		else
		{
		   if(root->parent->left == root) //make sure the parent of the subtree's root points to NULL, since the node no longer exists
			  root->parent->left = NULL;
		   else
			  root->parent->right = NULL;
		}
		current = root->parent; //set current to the parent of the subtree removed.
		delete root;
	 };
	//return value of current or ITEM_NOT_FOUND
    ItemType value() const{
    return dataAt(current);
	}; 

    //navigate the tree
	//The next five functions are used to navigate the tree. The programmer can visit a node's left child, right child, or parent, as well as reset current to the main root. Finally, the programmer can set current to a specific node by supplying a pointer to it. This is very helpful if the programmer would like to work with subtrees within the main tree object. Note, the SetCurrent() function should be used with caution. If a pointer is supplied to a node that is not within the tree, the results are unpredictable.

    void left(){
    current = current->left;
	};
    void right(){
    current = current->right;
	};
    void parent(){
    current = current->parent;
	};
    void reset(){
    current = main_root;
	}; //go to main_root
    void setCurrent(TreeNode<ItemType>* root) {
    current = root;
	};
	TreeNode<ItemType>*  getCurrent() {
    return current;
	};
    //return subtree (node) pointers
	//The four functions that follow return pointers to various nodes in the tree, depending on current. This is a required parameter for a few of our other functions, such as remove() and the three display functions. It is also used by one of our class constructors, which can make a new tree object from a subtree. The only function that is required is pointer_current(), since the programmer can navigate the tree to any node. The other three functions were also included for ease of use. It is often times necessary to perform an operation on a node's children or parent without leaving the node. The functions are also useful if a programmer would like to work on a subtree. An external TreeNode* pointer can be created, set by one of the pointer returning functions, and then passed to the operation functions of the class.


	 TreeNode<ItemType>* pointer_left() const
	 {
		return current->left;
	 };

 
	 TreeNode<ItemType>* pointer_right() const
	 {
		return current->right;
	 };

 
	 TreeNode<ItemType>* pointer_parent() const
	 {
		return current->parent;
	 };

 
	 TreeNode<ItemType>* pointer_current() const
	 {
		return current;
	 };
  

    //return values of children and parent without leaving current node
	 // return ITEM_NOT_FOUND if ItemType is NULL;
	//The next three functions are also not required, but were added for ease of use. 
	 //They return the values of a node's two children and parent without having to leave the node.
	 ItemType peek_left() const
	 {
		return dataAt(current->left);
	 };

	 ItemType peek_right() const
	 {
		return dataAt(current->right);
	 };
	 ItemType peek_parent() const
	 {
		return dataAt(current->parent);
	 };

		 /**
         * Internal method to get value of node t.
         * Return the element field or ITEM_NOT_FOUND if t is NULL.
         */
       const ItemType dataAt( TreeNode<ItemType>*t  ) const
        {
            if( t == NULL )
                return ITEM_NOT_FOUND;
            else
                return t->data;
        }

    //print the tree or a subtree. only works if ItemType is supported by << operator
   //The display functions as explained above are next. Note, these functions will work only if ItemType is supported by the << operator. For instance, any simple built in C/C++ type (such as int, float, char, etc.) will work without any modification. template <class ItemType>
	 void displayInorder() const
	 {
		displayInorder(main_root);
	 };


	 void displayInorder(TreeNode<ItemType>* root) const
		{
		   if (root == NULL)
			  return;

		   displayInorder(root->left);
		   cout << root->data;
		   displayInorder(root->right);
		};



	 void displayPreorder() const
	 {
		
		displayPreorder(main_root);
	 };

	 void displayPreorder(TreeNode<ItemType>* root) const
	 {
		if (root == NULL)
		   return;

		cout << root->data;
		displayInorder(root->left);
		displayInorder(root->right);
	 };

	 void displayPostorder() const
	 {
		displayInorder(main_root);
	 };
 
	 void displayPostorder(TreeNode<ItemType>* root) const
	 {
		if (root == NULL)
		   return;

		displayInorder(root->left);
		displayInorder(root->right);
		cout << root->data;
	 };


    //delete all nodes in the tree
	//The clear() function deletes all nodes in the list. This is very easy to do, since we can take advantage of the remove() function, which we has already defined. The remove() functions deletes all nodes of a subtree, as well as the root node. Therefore, we can pass the main root to remove() in order to delete all nodes in the tree.
	void clear()
	 {
		remove(main_root); //use the remove function on the main root
		main_root = NULL; //since there are no more items, set main_root to NULL
		current = NULL;
	 }

	// The IsEmpty() function works by evaluating main_root. If there aren't any nodes in the tree, main_root points to NULL.
	 bool isEmpty() const
	 {
		return (main_root == NULL);
	 };

	 //Finally, other than the data types, the implementation of the IsFull() function does not change from previous classes.
	 bool isFull() const
	 {
		TreeNode<ItemType> *tmp = new TreeNode<ItemType>;
		if(tmp == NULL)
		   return true;
		else
		{
		   delete tmp;
		   return false;
		}
	 };

	 // Now let's take a look at two additional functions.
	//Often times it is necessary to know how many nodes are in the list, or how many of them are leafs. One example of when a leaf count is required is in a binary expression tree. Binary expression trees store mathematical expression, for instance, 5*x+7=22. Each character of the expression is represented by one node. They are stored in such a way that the expression can then be displayed using an in-order traversal. Also, pre-order and post-order traversals will display the mathematical expression using prefix and postfix notations. This means an operator stored in a node perform an operation on its two children. In such a setup, all operators are internal nodes, whereas variables and constants are leafs. The code for the NodeCount() and LeafCount() functions is displayed below. Both are very short since recursion is used.

	 int nodeCount()
	 {
		
		return nodeCount(main_root); //add the leaf nodes in the left and right subtrees
	 };

	int leafCount(TreeNode<ItemType>* root)
	 {
		if(root == NULL) //base case - if the node doesn't exist, return 0 (don't count it)
		   return 0;
		if((root->left == NULL) && (root->right == NULL)) //if the node has no children return 1 (it is a leaf)
		   return 1;
		return leafCount(root->left) + leafCount(root->right); //add the leaf nodes in the left and right subtrees
	 };

	 int nodeCount(TreeNode<ItemType>* root)
	 {
		if(root == NULL) //base case - if the return 0 if node doesn't exist (don't count it)
		   return 0;
		else
		   return 1 + nodeCount(root->left) + nodeCount(root->right); //return 1 for the current node, and add the amount of nodes in the left and right subtree
	 };
	 	 /**
         * Internal method to find the smallest item from the root.
         * Return node containing the smallest item.
         */
        ItemType  findMax( ) const
        {
           return dataAt(findMax( main_root ));
		  
        };

		     /**
         * Internal method to find the smallest item from the root.
         * Return node containing the smallest item.
         */
        ItemType findMin( ) const
        {
			return dataAt(findMin( main_root ));
		};

		TreeNode<ItemType>* getRoot() {
			return main_root;
		}

		void setRoot(TreeNode<ItemType>* root) {
			main_root=root;
		}

 private:
    TreeNode<ItemType>* current;
    TreeNode<ItemType>* main_root;
	const ItemType ITEM_NOT_FOUND;

    //create a new copy of a subtree if passed to the constructor
	//The CopyTree() function creates a copy of subtree root and returns a pointer to the location of the new copy's root node. 
	//The second parameter is a pointer to the parent of the subtree being passed.
	//Since CopyTree() uses recursion to traverse the original tree, passing each node's parent as a parameter is the most efficient way of assigning each new node's parent value. Since the parent of the main root is always NULL, we pass NULL as the second parameter in the class constructor above.
	TreeNode<ItemType>* CopyTree(TreeNode<ItemType> *root, TreeNode<ItemType> *parent) const
	 {
		if(root == NULL) //base case - if the node doesn't exist, return NULL.
		   return NULL;
		TreeNode<ItemType>* tmp = new TreeNode<ItemType>; //make a new location in memory
		tmp->data = root->data; //make a copy of the node's data
		tmp->parent = parent; //set the new node's parent
		tmp->left = CopyTree(root->left,tmp); //copy the left subtree of the current node. pass the current node as the subtree's parent
		tmp->right = CopyTree(root->right,tmp); //do the same with the right subtree
		return tmp; //return a pointer to the newly created node.
	 };
    bool subtree; //does it reference a part of a larger object?
    
         /**
         * Internal method to find the smallest item in a subtree t.
         * Return node containing the smallest item.
         */
        TreeNode<ItemType> * findMin(  TreeNode<ItemType> *t  ) const
        {
            if( t == NULL )
                return NULL;
            if( t->left == NULL )
                return t;
            return findMin( t->left );
        };

		 /**
         * Internal method to find the smallest item in a subtree t.
         * Return node containing the smallest item.
         */
        TreeNode<ItemType> * findMax(  TreeNode<ItemType> *t  ) const
        {
            if( t == NULL )
                return NULL;
            if( t->right == NULL )
                return t;
            return findMax( t->right );
        };

#if 0       
		/**
         * Internal method to find the largest item in a subtree t.
         * Return node containing the largest item.
		 * non recursive
         */
     
         TreeNode<ItemType> * findMax(  TreeNode<ItemType> *t ) const
        {
            if( t != NULL )
                while( t->right != NULL )
                    t = t->right;
            return t;
        };
#endif
 };



 /*
Binary Search Trees

 Another type of special binary tree is the binary search tree (BinarySearchTree). 
 BSTs must conform to a property that states all the left children of a node have a lesser value than the node, 
 and all the right children have a value greater than the node. 
 In order to make our binary tree class a BinarySearchTree, we need only modify the insert() function, 
 since nodes can no longer be placed anywhere in the tree by the programmer. 
 Otherwise, a BinarySearchTree acts in the same fashion as a standard binary tree.

 The new insert() function accepts one parameter, the item to be inserted. 
 If the tree is empty, then the main root is added in the same fashion as it was with a standard binary tree, and the function exits. If the tree is not empty, the function proceeds with a new algorithm.

 The parent of the new node is found by running the insert_find() function, a new private member function that must be added to the BinarySearchTree class. 
 The insert_find() function accepts two parameters - the root of the tree and the item value. 
 The root is needed as a parameter because insert_find() uses recursion to traverse the tree. 
 The function works by comparing the value of item to each node. 
 If it is less than the node's value, and the node has a left child, the function proceeds to that child and performs the same operation. 
 If it is greater (or equal to) than the node's value, and a right child exists, then the function proceeds to the right child.
 If item is less than the node and a left child does not exist, or it is more than the node and a right child does not exist, 
 that is where the new node belongs.

 The insert() function receives a pointer to the new parent, however, we must check again if the new node is to be the left or right child. 
 This is because there is no efficient way a recursive version of insert_find() can return this information. 
 We would have to add another parameter, or write a non-recursive version of insert_find(). 
 Both methods are far more space and time consuming than simply performing another check.

 A new node is then created using the same method as in the original version of insert().
 */


  template <class ItemType>
 class CBinarySearchTree :public CBinaryTree<ItemType>
 {
 public:
	
	CBinarySearchTree( const ItemType & notFound ): CBinaryTree<ItemType>(notFound){}; //create empty tree with default root node which has no value. set current to main root node.
	CBinarySearchTree(TreeNode<ItemType>* node,int): CBinaryTree<ItemType>(node, int){}; //create new tree with passed node as the new main root. set current to main root. if the second parameter is 0, the new object simply points to the node of the original tree. If the second parameter is 1, a new copy of the subtree is created, which the object points to.
	~CBinarySearchTree(){};
	
			
	    /**
         * Internal method to find an item from the root.
         * x is item to search for.
         * Return node containing the matched item.
         */
		const ItemType & find( const ItemType & x ){
			
			return dataAt(find_node(x, getRoot()));
			
		
		}; 
	
		/**
         * Internal method to find an item from the root.
         * x is item to search for.
         * Return node containing the matched item.
         */
		TreeNode<ItemType> * find_node( const ItemType & x ) {
			TreeNode<ItemType> * node=NULL;
			node =find_node(x, getRoot());
			return node;
		
		};

	/**
         * Internal method to find an item and remove it.
         * x is item to search for.
         */
	void remove( const ItemType & x ) {
		TreeNode<ItemType> *node = find_node(x);
		if (node !=NULL) {
			remove_node(node);
		}

	};

	/**
         * Internal method to find an item in a subtree.
         * x is item to search for.
         * t is the node that roots the tree.
         * Return node containing the matched item.
         */
	TreeNode<ItemType> * find_node( const ItemType & x, TreeNode<ItemType> *t ) const
        {
            if( t == NULL )
                return NULL;
			else if( x == t->data) return t;
            else if( x < t->data )
                return find_node( x, t->left );
            else if( x > t->data )
                return find_node( x, t->right );
                           
        }

	TreeNode<ItemType>* insert_find(TreeNode<ItemType>* root,ItemType item)
	 {
		if((root->left != NULL) && (item < root->data))
		   return insert_find(root->left,item);

		else if((root->right != NULL) && (item > root->data))
		   return insert_find(root->right,item);
		else return root;   // item é igual a root->parent || root->left==NULL || root->right ==NULL;
	};

#if 0
	/**
         * Insert x into the tree; duplicates are ignored.
         */
        void insert( const ItemType & x )
        {
            //if the tree has no nodes, make a root node
			if(getRoot() == NULL)
			{
				setRoot(new TreeNode<ItemType>(x));
				setCurrent(getRoot());
				return;
			}else insert( x, getRoot() );
        }

	//insert new node as child of current.
	/**
         * Internal method to insert into a subtree.
         * x is the item to insert.
         * t is the node that roots the tree.
         * Set the new root.
         */
        void insert( const ItemType & x, TreeNode<ItemType> * & t ) const
        {
            if( t == NULL )
                t = new TreeNode<ItemType>( x );
			    t->parent = ?
            else if( x < t->data )
                insert( x, t->left );
            else if( t->data < x )
                insert( x, t->right );
            else
                ;  // Duplicate; do nothing
        }

#endif
	virtual void insert(const ItemType& item)
		{
		//if the tree has no nodes, make a root node
		if(getRoot() == NULL)
		{
		   setRoot(new TreeNode<ItemType>(item));
		   setCurrent(getRoot());
		   return;
		}

		TreeNode<ItemType>* new_parent = insert_find(getRoot(),item); //find the new node's parent

		if (item < new_parent->data) //check whether the new node is a left or right child and create it
		{
		   new_parent->left = new TreeNode<ItemType>(item);
		   new_parent->left->parent = new_parent;
		}
		else if(item > new_parent->data)
		{
		   new_parent->right = new TreeNode<ItemType>(item);
		   new_parent->right->parent = new_parent;
		}
		// item = new_parent->data não faz nada

	 };

	/*
 Since the programmer is no longer in control of the location of each node, we can add a function that removes one node at a time. 
 The reason we did not implement such a function for the standard binary tree class is that we do not know how the program requires the structure to handle removing a node. 
 If the node to be deleted is a leaf, the solution is simple. We set its parent's pointer to NULL. 
 If it has one child, then the parent is set to point to that child. However, what happens if the node has two children ? 
 How should we insert those children back into the tree once the node is deleted ? 
 The solution can vary, depending on the programming task. 
 Since a binary search tree follows a specific property, we can libraryelop an algorithm that maintains the binary search tree property when rearranging the node's children.
 The code for the remove_node() function may look difficult at first, however when broken down into each possible situation, it is very simple to understand. 
 The first case that must be considered is if we wish to remove the main root, and it has only one child. 
 In this situation, that child becomes the new main root.
 If the node to be deleted has no children, node's parent is set to point to NULL, and node is then deleted.
 Also as mentioned before, if node has one child, the parent of node is set to point to this child, and node is then deleted.
 If delete_node has two children, a little bit more work must be done. 
 The question arises as to how to attach delete_node's children to the tree, while preserving the binary search tree property. 
 One possible solution would be to attach one of the children to delete_node's parent, and reinsert each node from the second child subtree one-by-one. 
 However, this method is very inefficient, especially if the node to be deleted has a very large subtree.
 The ideal approach is to find another node in the tree, which can replace delete_node, and still maintain the binary search tree property. 
 We can then replace the value of delete_node, and remove the node who's value we replaced it with instead. 
 The possible nodes that would fit such a criteria are the largest node in the left subtree, and the smallest node in the right subtree. 
 The largest node in the left subtree is still smaller than any node of the right subtree, and the smallest node in the right subtree is larger than any node in the left subtree, 
 therefore making both possible values that can replace root. 
 If a right subtree exists, then it is used, since it may contain a value that is equal to delete_node (in which case that value will be used).
 The largest node in the left subtree can be found by moving to the left one time (starting from delete_node), and then moving to the right as much as possible. The smallest node in the right subtree can be found by moving once to the right, and then to the left as much as possible. This means that either node will have at most one child (the largest node in the left subtree can only have a left child, and the smallest node in the right subtree can only have a right child). It can therefore be removed using the above method, by attaching that child to the node's parent.

 The replace_find() private member function returns the node that is used to replace delete_node. The first parameter of the function is a pointer to the first possible node (if we are searching the left subtree, this value is root->left, whereas it is root->right if we are searching the right subtree), and the second parameter is what direction to search in. Zero means the function will locate the largest value in the left subtree, meaning it will travel to the right as much as possible. A value of one means the function will locate the smallest value in the right subtree, therefore travelling to the left as much as possible. Once the node is found, delete_node is set to its value, and the node is deleted.
 */

 void remove_node(TreeNode<ItemType>* root)
 {
    if (root == NULL) return;
	if((root->left == NULL) && (root->right == NULL)) //if the root has no children
    {
       if (root->parent == NULL) {// this is the main root
		delete root;
		setRoot(NULL);
		setCurrent(NULL);
		
	   }
		//have the parent point to NULL in place of it
		if(root->parent->left == root) //if it a left child
          root->parent->left = NULL;
		else  if(root->parent->right == root) //it is a right child
          root->parent->right = NULL;
			setCurrent(root->parent);
		delete root;
		return;
    } 
	//apenas um dos dois lados é null e é o nó root
	 if((root == getRoot()) && ((root->left == NULL) || (root->right == NULL)))
    {
       //set the main root's only child as the new root. if it has no children, main_root becomes NULL as the tree is empty.
       if(root->left == NULL)
          setRoot(root->right);
       else if(root->right == NULL)
       setRoot(root->left);
       getRoot()->parent = NULL; //set the new main root's parent to NULL
       if(getCurrent() == root) //if current is at the original main root, set it to the new root, since the original will be deleted
          setCurrent(getRoot());
       delete root;
       return;
    }

    if(getCurrent() == root) //if current is at the node to be deleted, set it to the node's parent
       setCurrent(root->parent);

    //if the root has one child, have the parent point to it in place of root
    if((root->left == NULL) && (root->right != NULL))
    {
       if(root->parent->left == root)
          root->parent->left = root->right;
       else
          root->parent->right = root->right;
       delete root;
       return;
    }
    if((root->left != NULL) && (root->right == NULL))
    {
       if(root->parent->left == root)
          root->parent->left = root->left;
       else
          root->parent->right = root->left;
       delete root;
       return;
    }

    //if the node has two children

    TreeNode<ItemType> *tmp;
    if(root->right != NULL) //if the root has a right subtree, search it for the smallest value
       tmp = replace_find(root->right,1);
    else if(root->left != NULL) //search the left subtree for the largest value
       tmp = replace_find(root->left,0);
    root->data = tmp->data;
    //if tmp has a child, have tmp's parent point to it. Otherwise, have the parent point to NULL in place of tmp.
    if(tmp->parent->left == tmp) //if tmp is a left child
    {
       if(root->right != NULL) //if it has a right child, have the parent point to it
          tmp->parent->left = tmp->right;
       else //point to the left child. This value is NULL if there is no left child
          tmp->parent->left = tmp->left;
    }
    else //if tmp is a right child
    {
       if(root->right != NULL) //if it has a right child, have the parent point to it
          tmp->parent->right = tmp->right;
       else //point to the left child. This value is NULL if there is no left child
          tmp->parent->right = tmp->left;
    }
    delete tmp;
	};
	 TreeNode<ItemType>* replace_find(TreeNode<ItemType>* root,int direction)
	 {
		if(direction == 0) //searching left subtree for largest value. go right as much as possible. Return last node.
		{
		   if(root->right == NULL)
			  return root;
		   return replace_find(root->right,0);
		}
		else if(direction == 1)//searching right subtree for smallest value. go left as much as possible. Return last node.
		{
		   if(root->left == NULL)
			  return root;
		   return replace_find(root->left,1);
		}
	};
 };


 

 

} //end SGF
#endif