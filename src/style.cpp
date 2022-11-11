#include <style.h>

// color

Color::Color( float r , float g , float b , float a ) : r(r) , g(g) , b(b) , a(a) {}

// style

Style::Style() : color( new Color() ) {}

std::string Style::getType(){
    return "point";
}

Style::~Style(){
    delete this->color;
}

// point

PointStyle::PointStyle() : Style() , pointSize( 1.0f ) {}

std::string PointStyle::getType(){
    return "point";
}

// line

LineStyle::LineStyle() : Style() , lineWidth( 1.0f ) {}

std::string LineStyle::getType(){
    return "line";
}