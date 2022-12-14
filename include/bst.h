#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <shape.h>
#include <functional>

template< typename T , typename _Comp >
class BinaryTree {

protected:

    struct Node {

        Node * left;
        Node * right;
        Node * parent;

        int balanceFactor ;

        T value;

        explicit Node( T value );

    };

public:

    Node * root;

    _Comp _comp;

public:

    BinaryTree( _Comp _comp );

    virtual ~BinaryTree();

public:

    virtual void add( T value );

    virtual bool remove( T value );

    bool find( T value );

    bool set( T oldValue , T newValue );

    int depth();

protected:

    bool find( T value , Node ** result );

    virtual int depth( Node * node );

public:

    void preOrder( );

    void inOrder( );
    

};

template<typename T , typename _Comp >
BinaryTree<T , _Comp >::Node::Node( T value ) : value( value ) , left( nullptr ) , right( nullptr ) , parent( nullptr ) {}

template<typename T , typename _Comp >
BinaryTree<T , _Comp >::BinaryTree( _Comp _comp ) : _comp( _comp ) , root( nullptr ) { } 

template<typename T , typename _Comp >
BinaryTree<T , _Comp >::~BinaryTree(){

    std::function<void(Node *)> del;
    
    del = [&]( Node * node ){
        if( node->left != nullptr ){
            del( node->left );
        }
        if( node->right != nullptr ){
            del( node->right );
        }
        delete node;
    };
    
    del( this->root );
}

template<typename T , typename _Comp >
void BinaryTree<T , _Comp >::add( T value ){
    Node * newNode = new Node( value );
        
    if( this->root == nullptr ){
    
        this->root = newNode;
    
    }else{

        Node * pNode ;
        Node * node = this->root;

        while( node != nullptr ){

            if( this->_comp( value , node->value ) ){

                pNode = node;
                node = node->left;

            }else{

                pNode = node;
                node = node->right;

            }

        }

        if( this->_comp( value , pNode->value ) ){

            pNode->left = newNode;
        
        }else{

            pNode->right = newNode;

        }

        newNode->parent = pNode;

    }
}


template<typename T , typename _Comp >
bool BinaryTree<T , _Comp >::remove( T value ){
    // 1?????????????????????????????????????????????
    // 2????????????????????????????????????????????????????????????????????????
    // 3?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????(???????????????avl??????????????????)
    //

    // the transplant just process the from.parent and to.child => the caller must process the from.child and from.child.parent
    std::function< void ( BinaryTree * , Node * , Node *) > transplant = []( BinaryTree * tree , Node * to , Node * from ){
        
        if( to->parent == nullptr ){ // to is the root of the tree , replace the root with from

            tree->root = from;

        }else if( to == to->parent->left ){

            to->parent->left = from;

        }else{

            to->parent->right = from;

        }

        if( from != nullptr ){
            
            from->parent = to->parent;

        }

    };


    
    // 1???find the node
    Node * target ;

    bool result = this->find( value , &target );

    if( !result ) return false;

    if( target->left == nullptr ){

        transplant( this , target , target->right );

    }else if( target->right == nullptr ){

        transplant( this , target , target->left );

    }else {
        
        // the target has next child 
        // 1???find the next node
        Node * pNext ;
        Node * next = target->right;

        while( next != nullptr ){

            pNext = next;
            next = next->left;

        }

        if( pNext == target->right ){

            // the pNext is the right child of the target => replace target with pNext
            transplant( this , target , pNext );
            
            // bind child and parent node , because of replaceing operation => the pNext has right child => just process the left branch of the pNext
            pNext->left = target->left;
            pNext->left->parent = pNext;

        }else{

            // the pNext is not the right child of the target => transplant pNext->right to pNext => transplant pNext to target
            transplant( this , pNext , pNext->right );

            // bind chind and parent node , replace pNext with pNext.right => process nothing

            // transplant target with pNext
            transplant( this , target , pNext );
            
            // process target->left.parent target->right.parent , pNext.left , pNext.right
            target->right->parent = pNext;
            target->left->parent = pNext;
            pNext->right = target->right;
            pNext->left = target->left;

        }

    }

    
    

    return false;

}

template<typename T , typename _Comp >
bool BinaryTree<T , _Comp >::find( T value ){
    
    Node ** node ;
    bool result = this->find( value , node );

    return result;
}

template<typename T , typename _Comp >
bool BinaryTree<T , _Comp >::set( T oldValue , T newValue ){

    Node ** targetNode;
    bool result = this->find( oldValue , targetNode );

    if( result ){

        (*targetNode)->value = newValue;

    }
    
    return result;

}

template<typename T , typename _Comp >
int BinaryTree<T , _Comp >::depth(){

    int d = this->depth( this->root );
    return d;

}

template<typename T , typename _Comp >
int BinaryTree<T , _Comp >::depth( Node * node ){
    if( node == nullptr ){
        return 0;
    }
    int lDepth = this->depth( node->left );
    int rDepth = this->depth( node->right );
    return ( lDepth > rDepth ? lDepth : rDepth ) + 1;
}

// protected

template<typename T , typename _Comp >
bool BinaryTree<T , _Comp >::find( T value , Node ** result ){
    Node * node = root;
    
    while( node != nullptr ){
        
        if( node->value == value ){

            *result = node;
            // finded
            return true;
        
        }
        
        if( this->_comp( value , node->value ) ){
        
            node = node->left;
        
        }else{
        
            node = node->right;
        
        }

    }

    return false;

}


//traverse 

template<typename T , typename _Comp >
void BinaryTree<T , _Comp >::preOrder( ){

    std::function< void( Node * ) > traverse;
    traverse = [&]( Node * node ){

        if( node != nullptr ){
            
            std::cout << node->value.x << " ";
            traverse( node->left );
            traverse( node->right );

        
        };

    };

    traverse( this->root );
    std::cout << std::endl;

}

template<typename T , typename _Comp >
void BinaryTree<T , _Comp >::inOrder( ){

    std::function< void( Node * ) > traverse;
    traverse = [&]( Node * node ){

        if( node != nullptr ){

            traverse( node->left );
            std::cout << node->value.x << " ";
            traverse( node->right );

        
        };

    };

    traverse( this->root );
    std::cout << std::endl;

}



#endif