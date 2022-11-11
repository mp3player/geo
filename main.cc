#include <iostream>
#include <window.h>
#include <gmath.h>


int main(){
    // 随机种子 
    srand(time(NULL));


    Window window = Window(800,800,400,100);

    Circle * circle = new Circle(700.0f);

    Rectangle * rect = new Rectangle(100,100);

    std::vector< Vector2f > vertices = randVector2f(10 , -400.0f , 400.0f);

    Polygon * p = new Polygon( vertices );

    LineStyle * style = new LineStyle();
    style->lineWidth = 2.0f;

    PointStyle * pStyle = new PointStyle();
    pStyle->pointSize = 20.0f;

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    while( !glfwWindowShouldClose( window.frame ) ){
        glClear(GL_COLOR_BUFFER_BIT);
        
        window.draw( p , pStyle );
        window.draw( circle , style );

        glfwPollEvents();
        glfwSwapBuffers( window.frame );
    }

    delete style;
    delete p;
    delete circle;
    delete rect;
    return 0;
}