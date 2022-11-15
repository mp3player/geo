#include <bst.h>
#include <functional>

template<typename T , typename _Comparer >
BinaryTree<T , _Comparer >::Node::Node( T value ) : value( value ) , left( nullptr ) , right( nullptr ) , parent( nullptr ) {}

template<typename T , typename _Comparer >
BinaryTree<T , _Comparer >::BinaryTree( _Comparer comparer ) : comparer( comparer ) , root( nullptr ) { } 

// template<typename T , typename _Comparer >
// BinaryTree<T , _Comparer >::~BinaryTree(){
    // this->del( this->root );
// }

template<typename T , typename _Comparer >
void BinaryTree<T , _Comparer >::add( T value ){
    Node * newNode = new Node( value );
        
    if( this->root == nullptr ){
    
        this->root = newNode;
    
    }else{

        Node * pNode ;
        Node * node = this->root;

        while( node != nullptr ){

            if( value.x < node->value.x ){

                pNode = node;
                node = node->left;

            }else{

                pNode = node;
                node = node->right;

            }

        }

        if(value.x < pNode->value.x ){

            pNode->left = newNode;
        
        }else{

            pNode->right = newNode;

        }

        newNode->parent = pNode;

    }
}

/*
template<typename T , typename _Comparer >
bool BinaryTree<T , _Comparer >::remove( T value ){
    // 1、如果该节点没有孩子，直接删除
    // 2、如果该节点只有一个孩子，那么直接用孩子节点替换
    // 3、如果该节点两个孩子都存在，那么找它的中序遍历的后继节点（前驱节点）放在该位置(也可以使用avl树的平衡操作)
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


    
    // 1、find the node
    Node * target ;

    bool result = this->find( value , &target );

    if( !result ) return false;

    if( target->left == nullptr ){

        transplant( this , target , target->right );

    }else if( target->right == nullptr ){

        transplant( this , target , target->left );

    }else {
        
        // the target has next child 
        // 1、find the next node
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

template<typename T , typename _Comparer >
bool BinaryTree<T , _Comparer >::find( T value ){
    
    Node ** node ;
    bool result = this->find( value , node );

    return result;
}

template<typename T , typename _Comparer >
bool BinaryTree<T , _Comparer >::set( T oldValue , T newValue ){

    Node ** targetNode;
    bool result = this->find( oldValue , targetNode );

    if( result ){

        (*targetNode)->value = newValue;

    }
    
    return result;

}

template<typename T , typename _Comparer >
int BinaryTree<T , _Comparer >::depth(){

    // int d = this->depth( this->root );
    return 2;

}

*/
// protected

// template<typename T , typename _Comparer >
// template< T >
// void BinaryTree<T , _Comparer >::del( Node<T> * node ){

//     if( node != nullptr ){

//         this->del( node->left );
//         this->del( node->right );
//         node->left = nullptr;
//         node->right = nullptr;
//         delete node;

//     }

// }

template<typename T , typename _Comparer >
bool BinaryTree<T , _Comparer >::find( T value , Node ** result ){
    Node * node = root;
    
    while( node != nullptr ){
        
        if( node->value == value ){

            *result = node;
            // finded
            return true;
        
        }
        
        if( value.x < node->value.x ){
        
            node = node->left;
        
        }else{
        
            node = node->right;
        
        }

    }

    return false;

}

// template<typename T , typename _Comparer >
// int BinaryTree<T , _Comparer >::depth( Node * node ){
    
//     if( node == nullptr ) return 0;

//     int lDepth = depth( node->left );
//     int rDepth = this->depth( node->right );

//     return 1 + ( lDepth > rDepth ? lDepth : rDepth );

// }

//traverse 

template<typename T , typename _Comparer >
void BinaryTree<T , _Comparer >::preOrder( ){

    std::function< void( Node * ) > traverse;
    traverse = [&]( Node * node ){

        if( node != nullptr ){

            traverse( node->left );
            traverse( node->right );
            std::cout << node->value << std::endl;
        
        };

    };

    traverse( this->root );

}

template<typename T , typename _Comparer >
void BinaryTree<T , _Comparer >::inOrder( ){

    std::function< void( Node * ) > traverse;
    traverse = [&]( Node * node ){

        if( node != nullptr ){

            traverse( node->left );
            std::cout << node->value << std::endl;
            traverse( node->right );

        
        };

    };

    traverse( this->root );

}


//------------------- avl tree ---------------
/*

AVLTree::AVLTree() : BinaryTree() { };

void AVLTree::add( Vector2f value ){
    
    BinaryTree::add( value );

    // rebalance

}

bool AVLTree::remove( Vector2f value ){

    bool result = BinaryTree::remove( value );

    // reblance
    
    return result;

}

void AVLTree::rotateLeft( AVLTree * tree , Node * node ){
    
    Node * y = node->right ;
    node->right = y->left;

    // process the left child of y
    if( y->left != nullptr ){

        y->left->parent = node;

    }

    // process y 
    y->parent = node->parent;
    if( node->parent == nullptr ){

        tree->root = y;

    }else if( node->parent->left = node ){

        node->parent->left = y;

    }else{

        node->parent->right = y;

    }

    y->left = node;
    node->parent = y;

}

void AVLTree::rotateRight( AVLTree * tree , Node * node ){

    Node * x = node->left ;

    // process child of node
    node->left = x;
    if( x->right != nullptr ){ 

        x->right->parent = node;

    }

    if( node->parent == nullptr ){

        tree->root = x;

    }else if( node->parent->left == node ){

        node->parent->left = x;

    }else{

        node->parent->right = x;

    }

    x->parent = node->parent;
    node->parent = x;

}


*/