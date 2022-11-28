#include <gmath.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stack>
#include <queue>
#include <list>
#include <heap.h>
#include <functional>
#include <algorithm>
#include <bst.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "./tree.cpp"

float randf(float min, float max)
{
	float v = ( rand() % 10000 ) / 10000.0f;
	v = v * (max - min) + min;
	return v;
}

glm::vec2 randv2f(float min, float max)
{
	float x = randf(min, max);
	float y = randf(min, max);
	return glm::vec2(x, y);
}

glm::vec3 randv3f(float min, float max)
{
	float x = randf(min, max);
	float y = randf(min, max);
	float z = randf(min, max);
	return glm::vec3(x, y, z);
}


bool pointInLine( glm::vec2 p , glm::vec2 start , glm::vec2 end , float eps ){
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

bool pointInPolygon( glm::vec2 p , std::vector< glm::vec2 > ps ){
    return true;
}

bool pointInCircle( glm::vec2 p , glm::vec2 center , float radius ){
    glm::vec2 dist = p - center;
    float sLength = dist.length();
    float sR = radius * radius;

    if( sLength < sR ) return true;
    return false;
}

std::vector< glm::vec2 > getConvex( std::vector< glm::vec2 > points ){

    std::function< bool(glm::vec2 , glm::vec2) > comparer = []( glm::vec2 a, glm::vec2 b ){
        if( a.x == b.x && a.y < b.y ) return true;
        if( a.x == b.x && a.y > b.y ) return false;
        return a.x < b.x;
    };

    std::vector< glm::vec2 >::iterator begin = points.begin();
    std::vector< glm::vec2 >::iterator end = points.end();
    
    std::sort<std::vector<glm::vec2>::iterator , std::function< bool(glm::vec2 , glm::vec2) >>( begin , end , comparer );

    // compute the turning direction
    std::function< bool( glm::vec2 , glm::vec2 , glm::vec2 ) > turning = [](glm::vec2 p0 , glm::vec2 p1 , glm::vec2 p2){
        glm::vec3 p30 = glm::vec3(p0.x,p0.y,1);
        glm::vec3 p31 = glm::vec3(p1.x,p1.y,1);
        glm::vec3 p32 = glm::vec3(p2.x,p2.y,1);


        glm::vec3 v0 = p31 - p30;
        glm::vec3 v1 = p32 - p31;
        glm::vec3 norm = glm::cross( v0 , v1);

        return norm.z > 0;
    };

    // the result of the function 
    std::vector< glm::vec2 > result = std::vector< glm::vec2 >();

    // traverse the whole points to get the half hull
    std::stack< glm::vec2 > s ;

    std::function< void(void) > handler = [ & ](){
        while( s.size() >= 3 ){

            // test the point in the stach that whether if satisfy the properties
            glm::vec2 p2 = s.top();
            s.pop();

            glm::vec2 p1 = s.top();
            s.pop();

            glm::vec2 p0 = s.top();
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

bool isLineSegmentIntersected( LineSegment * l0 , LineSegment * l1 ){
    // compute vector 
    glm::vec3 v0( l1->upper - l0->lower , 1.0f );
    glm::vec3 v1( l0->upper - l1->upper , 1.0f );
    glm::vec3 v2( l1->lower - l0->upper , 1.0f );
    glm::vec3 v3( l0->lower - l1->lower , 1.0f );

    glm::vec3 c0 = glm::cross(v0,v1);
    glm::vec3 c1 = glm::cross(v1,v2);
    glm::vec3 c2 = glm::cross(v2,v3);
    glm::vec3 c3 = glm::cross(v3,v0);

    float c0z = c0.z ;
    float c1z = c1.z ;
    float c2z = c2.z ;
    float c3z = c3.z ;
    if( c0z > 0 && c1z > 0 & c2z > 0 && c3z > 0 || c0z < 0 && c1z < 0 & c2z < 0 && c3z < 0 ){
        return true;
    }
    return false;
}

LineSegment* randLine(float min, float max)
{
    glm::vec2 v0 = randv2f(min, max);
    glm::vec2 v1 = randv2f(min, max);
    LineSegment* line = new LineSegment(v0,v1);
    return line;
}

bool isVertical(LineSegment* line)
{
    glm::vec2 upper = line->upper;
    glm::vec2 lower = line->lower;
    return upper.x == lower.x && upper.y != lower.y;
}

bool getSlope(LineSegment* line, float& k, float& b)
{
    glm::vec2 v0 = line->upper;
    glm::vec2 v1 = line->lower;
    if (isVertical(line)) return false;
    k = (v1.y - v0.y) / (v1.x - v0.x);
    b = v0.y - k * v0.x;
    return true;
}

bool getIntersectedPoint(LineSegment* l0, LineSegment* l1 , glm::vec2 & point )
{
    if (isVertical(l0) && isVertical(l1)) {
        std::cout << "vertical" << std::endl;
        return false;
    }
    else if (isVertical(l0)) {
        float x = l0->upper.x;
        float k ,b;
        getSlope(l1,k,b);
        float y = k * x + b;
        if (y > l0->upper.y || y < l0->lower.y) {

            return false;
        }
        point.x = x;
        point.y = y;
        return true;
    }
    else {

        // compute slope 
        float k0, b0, k1, b1;
        getSlope(l0, k0, b0);
        getSlope(l1, k1, b1);
        
        // l0 and l1 is parallel
        if (k0 == k1) return false;

        //compute the intersection point 
        float x = (b1 - b0) / (k0 - k1);
        float y = (k1 * b0 - k0 * b1) / (k1 - k0);
        
        // judge whether the intersection point is on the line segment
        float l0x0, l0x1, l1x0, l1x1;
        if (l0->upper.x < l0->lower.x) {
            l0x0 = l0->upper.x, l0x1 = l0->lower.x;
        }
        else {
            l0x1 = l0->upper.x, l0x0 = l0->lower.x;
        }

        if (l1->upper.x < l1->lower.x) {
            l1x0 = l1->upper.x, l1x1 = l1->lower.x;
        }
        else {
            l1x1 = l1->upper.x, l1x0 = l1->lower.x;
        }
        if (x > l0x0 && x < l0x1 && x > l1x0 && x < l1x1) {
            point = glm::vec2{ x,y };
            return true;
        }
        return false;
    }
}

// status内会存储line 和 intersection point
// 查找status会查看line是不是同一条
// 添加会通过point来查询
void sweepLineAlgorithm( std::vector< LineSegment * > segments ){
    enum EventType { UNKNOW , END , INTERCTION };

    struct Line {
        glm::vec2 point;
        glm::vec2 interior ;
        LineSegment * line ;
        Line( glm::vec2 point , LineSegment * line ) : line( line ) , point( point ) , interior( point ) { }
    };

    struct Event {
        glm::vec2 point;
        Event( glm::vec2 point ) : point( point ) { }
        virtual EventType getType() { return UNKNOW; }
    };

    struct EndEvent : Event {
        LineSegment * line ;
        bool isUpper ;
        EndEvent( glm::vec2 point , LineSegment * line , bool isUpper ) : Event( point ) , line( line ) , isUpper( isUpper ) { }
        EventType getType(){ return END; }
    };

    struct InterEvent : Event {
        LineSegment * left ;
        LineSegment * right;
        InterEvent( LineSegment * left , LineSegment * right , glm::vec2 point ) : Event( point ) , left( left ) , right( right ) {}
        EventType getType() { return INTERCTION; }
    };

    // smaller than
    typedef std::function< int( Line * , Line * ) > _StatusComp ;
    typedef std::function< bool( Event * , Event * ) > _QueueComp;
    typedef TreeNode< Line * > Node;

    _StatusComp sComp = []( Line * l0, Line * l1) {
        if( l0->line == l1->line ) return 0;
        if( l0->interior.x < l1->interior.x ) return 1;
        return -1;
    };

    _QueueComp qComp = []( Event * e0 , Event * e1 ){
        if( e0->point.y < e1->point.y ) return true;
        return false;
    };

    AVL< Line * , _StatusComp > status( sComp );
    Heap< Event * , _QueueComp > queue( qComp );


    for( LineSegment * line : segments ) {
        std::cout << "upper " << line->upper.y << std::endl;
        std::cout << "lower " << line->lower.y << std::endl;
        EndEvent * upper = new EndEvent(line->upper , line , true);
        EndEvent * lower = new EndEvent(line->lower , line , false);
        queue.add( upper );
        queue.add( lower );
    }

    // 测试是否相交
    // 找到邻接线
    std::function< Node*(Node *) > findLeft = [](Node * node ){
        if( node->parent == nullptr ){
            return node->left;
        } else if ( node == node->parent->left ){
            return node->left;
        }else {
            return node->parent ;
        }
    };

    std::function< Node*(Node *) > findRight = []( Node * node ){
        if( node->parent == nullptr ){
            return node->right;
        }else if ( node == node->parent->right ){
            return node->right;
        }else {
            return node->parent;
        }
    };

    // 处理事件
    std::function< void(Node *) > pUpper = [&]( Node * node ){
        
        Node * left = findLeft( node );
        Node * right = findRight( node );
        glm::vec2 point ;

        if( left != nullptr ){
            bool intersected = getIntersectedPoint( node->value->line , left->value->line , point );
            if( intersected ){
                if( point.y < node->value->interior.y ){
                    InterEvent * iEvent = new InterEvent(left->value->line , node->value->line , point);
                    queue.add( iEvent );
                }
            }
        }

        if( right != nullptr ){
            bool intersected = getIntersectedPoint( node->value->line , right->value->line , point );
            if( intersected ){
                if( point.y < node->value->interior.y ){
                    InterEvent * iEvent = new InterEvent( node->value->line , right->value->line , point );
                    queue.add( iEvent );
                }
            }
        }

    };  

    std::function< void(Node *) > pLower = [&]( Node * node ){
        Node * left = findLeft( node );
        Node * right = findRight( node );
        if( left == nullptr || right == nullptr ) return ;
        glm::vec2 point;
        bool intersected = getIntersectedPoint(left->value->line , right->value->line , point);
        if( intersected ){
            if( point.y < node->value->point.y ){
                InterEvent * iEvent = new InterEvent( left->value->line , right->value->line , point );
                queue.add( iEvent );
            }
        }
        
    };

    std::function< void(InterEvent *) > pInter = [&](InterEvent * iEvent){
        
    };

    while( !queue.empty() ){
        Event * event;
        bool result = queue.pop( event );
        
        if(!result ){
            std::cout << "pop error " << std::endl;
            return ;
        }

        switch ( event->getType() ){
            case END : {

            }break;
            case INTERCTION : {

            }break;
            case UNKNOW : {

            }break;
        }

    }


}


