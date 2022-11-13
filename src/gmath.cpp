#include <gmath.h>
#include <iostream>


float randFloat(float min , float max){
    
    float v = (float)(rand() % 10000) / 10000.0f;
    return v * (max - min) + min;
}

std::vector< Vector2f > randVector2f( int count , float min , float max ){
    std::vector< Vector2f > results;
    for( int i = 0 ; i < count ; ++ i ){
        float x = randFloat(min , max);
        float y = randFloat(min , max);

        results.push_back( Vector2f(x,y) );
    }
    return results;
}

// 

bool pointInLine( Vector2f p , Vector2f start , Vector2f end , float eps ){
    // the line is vertical to the x-axis
    if( start.x == end.x ){
        float minY = start.y < end.y ? start.y : end.y;
        float maxY = start.y > end.y ? start.y : end.y;

        if( p.x == start.x && p.y  > minY && p.y < maxY ) return true;
        return false;
    }
    float slope = ( end.y - start.y ) / ( end.x - start.x );
    float bias = end.y - slope * end.x;

    float y = slope * p.x + bias;
    if( p.y >= y - eps && p.y <= y + eps ) return true;
    return false;
}

bool pointInPolygon( Vector2f p , std::vector< Vector2f > ps ){

}

bool pointInCircle( Vector2f p , Vector2f center , float radius ){
    Vector2f dist = p - center;
    float sLength = dist.squareLength();
    float sR = radius * radius;

    if( sLength < sR ) return true;
    return false;

}