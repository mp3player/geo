#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

/**
 * properties of red-black tree
 * 1、the color of the node is red or black
 * 2、thre root of the tree is *black*
 * 3、thre leaves of the tree(nullptr) is black;
 * 4、the red node has two black child node;
 * 5、on the whole simple pathes from the node to leaves , there exists the same count of node; 
 * 
 * 
 */

#include <bst.h>

template< typename T , typename _Comp >
class RBTree : public BinaryTree< T , _Comp >{

typedef typename BinaryTree< T , _Comp >::Node BaseNode;

public:

    struct Node : public BaseNode {
        int a : 2;
        bool red;
        Node( T value );
    };

public:

    RBTree( _Comp _comp );

    void add( T value ) override;

    bool remove( T value ) override;


private:

    bool add( T value , Node ** );

    void rotateLeft( RBTree * , Node * );

    void rotateRight( RBTree * , Node *  );

    void rebalance( RBTree * , Node * );

    int balckHeight( Node * );
    

};


// create new Node and set the color to black
template< typename T , typename _Comp >
RBTree< T , _Comp >::Node::Node( T value ) : BinaryTree< T , _Comp >::Node( value ) , red( false ) {}

template< typename T , typename _Comp >
RBTree<T , _Comp>::RBTree( _Comp _comp ) : BinaryTree< T , _Comp > ( _comp ) {};

template< typename T , typename _Comp >
void RBTree< T , _Comp >::add( T value ) {
    Node * target;
    bool result = this->add( value , &target );
    if( !result ){
        return ;
    }
}

template< typename T , typename _Comp >
bool RBTree< T , _Comp >::remove( T value ){
    return false;
}


// private 

template< typename T , typename _Comp >
bool RBTree< T , _Comp >::add( T value , Node ** target ) {
    
    Node * newNode = new Node( value );
    *target = newNode;

    if( this->root == nullptr ){
        this->root = newNode;
        return true;
    }

    Node * node = (Node *)this->root;
    Node * p = node;

    while( node != nullptr ){
        p = node;
        if( this->_comp( value , node->value) ){
            node = (Node*)node->left;
        }else{
            node = (Node*)node->right;
        }
    }

    if( this->_comp( value , p->value ) ){
        p->left = newNode;
    }else{
        p->right = newNode;
    }

    return true;
}

// rotate
template< typename T , typename _Comp >
void RBTree< T , _Comp >::rotateLeft( RBTree * tree , Node * node ){
    Node * child = node->right;
    if( node->parent == nullptr ){
        tree->root = child;
    }else if( node == node->parent->left ){
        node->parent->left = child;
    }else{
        node->parent->right = child;
    }
    child->parent = node;
    node->right = child->left;
    if( child->left != nullptr ) child->left->parent = node;
    child->left = node;
}

template< typename T , typename _Comp >
void RBTree< T , _Comp >::rotateRight( RBTree * tree , Node * node ){
    Node * child = node->left;
    if( node->parent == nullptr ){
        tree->root = child;
    }else if( node == node->parent->left ){
        node->parent->left = child;
    }else{
        node->parent->right = child;
    }
    child->parent = node;
    node->left = child->right;
    if(child->right != nullptr )child->right->parent = node;
    child->right = node;
}

template< typename T , typename _Comp >
void RBTree< T , _Comp >::rebalance( RBTree * tree , Node * ){

}

template< typename T , typename _Comp >
int RBTree< T , _Comp>::balckHeight( Node * node ){

    if( node == nullptr ){
        return 1;
    }

    int bh = this->balckHeight( node->left );

    if( !node->red ) bh += 1;

    return bh;
}

#endif