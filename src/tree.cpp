#ifndef _TREE_H_
#define _TREE_H_

#include <functional>
#include <iostream>

template<typename T >
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	T value;
	int factor;
	TreeNode(T value);
};

template <typename T , typename _Comp >
class AVL
{
	typedef TreeNode<T> Node;
	Node* root;
	_Comp _comp;
public:
	explicit AVL( _Comp _comp );
	virtual ~AVL();

public:
	Node* add(T value);
	Node* find(T value);
	bool remove(T value);

	void preOrder( std::function<void(T)> handler );
	void inOrder(std::function<void(T)> handler);

	int computeBalanceFactor(Node* node);

	int depth(Node*);
	void rebalance(Node*);
	void rotateLeft(AVL* tree , Node*node);
	void rotateRight(AVL* tree , Node* node);
};


template<typename T, typename _Comp>
inline AVL<T, _Comp>::AVL(_Comp _comp):_comp(_comp) , root(nullptr)
{
}

template<typename T, typename _Comp>
inline AVL<T, _Comp>::~AVL()
{
	std::function<void(Node*)> del = [&](Node* node) {
		if (node != nullptr) {
			del(node->left);
			del(node->right);
			delete node;
		}
	};
}

template<typename T, typename _Comp>
inline TreeNode<T>* AVL<T, _Comp>::add(T value)
{
	Node* newNode = new Node(value);
	if (this->root == nullptr) {
		this->root = newNode;
		return newNode;
	}
	Node* node = this->root;
	Node* p = node;
	while (node != nullptr) {
		p = node;
		if (this->_comp(value, node->value) >= 0) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	if (this->_comp(value, p->value) >= 0) {
		p->left = newNode;
		newNode->parent = p;
	}
	else {
		p->right = newNode;
		newNode->parent = p;
	}
	//rebalance(newNode);
	return newNode;
}

template<typename T, typename _Comp>
TreeNode<T>* AVL<T, _Comp>::find(T value)
{
	Node* node = this->root;
	while (node != nullptr) {
		if (this->_comp(node->value , value ) == 0) {
			return node;
		}
		if (this->_comp(value, node->value) > 0) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return nullptr;

}

template<typename T, typename _Comp>
bool AVL<T, _Comp>::remove(T value)
{

	// the transplant just process the from.parent and to.child => the caller must process the from.child and from.child.parent
	std::function< void(AVL*, Node*, Node*) > transplant = [](AVL* tree, Node* to, Node* from) {

		if (to->parent == nullptr)  // to is the root of the tree , replace the root with from
			tree->root = from;
		else if (to == to->parent->left) 
			to->parent->left = from;
		else
			to->parent->right = from;

		if (from != nullptr)
			from->parent = to->parent;

	};

	// 1、find the node
	
	Node * target = this->find(value);

	if (target == nullptr) return false;

	if (target->left == nullptr) {
		transplant(this, target, target->right);
	}
	else if (target->right == nullptr) {
		transplant(this, target, target->left);
	}
	else {
		// the target has next child 
		// 1、find the next node
		
		Node* next = target->right;
		Node* pNext = next;

		while (next != nullptr) {

			pNext = next;
			next = next->left;

		}

		if (pNext == target->right) {

			// the pNext is the right child of the target => replace target with pNext
			transplant(this, target, pNext);

			// bind child and parent node , because of replaceing operation => the pNext has right child => just process the left branch of the pNext
			pNext->left = target->left;
			pNext->left->parent = pNext;

		}
		else {

			// the pNext is not the right child of the target => transplant pNext->right to pNext => transplant pNext to target
			transplant(this, pNext, pNext->right);

			// bind chind and parent node , replace pNext with pNext.right => process nothing

			// transplant target with pNext
			transplant(this, target, pNext);

			// process target->left.parent target->right.parent , pNext.left , pNext.right
			target->right->parent = pNext;
			target->left->parent = pNext;
			pNext->right = target->right;
			pNext->left = target->left;

		}

	}


	delete target;

	return true;
}

template<typename T, typename _Comp>
void AVL<T, _Comp>::preOrder(std::function<void(T)> handler)
{
	std::function< void(Node*) > traverse = [&]( Node * node) {
		if (node != nullptr) {
			handler(node->value);
			traverse(node->left);
			traverse(node->right);
		}
	};

	traverse(this->root);
}

template<typename T, typename _Comp>
inline void AVL<T, _Comp>::inOrder(std::function<void(T)> handler)
{
	std::function< void(Node*) > traverse = [&](Node* node) {
		if (node != nullptr) {
			traverse(node->left);
			handler(node->value);
			traverse(node->right);
		}
	};
	traverse(this->root);
}

template<typename T, typename _Comp>
inline int AVL<T, _Comp>::computeBalanceFactor(Node* node)
{
	int rDepth = this->depth(node->right);
	int lDepth = this->depth(node->left);
	int factor = rDepth - lDepth;
	if (node != nullptr) node->factor = factor;
	return factor;
}

template<typename T, typename _Comp>
inline int AVL<T, _Comp>::depth(Node* node)
{
	if (node == nullptr) return 0;
	int lDepth = this->depth(node->left);
	int rDepth = this->depth(node->right);
	return ( lDepth > rDepth ? lDepth : rDepth ) + 1;
}

template<typename T, typename _Comp>
inline void AVL<T, _Comp>::rotateLeft(AVL* tree, Node* node)
{
	Node* child = node->right;
	if (node->parent == nullptr) { // node is root
		tree->root = child;
	}
	else if (node->parent->left == node) { // node is left child of it's parent
		node->parent->left = child;
	}
	else { // node is right child of it's parent
		node->parent->right = child;
	}
	child->parent = node->parent;
	node->parent = child;
	node->right = child->left;
	if (child->left != nullptr) child->left->parent = node;
	child->left = node;

}

template<typename T, typename _Comp>
inline void AVL<T, _Comp>::rotateRight( AVL * tree , Node*node)
{
	Node* child = node->left;
	if (node->parent == nullptr) {
		tree->root = child;
	}
	else if (node == node->parent->left) {
		node->parent->left = child;
	}
	else {
		node->parent->right = child;
	}
	child->parent = node->parent;
	node->parent = child;
	node->left = child->right;
	if (child->right != nullptr) child->right->parent = node;
	child->right = node;
}

template<typename T, typename _Comp>
inline void AVL<T, _Comp>::rebalance(Node* node)
{
	// find the unbalanced node
	int factor;
	while ( node != nullptr ) {
		factor = this->computeBalanceFactor(node);
		if (factor <= -2 || factor >= 2)break;
		node = node->parent;
	}
	// there exists not a balanced subtree 
	if (node == nullptr) {
		return;
	}
	// process the true
	if (factor == 2) {
		Node* right = node->right;
		int rFactor = right->factor;
		if (rFactor == 1) {
			rotateLeft(this,node);
		}
		else {
			rotateRight(this, right);
			rotateLeft(this, node);
		}
	}
	else if (factor == -2) {
		Node* left = node->left;
		int rFactor = left->factor;
		if (rFactor == -1) {
			rotateRight(this, node);
		}
		else {
			rotateLeft(this, left);
			rotateRight(this, node);
		}
	}
}

template<typename T>
inline TreeNode<T>::TreeNode(T value):left(nullptr),right(nullptr),parent(nullptr),value(value),factor(0)
{
}


#endif