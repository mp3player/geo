#include <style.h>

// color

Color::Color( float r , float g , float b , float a ) : r(r) , g(g) , b(b) , a(a) {}

// style

Style::Style() : color( new Color() ) {}

Style::StyleType Style::getType(){
    return POINT;
}

Style::~Style(){
    delete this->color;
}

// point

PointStyle::PointStyle() : Style() , pointSize( 1.0f ) {}

Style::StyleType PointStyle::getType(){
    return POINT;
}

// line

LineStyle::LineStyle() : Style() , lineWidth( 1.0f ) , closed( false ) {}

Style::StyleType LineStyle::getType(){
    return Style::LINE;
}