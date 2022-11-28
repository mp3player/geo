#ifndef _STYLE_H_
#define _STYLE_H_

#include <string>

struct Color {
    
    float r , g , b , a ;

    explicit Color( float r = 1.0f , float g = 1.0f , float b = 1.0f , float a = 1.0f );

};

struct Style {

    enum StyleType {
        POINT , LINE , FACE
    };

    Color * color;
    
    explicit Style();

    virtual ~Style();

    virtual StyleType getType();
};

struct PointStyle : Style {

    float pointSize;

    explicit PointStyle();

    StyleType getType();

};

struct LineStyle : Style {

    float lineWidth;

    bool closed;

    explicit LineStyle();

    StyleType getType();

};

struct FaceStyle : Style {

    explicit FaceStyle();

    StyleType getType();
    
};

#endif