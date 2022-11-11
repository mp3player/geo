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