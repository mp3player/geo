#ifndef _G_MATH_H_
#define _G_MATH_H_

#include <shape.h>
#include <cmath>
#include <ctime>



float randf(float min = 0.0f, float max = 1.0f);

glm::vec2 randv2f(float min = 0.0f, float max = 1.0f);

glm::vec3 randv3f(float min=0.0f, float max = 1.0f);

LineSegment* randLine(float min=0.0f, float max=1.0f);

bool isVertical(LineSegment* line);

bool getSlope(LineSegment* line, float& k, float& b);

bool isLineSegmentIntersected(LineSegment* l0, LineSegment* l1);

bool getIntersectedPoint(LineSegment* l0, LineSegment* l1 , glm::vec2 & point );

void sweepLineAlgorithm( std::vector< LineSegment * > lineSegments );


#endif