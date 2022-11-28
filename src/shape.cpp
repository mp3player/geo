#include <shape.h>
#include <cmath>

// Shape

Shape::Shape( float x , float y ) : center( x , y ) {}

Shape::Shape( glm::vec2 center ) : center( center ) {}

void Shape::add( Shape * child ){
    this->children.push_back( child );
}

std::vector< glm::vec2 > Shape::getPoints(){
    return std::vector< glm::vec2 >();
}

std::vector< unsigned int > Shape::getIndexes(){
    return std::vector< unsigned int >();
}

void Shape::updateWorldTransform( glm::mat3 world ){
    this->worldTransform = world * this->transform;
    this->inverseWorldTransform = glm::inverse( this->worldTransform );
    for( Shape * shape : children ){
        shape->updateWorldTransform( this->worldTransform );
    }
}

void Shape::updateTransform( ){
    // apply rotate , 
    // apply scale
    // apply translate
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate( transform , this->rotation , glm::vec3(0.0f,0.0f,1.0f) );
    transform = glm::scale( transform , glm::vec3(this->scale,1.0f));
    transform = glm::translate( transform , glm::vec3(this->center , 0.0f) );

    this->transform = glm::mat3(transform);
    this->inverseTransform = glm::inverse( this->transform );
}

void Shape::rotate( float a ){
    this->rotation += a;
    this->updateTransform();
}

// Rectangle

Rectangle::Rectangle( float width , float height , float x , float y ) : size( width , height ) , Shape( x , y ) {}

std::vector< glm::vec2 > Rectangle::getPoints(){
    glm::vec2 p0 = glm::vec2( this->center );
    glm::vec2 p1 = glm::vec2( this->center.x + this->size.x , this->center.y );
    glm::vec2 p2 = glm::vec2( this->center.x + this->size.x , this->center.y + this->size.y );
    glm::vec2 p3 = glm::vec2( this->center.x , this->center.y + this->size.y );

    return std::vector< glm::vec2 >{ p0 , p1 , p2 , p3 };
}

// Circle

Circle::Circle( float radius , float x , float y ) : radius( radius ) , Shape( center ) {}

std::vector< glm::vec2 > Circle::getPoints(){
    std::vector< glm::vec2 > points;
    for(float i = 0 ; i < 2 * M_PI ; i += .01f){
        float x = this->radius * cos( i );
        float y = this->radius * sin( i );
        points.push_back( glm::vec2{x,y} );
    }
    return points;
}

// Polygon

Polygon::Polygon() : Shape() {}

Polygon::Polygon( std::vector<glm::vec2> vertices ) : Shape(){
    this->vertices = std::vector< glm::vec2 >();
    for( glm::vec2 & v : vertices ){
        this->vertices.push_back( glm::vec2{v.x,v.y} );
    }
    
}

std::vector< glm::vec2 > Polygon::getPoints(){
    return this->vertices;
}

// LineSegment

LineSegment::LineSegment( glm::vec2 v0 , glm::vec2 v1 ){
    if( v0.y < v1.y ){
        this->upper = v1;
        this->lower = v0;
    }else{
        this->upper = v0;
        this->lower = v1;
    }
}

std::vector<glm::vec2> LineSegment::getPoints(){
    return std::vector<glm::vec2> { this->upper , this->lower };
}



