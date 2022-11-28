#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

struct Shape {

    std::vector< Shape * > children;

    glm::vec2 center;

    explicit Shape( float x = 0.0f , float y = 0.0f ) ;

    explicit Shape( glm::vec2 center );

    void add( Shape * child );

    virtual std::vector< glm::vec2 > getPoints();

    virtual std::vector< unsigned int > getIndexes();

};

struct Rectangle : Shape {

    glm::vec2 size;

    explicit Rectangle( float width = 1.0f , float height = 1.0f , float x = 0.0f , float y = 0.0f );
    
    explicit Rectangle( glm::vec2 size , glm::vec2 center ); 

    std::vector< glm::vec2 > getPoints();

};

struct Circle : Shape {

    float radius;

    explicit Circle( float radius , float x = 0.0f , float y =0.0f ) ;

    std::vector< glm::vec2 > getPoints();

};

struct Polygon : Shape {

    std::vector< glm::vec2 > vertices;

    explicit Polygon( );

    explicit Polygon( std::vector< glm::vec2 > vertices );

    std::vector< glm::vec2 > getPoints();

};

struct LineSegment : Shape {
    glm::vec2 upper;
    glm::vec2 lower;
    explicit LineSegment( glm::vec2 v0 , glm::vec2 v1 );
    std::vector< glm::vec2 > getPoints();
};


#endif