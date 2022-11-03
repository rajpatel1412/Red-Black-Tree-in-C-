#pragma once

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

template <class T1, class T2>
class NodeT
{
public:
	//object attributes
	T1 key;
	T2 value;
	NodeT<T1, T2>* left;
	NodeT<T1, T2>* right;
	NodeT<T1, T2>* parent;
	bool isBlack;

	//non-default constructor
	NodeT(T1 k, T2 val) : key(k), value(val), left(nullptr), right(nullptr), parent(nullptr), isBlack(false) {}
};

template <class T1, class T2>
class RedBlackTree
{
private:

	NodeT<T1, T2>* root;
	int numOfNodes;

	//helper methods
	NodeT<T1, T2>* bstinsert(const T1 k, const T2 val);
	void left_rotate(NodeT<T1, T2>* node);
	void right_rotate(NodeT<T1, T2>* node);
	void clear(NodeT<T1, T2>* node);
	void preOrderinsert(NodeT<T1, T2>* node);
	NodeT<T1, T2>* predecessor(NodeT<T1, T2>* node);
	bool isLeftChild(NodeT<T1, T2>* node);
	void treefix(NodeT<T1, T2>* node, NodeT<T1, T2>* par, bool isLeft);
	void inOrderSearch(NodeT<T1, T2>* node, T1& key1, T1& key2, vector<T2>& vec) const;
	void inOrderValues(NodeT<T1, T2>* node, vector<T2>& vec) const;
	void inOrderKeys(NodeT<T1, T2>* node, vector<T1>& vec) const;

public:
	
	//constructors
	RedBlackTree();
	RedBlackTree(const RedBlackTree & rbt);
	RedBlackTree& operator=(const RedBlackTree& rbt);
	~RedBlackTree();

	//mutators
	bool insert(const T1 k, const T2 val);
	bool remove(T1 target);

	//accessors
	bool search(T1 target) const;
	vector<T2> search(const T1 key1, const T1 key2) const;
	vector<T2> values() const;
	vector<T1> keys() const;
	int size() const;
	NodeT<T1, T2>* getRoot() const;
};

template <class T1, class T2>
RedBlackTree<T1, T2>::RedBlackTree()
{
	root = nullptr;
	numOfNodes = 0;
}

//deep copy method
//PARAM: a NodeT* root
//POST: traverses tree and inserts node into calling object
template <class T1, class T2>
void RedBlackTree<T1, T2>::preOrderinsert(NodeT<T1, T2>* node)
{
	if(node != nullptr)
	{
		this->insert(node->key, node->value);
		preOrderinsert(node->left);
		preOrderinsert(node->right);
	}
}

//copy constructor passes root of parameter to be deep copied into calling object
template <class T1, class T2>
RedBlackTree<T1, T2>::RedBlackTree(const RedBlackTree& rbt)
{
	this->root = nullptr;
	this->numOfNodes = 0;
	this->preOrderinsert(rbt.root);
}

//overloaded operator passes root of parameter to be deep copied into calling object, clears calling object and checks for self assignemnt
template <class T1, class T2>
RedBlackTree<T1, T2>& RedBlackTree<T1, T2>::operator=(const RedBlackTree& rbt)
{
	if(this == &rbt)
	{
		return *this;
	}

	this->clear(this->root);
	this->numOfNodes = 0;
	this->preOrderinsert(rbt.root);
	return *this;
}

//helper method for destructor
//PARAM: NodeT* (usually root)
//POST: traverses tree and deletes all nodes
template <class T1, class T2>
void RedBlackTree<T1, T2>::clear(NodeT<T1, T2>* node)
{
	if(node != nullptr)
	{
		clear(node->right);
		clear(node->left);
		delete node;
	}
}

//destructor passes calling object's root to helper method for enitre tree deletion
template <class T1, class T2>
RedBlackTree<T1, T2>::~RedBlackTree()
{
	clear(this->root);
	root = nullptr;
	numOfNodes = 0;
}

//helper method for insert, usual bst insert
//PARAM: templated parameters for key and value
//POST: creates nodes and inserts them into tree at the right place for an unbalanced BST
template <class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::bstinsert(const T1 k, const T2 val)
{
	NodeT<T1, T2>* newnode = new NodeT<T1, T2>(k, val);
	NodeT<T1, T2>* par = root;
	NodeT<T1, T2>* next = root;

	if(root == nullptr)
	{
		root = newnode;
		numOfNodes++;
		return newnode;
	}
	else
	{
		if(search(k) == false)
		{
			while(next != nullptr)
			{
				par = next;
				if(k < par->key)
				{
					next = par->left;
				}
				else
				{
					next = par->right;
				}
			}
			if(k < par->key)
			{
				par->left = newnode;
				newnode->parent = par;
			}
			else
			{
				par->right = newnode;
				newnode->parent = par;
			}
			numOfNodes++;
			return newnode;
		}
		return nullptr;
	}
}

//helper method for removal and insertion, algorithm as presented in class, rotates tree left
template <class T1, class T2>
void RedBlackTree<T1, T2>::left_rotate(NodeT<T1, T2>* node)
{
	NodeT<T1, T2>* temp = node->right;
	node->right = temp->left;
	if(temp->left != nullptr)
	{
		temp->left->parent = node;
	}

	temp->parent = node->parent;

	if(node->parent == nullptr)
	{
		root = temp;
	}
	else if(node == node->parent->left)
	{
		node->parent->left = temp;
	}
	else
	{
		node->parent->right = temp;
	}
	temp->left = node;
	node->parent = temp;
}

//helper method for removal and insertion, algorithm as presented in class, rotates tree right
template <class T1, class T2>
void RedBlackTree<T1, T2>::right_rotate(NodeT<T1, T2>* node)
{
	NodeT<T1, T2>* temp = node->left;
	node->left = temp->right;
	if(temp->right != nullptr)
	{
		temp->right->parent = node;
	}

	temp->parent = node->parent;

	if(node->parent == nullptr)
	{
		root = temp;
	}
	else if(node == node->parent->right)
	{
		node->parent->right = temp;
	}
	else
	{
		node->parent->left = temp;
	}
	temp->right = node;
	node->parent = temp;
}

//insertion algorithm as presented in class
template <class T1, class T2>
bool RedBlackTree<T1, T2>::insert(const T1 k, const T2 val)
{
	NodeT<T1, T2>* newnode = this->bstinsert(k, val);
	if(newnode == nullptr)
	{
		return false;
	}
	newnode->isBlack = false;
	while(newnode != root && newnode->parent->isBlack == false)
	{
		if(newnode->parent == newnode->parent->parent->left)
		{
			NodeT<T1, T2>* uncle = newnode->parent->parent->right;
			if(uncle == nullptr || uncle->isBlack == true)
			{
				if(newnode == newnode->parent->right)
				{
					newnode = newnode->parent;
					left_rotate(newnode);
				}
				newnode->parent->isBlack = true;
				newnode->parent->parent->isBlack = false;
				right_rotate(newnode->parent->parent);
			}
			else if(uncle->isBlack == false && uncle != nullptr) 
			{
				newnode->parent->isBlack = true;
				uncle->isBlack = true;
				newnode->parent->parent->isBlack = false;
				newnode = newnode->parent->parent;
			}
		}
		else
		{
			NodeT<T1, T2>* uncle = newnode->parent->parent->left;
			if(uncle == nullptr || uncle->isBlack == true)
			{
				if(newnode == newnode->parent->left)
				{
					newnode = newnode->parent;
					right_rotate(newnode);
				}
				newnode->parent->isBlack = true;
				newnode->parent->parent->isBlack = false;
				left_rotate(newnode->parent->parent);
				
				
			}
			else if(uncle->isBlack == false)
			{
				newnode->parent->isBlack = true;
				uncle->isBlack = true;
				newnode->parent->parent->isBlack = false;
				newnode = newnode->parent->parent;
			}
		}
	}
	root->isBlack = true;
	return true;
}

//hepler method for removal, returns a pointer to predecessor
template <class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::predecessor(NodeT<T1, T2>* node)
{
	NodeT<T1, T2>* pred = node->left;
	NodeT<T1, T2>* par = node;
	if(pred != nullptr)
	{
		par = pred;
		pred = pred->right;
	}
	return par;
}

//helper method for removal, returns true if parameter is a left child
template <class T1, class T2>
bool RedBlackTree<T1, T2>::isLeftChild(NodeT<T1, T2>* node)
{
	if(node->parent != nullptr && node == node->parent->left)
	{
		return true;
	}
	return false;
}

//helper method for removal, tree fix algorithm as presented in class
template <class T1, class T2>
void RedBlackTree<T1, T2>::treefix(NodeT<T1, T2>* node, NodeT<T1, T2>* par, bool isLeft)
{
	while(node != root && (node == nullptr || node->isBlack == true))
	{
		if(isLeft == true)
		{
			NodeT<T1, T2>* sibling = par->right;
			if(sibling->isBlack == false && sibling != nullptr)
			{
				sibling->isBlack = true;
				par->isBlack = false;
				left_rotate(par);
				sibling = par->right;
			}
			if(sibling->left == nullptr  || sibling->left->isBlack == true && sibling->right == nullptr || sibling->right->isBlack == true)
			{
				sibling->isBlack = false;
				node = par;
				par = par->parent;
			}
			else
			{
				if(sibling->right == nullptr || sibling->right->isBlack == true)
				{
					sibling->left->isBlack = true;
					sibling->isBlack = false;
					right_rotate(sibling);
					sibling = par->right;
				}
				sibling->isBlack = par->isBlack;
				par->isBlack = true;
				sibling->right->isBlack = true;
				left_rotate(par);
				node = root;
			}	
		}
		else
		{
			NodeT<T1, T2>* sibling = par->left;
			if(sibling->isBlack == false && sibling != nullptr)
			{
				sibling->isBlack = true;
				par->isBlack = false;
				right_rotate(par);
				sibling = par->left;
			}
			if(sibling->right == nullptr || sibling->right->isBlack == true && sibling->left == nullptr ||  sibling->left->isBlack == true)
			{
				sibling->isBlack = false;
				node = par;
				par = par->parent;
			}
			else
			{
				if(sibling->left == nullptr || sibling->left->isBlack == true)
				{
					sibling->right->isBlack = true;
					sibling->isBlack = false;
					left_rotate(sibling);
					sibling = par->left;
				}
				sibling->isBlack = par->isBlack;
				par->isBlack = true;
				sibling->left->isBlack = true;
				right_rotate(par);
				node = root;
			}	
		}
	}
	node->isBlack = true;
}

//remove alorithm as presented in class
template <class T1, class T2>
bool RedBlackTree<T1, T2>::remove(T1 target)
{
	NodeT<T1, T2>* node = root;
	while(node != nullptr)
	{
		if(target == node->key)
		{
			break;
		}
		else if(target < node->key)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	if(node == nullptr)
	{
		return false;
	}
	
	NodeT<T1, T2>* nd = nullptr;
	if(node->left == nullptr || node->right == nullptr)
	{
		nd = node;
	}
	else
	{
		nd = predecessor(node);
	}
	

	NodeT<T1, T2>* nod = nullptr;
	if(nd->left != nullptr)
	{
		nod = nd->left;
	}
	else
	{
		nod = nd->right;
	}
	if(nod != nullptr)
	{
		nod->parent = nd->parent;
	}
	
	if(nd->parent == nullptr)
	{
		root = nod;
		nod->isBlack = true;
		delete nd;
		numOfNodes--;
		return true;
	}
	else
	{
		if(nd == nd->parent->left)
		{
			nd->parent->left = nod;
		}
		else
		{
			nd->parent->right = nod;
		}
	}
	if(nd != node)
	{
		node->key = nd->key;
		node->value = nod->value;
	}
	bool isLeft = isLeftChild(nd);
	if(nd->isBlack == true)
	{
		treefix(nod, nd->parent, isLeft);
	}
	numOfNodes--;
	delete nd;
	return true;
}

//search function, returns true if key is in the tree
template <class T1, class T2>
bool RedBlackTree<T1, T2>::search(T1 target) const
{
	NodeT<T1, T2>* next = root;
	while(next != nullptr)
	{
		if(target == next->key)
		{
			return true;
		}
		else if(target < next->key)
		{
			next = next->left;
		}
		else
		{
			next = next->right;
		}
	}
	return false;
	
}

//helper method for search function, inserts values into parameter vecotr based on key range
template <class T1, class T2>
void RedBlackTree<T1, T2>::inOrderSearch(NodeT<T1, T2>* node, T1& key1, T1& key2, vector<T2>& vec) const
{
	if(node != nullptr)
	{
		inOrderSearch(node->left, key1, key2, vec);
		if(node->key >= key1 && node->key <= key2)
		{
			vec.push_back(node->value);
		}
		inOrderSearch(node->right, key1, key2, vec);
	}
}

//overloaded search function, returns vector of values between keys
template <class T1, class T2>
vector<T2> RedBlackTree<T1, T2>::search(T1 key1, T1 key2) const
{
	vector<T2> vec;
	inOrderSearch(root, key1, key2, vec);
	return vec;
}

//helper method for values function, inserts all values of tree into vector
template <class T1, class T2>
void RedBlackTree<T1, T2>::inOrderValues(NodeT<T1, T2>* node, vector<T2>& vec) const
{
	if(node != nullptr)
	{
		inOrderValues(node->left, vec);
		vec.push_back(node->value);
		inOrderValues(node->right, vec);
	}
}

//values function, returns a vector of values
template <class T1, class T2>
vector<T2> RedBlackTree<T1, T2>::values() const
{
	vector<T2> vec;
	if(root == nullptr)
	{
		return vec;
	}
	inOrderValues(root, vec);
	return vec;
}

//helper method for keys function, inserts all tree keys into vector paramter
template <class T1, class T2>
void RedBlackTree<T1, T2>::inOrderKeys(NodeT<T1, T2>* node, vector<T1>& vec) const
{
	if(node != nullptr)
	{
		inOrderKeys(node->left, vec);
		vec.push_back(node->key);
		inOrderKeys(node->right, vec);
	}
}

//keys function, returns vector of keys
template <class T1, class T2>
vector<T1> RedBlackTree<T1, T2>::keys() const
{
	vector<T1> vec;
	if(root == nullptr)
	{
		return vec;
	}
	inOrderKeys(root, vec);
	return vec;
}

//size function, returns the number of nodes, an attribute of the RedBlackTree
template <class T1, class T2>
int RedBlackTree<T1, T2>::size() const
{
	return numOfNodes;
}

//getRoot function, returns the root of the tree
template <class T1, class T2>
NodeT<T1, T2>* RedBlackTree<T1, T2>::getRoot() const
{
	return root;
}