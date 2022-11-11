#ifndef _G_MATH_H_
#define _G_MATH_H_

#include <shape.h>
#include <cmath>
#include <ctime>



// random Vector
float randFloat( float min = 0.0f , float max = 1.0f );
std::vector< Vector2f > randVector2f( int count , float min = 0.0f , float max = 1.0f );

#endif