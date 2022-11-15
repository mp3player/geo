#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <shape.h>

template< typename T , typename _Comparer >
class BinaryTree {

public:

    struct Node {

        Node * left;
        Node * right;
        Node * parent;
        T value;

        explicit Node( T value );

    };

public:

    Node * root;

    _Comparer comparer;

public:

    BinaryTree( _Comparer comparer );

    // virtual ~BinaryTree();

public:

    virtual void add( T value );

    virtual bool remove( T value );

    bool find( T value );

    bool set( T oldValue , T newValue );

    int depth();

public:

    void del( T * node );

    bool find( T value , Node ** result );

    virtual int depth( T * node );

public:

    void preOrder( );

    void inOrder( );
    

};

// AVL tree
/*

template< typename T , typename _Comparer> 
class AVLTree : public BinaryTree< T , _Comparer > {


public:

    AVLTree() ; 

public:

    void add( Vector2f value );

    bool remove( Vector2f value );

private:

    void rotateLeft( AVLTree * tree , Vector2fNode * node );

    void rotateRight( AVLTree *tree , Vector2fNode * node );



};

*/

#endif