#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>
#include <iostream>

struct Vector2f ;
struct Vector3f ;

struct Vector2f {

    float x , y ;

    explicit Vector2f( float x = 0 , float y = 0 );

    explicit Vector2f( const Vector3f & v );

    Vector2f operator + (Vector2f v);

    Vector2f operator - (Vector2f v);

    Vector2f operator * (Vector2f v);

    Vector2f operator * (float s);

    friend Vector2f operator * ( float s , Vector2f v );

    float length();

    float squareLength();

    float dot( Vector2f v );

    bool operator == (Vector2f v);

    friend std::ostream & operator << ( std::ostream & cout , Vector2f v );

};

struct Vector3f {

    float x , y , z ;

    explicit Vector3f( float x = 0 , float y = 0 , float z = 0 );

    Vector3f( const Vector2f & v);

    Vector3f cross( Vector3f v );

    friend std::ostream && operator << ( std::ostream && cout , Vector3f v );

};

struct Shape {

    std::vector< Shape * > children;

    Vector2f center;

    explicit Shape( float x = 0.0f , float y = 0.0f ) ;

    explicit Shape( Vector2f center );

    void add( Shape * child );

    virtual std::vector< Vector2f > getPoints();

    virtual std::vector< unsigned int > getIndexes();

};

struct Rectangle : Shape {

    Vector2f size;

    explicit Rectangle( float width = 1.0f , float height = 1.0f , float x = 0.0f , float y = 0.0f );
    
    explicit Rectangle( Vector2f size , Vector2f center ); 

    std::vector< Vector2f > getPoints();

};

struct Circle : Shape {

    float radius;

    explicit Circle( float radius , float x = 0.0f , float y =0.0f ) ;

    std::vector< Vector2f > getPoints();

};

struct Polygon : Shape {

    std::vector< Vector2f > vertices;

    explicit Polygon( );

    explicit Polygon( std::vector< Vector2f > vertices );

    std::vector< Vector2f > getPoints();

};




#endif