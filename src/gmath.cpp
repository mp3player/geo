#include <gmath.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stack>


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
    return true;
}

bool pointInCircle( Vector2f p , Vector2f center , float radius ){
    Vector2f dist = p - center;
    float sLength = dist.squareLength();
    float sR = radius * radius;

    if( sLength < sR ) return true;
    return false;

}

// convex
// BF algorithm
// semi-optimization algorithm

std::vector< Vector2f > getConvex( std::vector< Vector2f > points ){
    // BF algorithm pseudo code
    // test line composed by two point that if it is the edge of the convex to get the border of the convex

    // sort the point => ascending order
    std::function< bool(Vector2f , Vector2f) > comparer = []( Vector2f a, Vector2f b ){
        if( a.x == b.x && a.y < b.y ) return true;
        if( a.x == b.x && a.y > b.y ) return false;
        return a.x < b.x;
    };
    std::vector< Vector2f >::iterator begin = points.begin();
    std::vector< Vector2f >::iterator end = points.end();
    
    std::sort<std::vector<Vector2f>::iterator , std::function< bool(Vector2f , Vector2f) >>( begin , end , comparer );

    // compute the turning direction
    std::function< bool( Vector2f , Vector2f , Vector2f ) > turning = [](Vector2f p0 , Vector2f p1 , Vector2f p2){
        Vector3f p30 = Vector3f(p0);
        Vector3f p31 = Vector3f(p1);
        Vector3f p32 = Vector3f(p2);

        Vector3f v0 = p1 - p0;
        Vector3f v1 = p2 - p1;
        Vector3f norm = v0.cross(v1);

        return norm.z > 0;
    };

    // the result of the function 

    std::vector< Vector2f > result = std::vector< Vector2f >();

    // traverse the whole points to get the half hull

    std::stack< Vector2f > s ;

    std::function< void(void) > handler = [ & ](){
        
        while( s.size() >= 3 ){

            // test the point in the stach that whether if satisfy the properties

            Vector2f p2 = s.top();
            s.pop();

            Vector2f p1 = s.top();
            s.pop();

            Vector2f p0 = s.top();
            s.pop();

            bool direction = turning( p0 , p1 , p2 );

            if( direction ){

                s.push( p0 );
                s.push( p1 );
                s.push( p2 );

                break;

            }else{

                s.push( p0 );
                s.push( p2 );

            }
        }
    };

    for( int i = 0 ; i < points.size() ; ++ i ){

        s.push( points.at(i) );

        handler();

    }

    while( !s.empty() ){
        result.push_back( s.top() );
        s.pop();
    }

    // to get the other half 

    for( int i = points.size() - 1 ; i >= 0 ; --i ){
        s.push( points.at(i) );

        handler();
    }

    while( !s.empty() ){
        result.push_back( s.top() );
        s.pop();
    }


    return result;

}