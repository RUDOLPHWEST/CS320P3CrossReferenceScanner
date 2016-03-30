#pragma once
#include <iostream>
#include "exceptions_CS320.h"
#include "OrderedPair.h"  
using namespace std;
//Erase, Find, End
template <typename Comparable>
class BinarySearchTree
{
private:
	//the node structure for binary search trees includes pointers to parent nodes
	//the root's parent is NULL
	//struct is used for BinarySearchTree easy access to the public data members;
	struct BST_Node
	{
		Comparable element;
		BST_Node *left;
		BST_Node *right;
		BST_Node *parent;
		BST_Node(const Comparable & theElement, BST_Node *lt = NULL, BST_Node *rt = NULL, BST_Node *p = NULL)
			: element(theElement), left(lt), right(rt), parent(p) { }
	};

	//the iterators for binary search trees
public:
	class const_iterator
	{

	public:

		// constructor
		const_iterator()
		{}

		// used to convert a const iterator to a const_iterator
		const_iterator(const iterator& pos) : nodePtr(pos.nodePtr)
		{}

		// comparison operators. just compare node pointers
		bool operator== (const const_iterator& rhs) const
		{
			return nodePtr == rhs.nodePtr;
		}

		bool operator!= (const const_iterator& rhs) const
		{
			return nodePtr != rhs.nodePtr;
		}

		// dereference operator. return a reference to
		// the value pointed to by nodePtr
		const Comparable& operator* () const
		{
			if (nodePtr == NULL)
				throw
				referenceError("BinarySearchTree const_iterator operator* (): NULL reference");
			return nodePtr->element;
		}

		// preincrement. move forward to next larger value
		const_iterator& operator++ ()
		{
			BST_Node  *p;

			if (nodePtr == NULL)
			{
				// ++ from end(). get the root of the tree
				nodePtr = tree->root;

				// error! ++ requested for an empty tree
				if (nodePtr == NULL)
					throw underflowError("BinarySearchTree const_iterator operator++ (): tree empty");

				// move to the smallest value in the tree,
				// which is the first node inorder
				while (nodePtr->left != NULL)
					nodePtr = nodePtr->left;
			}
			else
				if (nodePtr->right != NULL)
				{
					// successor is the furthest left node of
					// right subtree
					nodePtr = nodePtr->right;

					while (nodePtr->left != NULL)
						nodePtr = nodePtr->left;
				}
				else
				{
					// have already processed the left subtree, and
					// there is no right subtree. move up the tree,
					// looking for a parent for which nodePtr is a left child,
					// stopping if the parent becomes NULL. a non-NULL parent
					// is the successor. if parent is NULL, the original node
					// was the last node inorder, and its successor
					// is the end of the list
					p = nodePtr->parent;

					while (p != NULL && nodePtr == p->right)
					{
						nodePtr = p;
						p = p->parent;
					}

					// if we were previously at the right-most node in
					// the tree, nodePtr = NULL, and the iterator specifies
					// the end of the list
					nodePtr = p;
				}

			return *this;
		}

		// postincrement
		const_iterator operator++ (int)
		{
			// save current const_iterator
			const_iterator tmp = *this;

			// move myself forward to the next tree node
			++*this;

			// return the previous value
			return tmp;
		}

		// predecrement. move backward to largest value < current value
		const_iterator& operator-- ()
		{
			BST_Node<T> *p;

			if (nodePtr == NULL)
			{
				// -- from end(). get the root of the tree
				nodePtr = tree->root;

				// error! -- requested for an empty tree
				if (nodePtr == NULL)
					throw
					underflowError("BinarySearchTree iterator operator--: tree empty");

				// move to the largest value in the tree,
				// which is the last node inorder
				while (nodePtr->right != NULL)
					nodePtr = nodePtr->right;
			}
			else if (nodePtr->left != NULL)
			{
				// must have gotten here by processing all the nodes
				// on the left branch. predecessor is the farthest
				// right node of the left subtree
				nodePtr = nodePtr->left;

				while (nodePtr->right != NULL)
					nodePtr = nodePtr->right;
			}
			else
			{
				// must have gotten here by going right and then
				// far left. move up the tree, looking for a parent
				// for which nodePtr is a right child, stopping if the
				// parent becomes NULL. a non-NULL parent is the
				// predecessor. if parent is NULL, the original node
				// was the first node inorder, and its predecessor
				// is the end of the list
				p = nodePtr->parent;
				while (p != NULL && nodePtr == p->left)
				{
					nodePtr = p;
					p = p->parent;
				}

				// if we were previously at the left-most node in
				// the tree, nodePtr = NULL, and the iterator specifies
				// the end of the list
				nodePtr = p;
			}

			return *this;
		}

		// postdecrement
		const_iterator operator-- (int)
		{
			// save current const_iterator
			const_iterator tmp = *this;

			// move myself backward to the previous tree node
			--*this;

			// return the previous value
			return tmp;
		}

	private:

		// nodePtr is the current location in the tree. we can move
		// freely about the tree using left, right, and parent.
		// tree is the address of the BinarySearchTree object associated
		// with this iterator. it is used only to access the
		// root pointer, which is needed for ++ and --
		// when the iterator value is end()
		const BST_Node *nodePtr;
		const BinarySearchTree<Comparable> *tree;

		// used to construct a const_iterator return value from
		// an BST_Node pointer
		const_iterator(const BST_Node *p, const BinarySearchTree<Comparable> *t) : nodePtr(p), tree(t)
		{}
		friend class BinarySearchTree<Comparable>;
	};

	class iterator
	{
		friend class BinarySearchTree<Comparable>;
		friend class const_iterator;

	public:

		// constructor
		iterator()
		{}

		// comparison operators. just compare node pointers
		bool operator== (const iterator& rhs) const
		{
			return nodePtr == rhs.nodePtr;
		}

		bool operator!= (const iterator& rhs) const
		{
			return nodePtr != rhs.nodePtr;
		}

		// dereference operator. return a reference to
		// the value pointed to by nodePtr
		Comparable& operator* () const
		{
			if (nodePtr == NULL)
				throw referenceError("BinarySearchTree iterator operator* (): NULL reference");

			return nodePtr->element;
		}

		// preincrement. move forward to next larger value
		iterator& operator++ ()
		{
			BST_Node *p;

			if (nodePtr == NULL)
			{
				// ++ from end(). get the root of the tree
				nodePtr = tree->root;

				// error! ++ requested for an empty tree
				if (nodePtr == NULL)
					throw
					underflowError("BinarySearchTree iterator operator++ (): tree empty");

				// move to the smallest value in the tree,
				// which is the first node inorder
				while (nodePtr->left != NULL)
					nodePtr = nodePtr->left;
			}
			else
				if (nodePtr->right != NULL)
				{
					// successor is the furthest left node of
					// right subtree
					nodePtr = nodePtr->right;

					while (nodePtr->left != NULL)
						nodePtr = nodePtr->left;
				}
				else
				{
					// have already processed the left subtree, and
					// there is no right subtree. move up the tree,
					// looking for a parent for which nodePtr is a left child,
					// stopping if the parent becomes NULL. a non-NULL parent
					// is the successor. if parent is NULL, the original node
					// was the last node inorder, and its successor
					// is the end of the list
					p = nodePtr->parent;

					while (p != NULL && nodePtr == p->right)
					{
						nodePtr = p;
						p = p->parent;
					}

					// if we were previously at the right-most node in
					// the tree, nodePtr = NULL, and the iterator specifies
					// the end of the list
					nodePtr = p;
				}

			return *this;
		}

		// postincrement
		iterator operator++ (int)
		{
			// save current iterator
			iterator tmp = *this;

			// move myself forward to the next tree node
			++*this;

			// return the previous value
			return tmp;
		}

		// predecrement. move backward to largest value < current value
		iterator& operator-- ()
		{
			BST_Node *p;

			if (nodePtr == NULL)
			{
				// -- from end(). get the root of the tree
				nodePtr = tree->root;

				// error! -- requested for an empty tree
				if (nodePtr == NULL)
					throw
					underflowError("BinarySearchTree iterator operator--: tree empty");

				// move to the largest value in the tree,
				// which is the last node inorder
				while (nodePtr->right != NULL)
					nodePtr = nodePtr->right;
			}
			else if (nodePtr->left != NULL)
			{
				// must have gotten here by processing all the nodes
				// on the left branch. predecessor is the farthest
				// right node of the left subtree
				nodePtr = nodePtr->left;

				while (nodePtr->right != NULL)
					nodePtr = nodePtr->right;
			}
			else
			{
				// must have gotten here by going right and then
				// far left. move up the tree, looking for a parent
				// for which nodePtr is a right child, stopping if the
				// parent becomes NULL. a non-NULL parent is the
				// predecessor. if parent is NULL, the original node
				// was the first node inorder, and its predecessor
				// is the end of the list
				p = nodePtr->parent;
				while (p != NULL && nodePtr == p->left)
				{
					nodePtr = p;
					p = p->parent;
				}

				// if we were previously at the left-most node in
				// the tree, nodePtr = NULL, and the iterator specifies
				// the end of the list
				nodePtr = p;
			}

			return *this;
		}

		// postdecrement
		iterator operator-- (int)
		{
			// save current iterator
			iterator tmp = *this;

			// move myself backward to the previous tree node
			--*this;

			// return the previous value
			return tmp;
		}

	private:

		// nodePtr is the current location in the tree. we can move
		// freely about the tree using left, right, and parent.
		// tree is the address of the BinarySearchTree object associated
		// with this iterator. it is used only to access the
		// root pointer, which is needed for ++ and --
		// when the iterator value is end()
		BST_Node  *nodePtr;
		BinarySearchTree<Comparable> *tree;

		// used to construct an iterator return value from
		// an BST_Node pointer
		iterator(BST_Node  *p, BinarySearchTree<Comparable> *t) : nodePtr(p), tree(t)
		{}

	};

	// the interface for BinarySearchTree class 
public:
	BinarySearchTree();
	BinarySearchTree(Comparable *first, Comparable *last);
	BinarySearchTree(const BinarySearchTree<Comparable> & rhs);
	~BinarySearchTree();

	const BinarySearchTree & operator=(const BinarySearchTree & rhs);
	bool empty() const;
	unsigned size() const;
	void printInOrder() const;
	void makeEmpty();
	OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool>  find(const Comparable & x) /*const*/;
	OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool>  insert(const Comparable & x);
	void erase(const Comparable & x);
	void erase(typename BinarySearchTree<Comparable>::iterator); //const iterator
	void erase(iterator first, iterator last);
	// erase all items in the range [first, last).
	// Precondition: the tree must not be empty. 
	//               if the tree is empty, the function throws the underflowError exception.
	// Postcondition: the size of the tree decreases by the number of elements in the range [first, last)
	const Comparable & findMin() const;
	const Comparable & findMax() const;
	// return an iterator pointing to the first item
	// inorder
	iterator begin()
	{
		if (root == nullptr)
		{
			//iterator itr(NULL, this) ;
			return iterator(NULL, this);
		}
		//if the tree has a root
		else
		{
			BST_Node * currentNode;
			currentNode = root;

			while (currentNode->left != nullptr)
			{
				currentNode = currentNode->left;
			}

			iterator itr(currentNode, this); 
			return itr;
		}
	}

	// constant version
	const_iterator begin() const
	{
		if (root == NULL)
		{
			iterator itr = NULL;
			return itr;
		}
		//if the tree has a root
		else
		{
			BST_Node * currentNode;
			currentNode = root;

			while (currentNode->left != NULL)
			{
				currentNode = currentNode->left;
			}

			const_iterator itr(currentNode, this);
			return itr;
		}
	}

	iterator end()
	{
		// end indicated by an iterator with NULL stnode pointer
		return iterator(NULL, this);
	}

	// constant version
	const_iterator end() const
	{
		// end indicated by an iterator with NULL stnode pointer
		return const_iterator(NULL, this);
	}

private: 
	// utility functions
	void makeEmpty(BST_Node * & t);
	void printInOrder(BST_Node *t) const;
	BST_Node * clone(BST_Node *t) const;
	BST_Node * findMin(BST_Node * t) const;
	BST_Node * findMax(BST_Node * t) const;

	//The tree
	BST_Node *root;
	unsigned numberOfNodes;

};

/*******START DEFINITONS of METHODS *********/

template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree() :root(NULL), numberOfNodes(0) { }

template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(Comparable *first, Comparable *last) : root(NULL), numberOfNodes(0)
{
	Comparable *p = first;

	// insert each item in [first, last) into the tree
	while (p != last)
	{
		insert(*p);
		p++;
	}
}

/**
* Destructor for BinarySearchTree

*/
template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
	makeEmpty();
}

/*
* Copy Constructor for BinarySearchTree

*/
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree<Comparable> & rhs)
{
	root = clone(rhs.root);
	numberOfNodes = rhs.numberOfNodes;
}

/*
* Assignment operator with deep copy (cloning of a tree).
*/
template<typename Comparable>
const BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(const BinarySearchTree & rhs)
{
	if (this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
		numberOfNodes = rhs.numberOfNodes;
	}
	return *this;
}

/* Accessor return the number of nodes in this tree
*/
template<typename Comparable>
unsigned BinarySearchTree<Comparable>::size() const { return numberOfNodes; }

/* Accessor method returns whether this BinarySearchTree
*/
template<typename Comparable>
bool BinarySearchTree<Comparable>::empty() const { return root == NULL; }

/* Prints this tree's node values using inOrder traversal
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::printInOrder() const
{
	printInOrder(root);
}
 
/*
* Find an element in this tree.
* Returns a pair: if second is true, the first element is an iterator object pointing at node in tree
*                 if second is false, the first element is end() of tree indicating element not found
*/
template<typename Comparable>
typename OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool>  BinarySearchTree<Comparable>::find(const Comparable & x) //const
{

	BST_Node *t = root, *curr;;

	// traverse the tree using t and starting at root
	// terminate on on empty subtree or found value
	while (t != NULL && !(x == t->element))
		if (x < t->element)
			t = t->left;
		else
			t = t->right;

	// t points at the node containing x if found; t is NULL if not found
	// if x is found, return a const_iterator with pointer t;
	// otherwise, return that the end() of tree was reached
	if (t != NULL)
		return OrderedPair<iterator,bool>(iterator(t,this), true);
	else
		return OrderedPair<iterator,bool>(iterator(NULL, this), false);
}

/*
* Insert x into this BinarySearchTree;
* Returns a pair: if second is true, the first element is an iterator object
*                    just inserted in tree
*                 if second is false, the first element is is and iterator pointing
*                    node in tree where x already exists

*/
template<typename Comparable>
typename OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool> BinarySearchTree<Comparable>::insert(const Comparable & x)
{
	if (root == NULL)
	{
		BST_Node * rootNode = new BST_Node(x);
		root = rootNode;
		numberOfNodes++;
		iterator itr(root, this);
		OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool> insertionPair(itr, true);
		return insertionPair;
		//return
	}
	else {
		BST_Node *currentNode;
		currentNode = root;
		while (currentNode != NULL) {
			if (x < currentNode->element)
			{	
				if (currentNode->left == NULL){
					BST_Node * newleaf = new BST_Node(x, NULL, NULL, currentNode);
					currentNode->left = newleaf;
					numberOfNodes++;

					iterator itr(root, this);
					OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool> insertionPair(itr, true);
					return insertionPair;
					//return
				}
				currentNode = currentNode->left;
			}
			else if (currentNode->element < x)
			{
				if (currentNode->right == NULL){
					BST_Node * newleaf = new BST_Node(x, NULL, NULL, currentNode);
					currentNode->right = newleaf;
					numberOfNodes++;

					iterator itr(root, this);
					OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool> insertionPair(itr, true);
					return insertionPair;
					//return
				}
				currentNode = currentNode->right;
			}
			else
			{
				iterator itr(root, this);
				OrderedPair<typename BinarySearchTree<Comparable>::iterator, bool> insertionPair(itr, false);
				return insertionPair;
				
				//duplicate
				//return false
			}
		}
	}
}

/*
* Remove node pointed at by iterator itr
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::erase(typename BinarySearchTree<Comparable>::iterator itr) // const
{
	// dNodePtr = pointer to node D that is deleted
	// pNodePtr = pointer to parent P of node D
	// rNodePtr = pointer to node R that replaces D
	BST_Node *dNodePtr = itr.nodePtr, *pNodePtr, *rNodePtr;
	if (root == NULL)
		throw  underflowError("BinarySearchTree::erase() : underflow");
	if (dNodePtr == NULL)
		throw  referenceError("BinarySearchTree::erase(): invalid iterator");

	// assign pNodePtr the address of P
	pNodePtr = dNodePtr->parent;

	// If D has a NULL pointer, the replacement node is the other child
	if (dNodePtr->left == NULL || dNodePtr->right == NULL)
	{
		if (dNodePtr->right == NULL)
			rNodePtr = dNodePtr->left;
		else
			rNodePtr = dNodePtr->right;

		if (rNodePtr != NULL)
			// the parent of R is now the parent of D
			rNodePtr->parent = pNodePtr;
	}
	// both pointers of dNodePtr are non-NULL.
	else
	{
		// find and unlink replacement node for D.
		// starting at the right child of node D,
		// find the node whose value is the smallest of all
		// nodes whose values are greater than the value in D.
		// unlink the node from the tree.

		// pOfRNodePtr = pointer to parent of replacement node
		BST_Node *pOfRNodePtr = dNodePtr;

		// first possible replacement is right child of D
		rNodePtr = dNodePtr->right;

		// descend down left subtree of the right child of D,
		// keeping a record of current node and its parent.
		// when we stop, we have found the replacement
		while (rNodePtr->left != NULL)
		{
			pOfRNodePtr = rNodePtr;
			rNodePtr = rNodePtr->left;
		}

		if (pOfRNodePtr == dNodePtr)
		{
			// right child of deleted node is the replacement.
			// assign left subtree of D to left subtree of R
			rNodePtr->left = dNodePtr->left;
			// assign the parent of D as the parent of R
			rNodePtr->parent = pNodePtr;
			// assign the left child of D to have parent R
			dNodePtr->left->parent = rNodePtr;
		}
		else
		{
			// we moved at least one node down a left branch
			// of the right child of D. unlink R from tree by
			// assigning its right subtree as the left child of
			// the parent of R
			//cout << pOfRNodePtr << endl;
			pOfRNodePtr->left = rNodePtr->right;
			

			// the parent of the right child of R is the
			// parent of R
			if (rNodePtr->right != NULL)
				rNodePtr->right->parent = pOfRNodePtr;

			// put replacement node in place of dNodePtr
			// assign children of R to be those of D
			rNodePtr->left = dNodePtr->left;
			rNodePtr->right = dNodePtr->right;
			// assign the parent of R to be the parent of D
			rNodePtr->parent = pNodePtr;
			// assign the parent pointer in the children
			// of R to point at R
			rNodePtr->left->parent = rNodePtr;
			rNodePtr->right->parent = rNodePtr;
		}
	}

	// complete the link to the parent node.

	// deleting the root node. assign new root
	if (pNodePtr == NULL)
		root = rNodePtr;
	// attach R to the correct branch of P
	else if (dNodePtr->element < pNodePtr->element)
		pNodePtr->left = rNodePtr;
	else
		pNodePtr->right = rNodePtr;

	// delete the node from memory and decrement tree size
	delete dNodePtr;
	numberOfNodes--;

}

/*
* Remove x from the tree. Nothing is done if x is not found.
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::erase(const Comparable & x)
{
	// search tree for item
	BST_Node *t = root;
	// traverse the tree using t and starting at root
	// terminate on on empty subtree or found value
	while (t != NULL && !(x == t->element))
		if (x < t->element)
			t = t->left;
		else
			t = t->right;

	// if item found, delete the node
	if (t != NULL) {
		erase(iterator(t, this));
		numberOfNodes--;
	}
	return;
}

/*  erase(iterator first, iterator last)
* erases all items in the range [first, last) in inorder.
* NOTE: the tree must not be empty.
* NOTE: postcondition: the number of BST_Nodes in the tree decreases by
the number of elements in the range [first, last)
*/
template <typename Comparable>
void BinarySearchTree<Comparable>::erase(iterator first, iterator last)
{
	if (root == NULL)
		throw
		underflowError("BinarySearchTree::erase(): tree is empty");

	iterator p = first;

	if (first == begin() && last == end())
	{
		//  
		// erase this entire BinarySearchTreetree from memory
		makeEmpty(root);

		// redundant for emphasis. tree is empty
		root = NULL;
	}
	else
		// erase each item in a subrange of the tree
		while (p != last) {
			erase(p++);
			numberOfNodes--;
		}
}


/*
* Private method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
	if (root == NULL)
		return NULL
	else return BinarySearchTree<Comparable>::findMax(root)->element;
}

/*
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template<typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const
{
	if (root == NULL)
		return NULL;
	else return BinarySearchTree<Comparable>::findMin(root)->element;
}

/*
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template<typename Comparable>
typename BinarySearchTree<Comparable>::BST_Node * BinarySearchTree<Comparable>::findMin(BST_Node *t) const
{
	if (t == NULL)
		return NULL;
	if (t->left == NULL)
		return t;
	return BinarySearchTree<Comparable>::findMin(t->left);
}

/*
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template<typename Comparable>
typename BinarySearchTree<Comparable>::BST_Node * BinarySearchTree<Comparable>::findMax(BST_Node *t) const
{
	if (t != NULL)
		while (t->right != NULL)
			t = t->right;
	return t;
}

/*
* Method to remove the BinarySearchTree from memory
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::printInOrder(BST_Node * t) const
{
	if (t == NULL)
		return;
	printInOrder(t->left);
	cout << " " << t->element << " ";
	printInOrder(t->right);
}
template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
	if (root != NULL)
	{
		makeEmpty(root);
	}
	root = NULL;
}

/*
* Private method to make subtree empty.
*/
template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BST_Node * & t)
{
	if (t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

/*
* Private method to clone subtree.
*/
template<typename Comparable>
typename BinarySearchTree<Comparable>::BST_Node * BinarySearchTree<Comparable>::clone(BST_Node *t) const
{
	if (t == NULL)
		return NULL;

	return new BST_Node(t->element, clone(t->left), clone(t->right));
}




