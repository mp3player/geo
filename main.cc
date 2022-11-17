#include <iostream>
#include <functional>

#include <window.h>
#include <gmath.h>
#include <program.h>
#include <bst.h>
#include <avl.h>



int main(){

    using Comparer = std::function< bool(Vector2f , Vector2f ) >  ;

    Comparer comparer = []( Vector2f v0 , Vector2f v1 ){
        return v0.x < v1.x;;
    };

    AVLTree< Vector2f , Comparer> tree = AVLTree< Vector2f , Comparer >( comparer );

    tree.add( Vector2f(4));
    tree.add( Vector2f(7));
    tree.add( Vector2f(10));
    tree.add( Vector2f(22));
    tree.add( Vector2f(23));
    tree.add( Vector2f(47));
    tree.add( Vector2f(48));
    tree.add( Vector2f(49));
    tree.add( Vector2f(59));
    tree.add( Vector2f(71));
    tree.add( Vector2f(82));
    tree.add( Vector2f(84));

    std::cout << std::endl;

    tree.preOrder();
    tree.inOrder();

    tree.remove(Vector2f(59));

    tree.preOrder();
    tree.inOrder();

    std::cout << std::endl;

    /*

    // 随机种子 
    srand(time(NULL));

    // Window window = Window(800,800,400,100);

    std::vector< Vector2f > vertices = randVector2f(10 , -400.0f , 400.0f);

    
    


    // std::vector< Vector2f > convex = getConvex( vertices );

    // Polygon * p = new Polygon( vertices );
    // Polygon * pc = new Polygon( convex );

    PointStyle * pStyle = new PointStyle();
    pStyle->pointSize = 10.0f;

    LineStyle * lStyle = new LineStyle();
    lStyle->closed = true;
    lStyle->lineWidth = 2.0f;

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

    while( !glfwWindowShouldClose( window.frame ) ){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // window.draw( p , pStyle );

        // window.draw( pc , lStyle );

        glfwPollEvents();
        glfwSwapBuffers( window.frame );
    }

    // delete pc;
    // delete p;
    delete pStyle;
    delete lStyle;

    */

    return 0;
}