#include <iostream>

struct Vector2f ;

struct Vector3f ;

struct Vector2f {

    float x , y ;

    explicit Vector2f( float x = 0 , float y = 0 );

    Vector2f( const Vector3f & v );

    Vector2f operator + (Vector2f v);

    Vector2f operator - (Vector2f v);

    Vector2f operator * (Vector2f v);

    Vector2f operator * (float s);

    friend Vector2f operator * ( float s , Vector2f v );

    float length();

    float squareLength();

    float dot( Vector2f v );

    Vector2f normalization();

    bool operator == (Vector2f v);

    friend std::ostream & operator << ( std::ostream & cout , Vector2f v );

};

struct Vector3f {

    float x , y , z ;

    explicit Vector3f( float x = 0 , float y = 0 , float z = 0 );

    Vector3f( const Vector2f & v);

    Vector3f operator + (Vector3f v);

    Vector3f operator - (Vector3f v);

    Vector3f operator * (Vector3f v);

    Vector3f operator * (float s);

    friend Vector3f operator * ( float s , Vector3f v );

    Vector3f cross( Vector3f v );

    float length();

    float dot( Vector3f v );

    Vector3f normalization( );

    friend std::ostream && operator << ( std::ostream && cout , Vector3f v );

};





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

float Vector2f::squareLength(){
    return this->x * this->x + this->y * this->y;
}

float Vector2f::dot( Vector2f v ){
    return this->x * v.x + this->y * v.y;
}

Vector2f Vector2f::normalization(){
    float len = this->length();
    if( len == 0 ){
        return *this;
    }else{
        return *this * ( 1.0f / len );
    }
}

bool Vector2f::operator == (Vector2f v){
    return (this->x == v.x) && (this->y == v.y) ;
}

std::ostream & operator << ( std::ostream & cout , Vector2f v ){
    cout << v.x << " " << v.y ;
    return cout;
}

// Vector3

Vector3f::Vector3f( float x , float y , float z ) :x(x) , y(y) , z(z) {}

Vector3f::Vector3f( const Vector2f & v ) : x(v.x) , y(v.y) , z(1.0f) {}

Vector3f Vector3f::operator + (Vector3f v){
    return Vector3f( this->x + v.x , this->y + v.y , this->z + v.z );
}

Vector3f Vector3f::operator - (Vector3f v){
    return Vector3f( this->x - v.x , this->y - v.y , this->z - v.z );
}

Vector3f Vector3f::operator * (Vector3f v){
    return Vector3f( this->x * v.x , this->y * v.y , this->z * v.z );
}

Vector3f Vector3f::operator * (float s){
    return Vector3f( this->x * s , this->y * s , this->z * s );
}

Vector3f operator * ( float s , Vector3f v ){
    return v.operator*(s);
}

Vector3f Vector3f::cross( Vector3f v ){
    // this x v
    float x = this->y * v.z - this->z * v.y;
    float y = this->z * v.x - this->x * v.z;
    float z = this->x * v.y - this->y * v.x;

    return Vector3f(x,y,z);
}

float Vector3f::length(){
    return std::hypot( this->x , this->y , this->z );
}

float Vector3f::dot( Vector3f v ){
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3f Vector3f::normalization(){
    float len = this->length();
    if( len == 0 ){
        return *this;
    }
    return *this * ( 1.0f / len );
}

std::ostream & operator << ( std::ostream & cout , Vector3f v ){
    cout << v.x << " " << v.y << " " << v.z ;
    return cout;
}
