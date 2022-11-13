#include <iostream>
#include <window.h>
#include <gmath.h>
#include <program.h>


int main(){
    // 随机种子 
    srand(time(NULL));

    Window window = Window(800,800,400,100);

    std::vector< Vector2f > vertices = randVector2f(10 , -400.0f , 400.0f);

    std::cout << std::endl;

    std::vector< Vector2f > convex = getConvex( vertices );


    Polygon * p = new Polygon( vertices );
    Polygon * pc = new Polygon( convex );

    PointStyle * pStyle = new PointStyle();
    pStyle->pointSize = 10.0f;

    LineStyle * lStyle = new LineStyle();
    lStyle->closed = true;
    lStyle->lineWidth = 2.0f;

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

    while( !glfwWindowShouldClose( window.frame ) ){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        window.draw( p , pStyle );

        window.draw( pc , lStyle );

        glfwPollEvents();
        glfwSwapBuffers( window.frame );
    }

    delete pc;
    delete p;
    delete pStyle;
    delete lStyle;

    return 0;
}