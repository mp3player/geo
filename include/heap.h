#ifndef _HEAP_H_
#define _HEAP_H_

#include <utility>
#include <iostream>

template <typename T , typename _Comp > 
class Heap{

public:

    int _capacity;
    int _size;
    T * datum;

    _Comp _comp;

public: 

    explicit Heap( _Comp _comp , int = 1 );

    ~Heap();

public:

    void add( T value );

    bool pop( T & value );

    int size() const;

    bool empty() const ; 

private:

    bool full() const ;

    void expand();

    void shiftDown( int );

    void shiftUp( int );



};

template< typename T , typename _Comp >
Heap<T , _Comp>::Heap( _Comp _comp , int capacity ) : _comp( _comp ) , _capacity( capacity ) , _size(0) {
    datum = new T[ capacity ];
}

template< typename T , typename _Comp >
Heap<T , _Comp>::~Heap(){
    delete []datum;
}

template< typename T , typename _Comp >
void Heap<T , _Comp>::add( T value ){
    if( full() ) expand();
    datum[_size] = value;
    this->shiftUp( _size );
    _size += 1;
}

template< typename T , typename _Comp >
bool Heap<T , _Comp>::pop( T & value ){
    if( _size <= 0 ) return false;

    // get value
    value = datum[0];

    // swap the first the the last
    std::swap( datum[0] , datum[_size - 1] ); 

    // remove the last 
    _size -= 1;
    
    // shift down
    this->shiftDown(0);

    return true;
}

template< typename T , typename _Comp >
int  Heap<T , _Comp>::size() const {
    return this->_size;
}

template< typename T , typename _Comp >
bool Heap<T , _Comp>::empty() const {
    return _size == 0;
}

template< typename T , typename _Comp >
bool Heap<T , _Comp>::full() const {
    return _size >= _capacity;
}

template< typename T , typename _Comp >
void Heap<T , _Comp>::expand(){
    // re allocate memory 
    int __capacity = int( _capacity * 1.5 ) + 1;
    // copy the value
    T * tmp = datum;
    datum = new T[__capacity];
    for( int i = 0 ; i < _size ; ++ i ){
        datum[i] = tmp[i];
    }
    this->_capacity = __capacity;
    delete []tmp;
}

template< typename T , typename _Comp >
void Heap<T , _Comp>::shiftDown( int index ){
    int cIndex = index * 2 + 1;

    //reach the bottom of the tree
    if( cIndex >= _size ) return ;
    
    // the right child is greater
    if( cIndex + 1 < _size && this->_comp( datum[cIndex + 1] , datum[cIndex] ) ){
        cIndex += 1;
    }

    if( this->_comp( datum[cIndex] , datum[index] ) ){
        std::swap( datum[index] , datum[cIndex] );
        this->shiftDown( cIndex );
    }

}

template< typename T , typename _Comp >
void Heap<T , _Comp>::shiftUp( int index ){
    if( index <= 0) return ;

    int pIndex = ( index - 1 ) / 2;
    if( this->_comp( datum[index] , datum[pIndex] ) ){

        // swap the parent with the child
        // shiftUp
        std::swap( datum[index] , datum[pIndex] );

        this->shiftUp( pIndex );

    }
}


#endif