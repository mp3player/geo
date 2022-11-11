#ifndef _STYLE_H_
#define _STYLE_H_

#include <string>

struct Color {
    float r , g , b , a ;
    explicit Color( float r = 1.0f , float g = 1.0f , float b = 1.0f , float a = 1.0f );
};

struct Style {
    Color * color;
    
    explicit Style();
    virtual ~Style();
    virtual std::string getType();
};

struct PointStyle : Style {
    float pointSize;
    explicit PointStyle();
    std::string getType();
};

struct LineStyle : Style {
    float lineWidth;
    explicit LineStyle();
    std::string getType();
};

struct FaceStyle : Style {
    explicit FaceStyle();
    std::string getType();
};

#endif