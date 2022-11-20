#ifndef _G_MATH_H_
#define _G_MATH_H_

#include <shape.h>
#include <cmath>
#include <ctime>



// random Vector
float randFloat( float min = 0.0f , float max = 1.0f );

std::vector< Vector2f > randVector2f( int count , float min = 0.0f , float max = 1.0f );

// checkout whether the point in the shape , 2-d condition

bool pointInLine( Vector2f p , Vector2f start , Vector2f end , float eps = 1e-6 );

bool pointInPolygon( Vector2f p , std::vector< Vector2f > ps );

bool pointInCircle( Vector2f p , Vector2f center , float radius );

// convex
// BF algorithm
// optimization algorithm

std::vector< Vector2f > getConvex( std::vector< Vector2f > points );

// line segment intersection test
// sweep line algorithm
void intersection();


#endif