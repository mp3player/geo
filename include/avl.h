#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <bst.h>



template< typename T , typename _Comp > 
class AVLTree : public BinaryTree< T , _Comp > {

public:

    AVLTree( _Comp _comp );

public:

    void add( T value );

    bool remove( T value );

private:

    void rotateLeft( AVLTree * , typename BinaryTree< T , _Comp >::Node * );

    void rotateRight( AVLTree * , typename BinaryTree< T , _Comp >::Node * );

    void add( T value , typename BinaryTree< T , _Comp >::Node ** );

    int computeBalanceFactor( typename BinaryTree< T , _Comp >::Node * );

    void updateBalanceFactor( typename BinaryTree< T , _Comp>::Node * );

    void rebalance( typename BinaryTree< T , _Comp >::Node * );
};


template< typename T , typename _Comp > 
AVLTree<T , _Comp>::AVLTree( _Comp _comp ) : BinaryTree< T , _Comp >( _comp ){
    
};

template< typename T , typename _Comp > 
void AVLTree<T , _Comp>::add( T value ){
    
    typename BinaryTree< T , _Comp>::Node * node = nullptr ;
    this->add( value , &node );



    this->rebalance( node );
    


    // there exists unbalance in the tree which root is node;
    // process the tree 
    // 

}

template< typename T , typename _Comp > 
bool AVLTree<T , _Comp>::remove( T value ){

    // remove => rebalance
    bool result = BinaryTree< T , _Comp >::remove( value );
    // rebalace from the leaves of the tree


    // rotate => remove => rebalance

    return false;

}

// private

template< typename T , typename _Comp > 
void AVLTree<T , _Comp>::rotateLeft( AVLTree * tree , typename BinaryTree< T , _Comp >::Node * node ){


    // BF(node) == 2 => the right depth of node is 2 greater than the left => the right exists
    typename BinaryTree< T , _Comp >::Node * child = node->right ;

    // move child to the node
    if( node->parent == nullptr ){
        // the node is root
        tree->root = child;
    }else if( node == node->parent->left ){
        node->parent->left = child;
    }else{
        node->parent->right = child;
    }
    child->parent = node->parent;
    // move child.left to node.right
    node->right = child->left;
    if( child->left != nullptr ) child->left->parent = node;
    //
    node->parent = child;
    child->left = node;

}

template< typename T , typename _Comp > 
void AVLTree<T , _Comp>::rotateRight( AVLTree * tree , typename BinaryTree< T , _Comp >::Node * node ){

    // BF(node) == -2 => the right depth of node is 2 smaller than the left => the left exists
    typename BinaryTree< T , _Comp >::Node * child = node->left ;

    if( node->parent == nullptr ){
        tree->root = child;
    }else if( node == node->parent->left ){
        node->parent->left = child;
    }else{
        node->parent->right = child;
    }
    child->parent = node->parent;
    
    // child->right
    node->left = child->right;
    if( child->right != nullptr ) child->right->parent = node;

    node->parent = child;
    child->right = node;

}

template< typename T , typename _Comp > 
void AVLTree<T , _Comp>::add( T value , typename BinaryTree< T , _Comp >::Node ** target ){
    using Node = typename BinaryTree< T , _Comp >::Node;

    Node * newNode = new Node(value);
    *target = newNode;

    if( this->root == nullptr ){
        this->root = newNode;
        return ;
    }
    Node * node = this->root;
    Node * p = node;
    while( node != nullptr ){
        p = node;
        if( this->_comp( value , node->value) ) node = node->left;
        else node = node->right;
    }
    if( this->_comp( value , p->value) ) p->left = newNode;
    else p->right = newNode;

    newNode->parent = p;

}

template< typename T , typename _Comp >
int AVLTree< T , _Comp >::computeBalanceFactor( typename BinaryTree< T , _Comp>::Node * node ){
    if( node != nullptr ){
        int lDepth = BinaryTree< T , _Comp > ::depth( node->left );
        int rDepth = BinaryTree< T , _Comp > ::depth( node->right );
        int factor = rDepth - lDepth;
        node->balanceFactor = factor;
        return factor;
    }
    return -100;
}

template< typename T , typename _Comp >
void AVLTree< T , _Comp >::updateBalanceFactor( typename BinaryTree< T , _Comp >::Node * node ){
    // update the balance factor of the tree
    std::cout << ( node == nullptr ) << std::endl;
    if( node != nullptr ){
        this->computeBalanceFactor( node );
        this->updateBalanceFactor( node->parent );
    }
}

template< typename T , typename _Comp >
void AVLTree< T , _Comp >::rebalance( typename BinaryTree< T , _Comp >::Node * node ){
    using Tree = AVLTree< T , _Comp >;
    using Node = typename BinaryTree< T , _Comp >::Node;

    // update balance factor when rebalanced

    // find the unbalance node 
    Node * tmp = node;
    int factor ;
    while( tmp != nullptr ){
        factor = this->computeBalanceFactor( tmp );
        if( factor == -2 || factor == 2 ) break;
        tmp = tmp->parent;
    }

    if( factor == 2 ){
        // apply balance operation
        int rightFactor = this->computeBalanceFactor( tmp->right );
        if( rightFactor == 1 ){
            this->rotateLeft( this , tmp );
        }else if( rightFactor == - 1 ){
            this->rotateRight( this , tmp->right );
            this->rotateLeft( this , tmp );
        }else{
            std::cout << "error" << std::endl;
        }

    }else if( factor == -2 ){
        int leftFactor = this->computeBalanceFactor( tmp->left );
        if( leftFactor == -1 ){
            this->rotateRight( this , tmp );
        }else if( leftFactor == 1 ){
            this->rotateLeft( this , tmp->left );
            this->rotateRight( this , tmp );
        }else{
            std::cout << "error" << std::endl;
        }
    }else{
        // balanced 
        //std::cout << 123 << std::endl;
    }

}




#endif