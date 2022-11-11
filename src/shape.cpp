#include <shape.h>
#include <cmath>
#include <iostream>

// Vector2

Vector2f::Vector2f( float x , float y ) : x(x) , y(y) {}

Vector2f::Vector2f( const Vector3f & v ) : x(v.x) , y(v.y) {}

Vector2f Vector2f::operator + (Vector2f v){
    return Vector2f( this->x + v.x , this->y + v.y );
}

Vector2f Vector2f::operator - (Vector2f v){
    return Vector2f( this->x - v.x , this->y - v.y );
}

Vector2f Vector2f::operator * (Vector2f v){
    return Vector2f( this->x * v.x , this->y - v.y );
}

Vector2f Vector2f::operator * (float s){
    return Vector2f( s * this->x , s * this->y );
}

Vector2f operator * ( float s , Vector2f v){
    return s * v;
}

float Vector2f::length(){
    return std::sqrt( this->x * this->x + this->y * this->y );
}

float Vector2f::dot( Vector2f v ){
    return this->x * v.x + this->y * v.y;
}

bool Vector2f::operator == (Vector2f v){
    return (this->x == v.x) && (this->y == v.y) ;
}

// Vector3

Vector3f::Vector3f( float x , float y , float z ) :x(x) , y(y) , z(z) {}

Vector3f::Vector3f( const Vector2f & v ) : x(v.x) , y(v.y) , z(1.0f) {}

Vector3f Vector3f::cross( Vector3f v ){
    // this x v
    float x = this->y * v.z - this->z * v.y;
    float y = this->z * v.x - this->x * v.z;
    float z = this->x * v.y - this->y * v.x;

    return Vector3f(x,y,z);
}

// Shape

Shape::Shape( float x , float y ) : center( x , y ) {}

Shape::Shape( Vector2f center ) : center( center ) {}

void Shape::add( Shape * child ){
    this->children.push_back( child );
}

std::vector< Vector2f > Shape::getPoints(){
    return std::vector< Vector2f >();
}

// Rectangle

Rectangle::Rectangle( float width , float height , float x , float y ) : size( width , height ) , Shape( x , y ) {}

std::vector< Vector2f > Rectangle::getPoints(){
    Vector2f p0 = Vector2f( this->center );
    Vector2f p1 = Vector2f( this->center.x + this->size.x , this->center.y );
    Vector2f p2 = Vector2f( this->center.x + this->size.x , this->center.y + this->size.y );
    Vector2f p3 = Vector2f( this->center.x , this->center.y + this->size.y );

    return std::vector< Vector2f >{ p0 , p1 , p2 , p3 };
}

// Circle

Circle::Circle( float radius , float x , float y ) : radius( radius ) , Shape( center ) {}

std::vector< Vector2f > Circle::getPoints(){
    std::vector< Vector2f > points;
    for(float i = 0 ; i < 2 * M_PI ; i += .01f){
        float x = this->radius * cos( i );
        float y = this->radius * sin( i );
        points.push_back( Vector2f{x,y} );
    }
    return points;
}

// Polygon

Polygon::Polygon() : Shape() {}

Polygon::Polygon( std::vector<Vector2f> vertices) : Shape(){
    this->vertices = std::vector< Vector2f >();
    for( Vector2f & v : vertices ){
        this->vertices.push_back( Vector2f{v.x,v.y} );
    }
    
}

std::vector< Vector2f > Polygon::getPoints(){
    return this->vertices;
}

