#include <bst.h>

template< typename T , typename C >
template< typename _C >
template< typename E >
bool BinaryTree< T , C >::Comparer<_C>::operator()(E e1 ,E e2 ){
    return this->_compare(e1,e2);
}

template< typename T , typename C >
BinaryTree< T , C >::Node::Node( T value ) : value( value ) {
    this->left = nullptr;
    this->right = nullptr;
}


template<typename T , typename C> 
BinaryTree< T , C >::BinaryTree(){
    root = nullptr;
}

template<typename T , typename C> 
BinaryTree< T , C >::~BinaryTree(){
    remove( root );
}

template<typename T , typename C> 
void BinaryTree< T , C >::add( T value ){
    Node * node = new BinaryTree::Node( value );
    if( this->root = nullptr ) { this->root = node; }
    else{
        Node * parent = root;
        // bool value C( parent , node );
    }
}

template<typename T , typename C> 
bool BinaryTree< T , C >::del( T value ){
    return false;
}

template<typename T , typename C> 
bool BinaryTree< T , C >::find( T value ){
    return false;
}

template<typename T , typename C> 
bool BinaryTree< T , C >::set( T oldValue , T newValue ){
    return false;
}


template<typename T , typename C>
void BinaryTree< T , C >::remove( Node * node ){
    if( node != nullptr ){
        remove( node->left );
        remove( node->right );
        remove( node );
    }
}