#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <functional>


template< typename T , typename C >
class BinaryTree {

public:
    template< typename _C >
    struct Comparer {
        _C _compare;
        template< typename E >
        bool operator()( E e1 , E e2 );
    };
    struct Node {
        Node * left;
        Node * right;
        Node * parent;
        T value;
        Node( T value );

    };

public:
    Node * root;

public:

    BinaryTree();

    virtual ~BinaryTree();

    virtual void add( T value );

    virtual bool del( T value );

    bool find( T value );

    bool set( T oldValue , T newValue );

private:

    void remove( Node * node );

};

#endif