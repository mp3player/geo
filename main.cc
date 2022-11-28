#include <iostream>
#include <functional>

#include <window.h>
#include <gmath.h>
#include <program.h>
#include <bst.h>
#include <avl.h>
#include <rbtree.h>
#include <heap.h>


int main(){

    

    // 随机种子 
    srand(time(NULL));

    Window window = Window(800,800,400,100);

    LineStyle * redStyle = new LineStyle();
    redStyle->lineWidth = 10;
    LineStyle * greenStyle = new LineStyle();

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

    LineStyle * style = redStyle;
    
    int k = 0;
    while( !glfwWindowShouldClose( window.frame ) ){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            LineSegment * l0 = randLine(-400,400);
            LineSegment * l1 = randLine(-400,400);


            bool intersected = isLineSegmentIntersected( l0 , l1 );
            std::cout << "intersected : " << intersected << std::endl;
            if( intersected ){
                style = redStyle;
            }else{
                style = greenStyle;
            }

            window.draw(l0,style);
            window.draw(l1,style);

            // delete l0;delete l1;
        }
    

        glfwPollEvents();
        glfwSwapBuffers( window.frame );

        glfwSwapInterval(50);
        
    }


    delete redStyle;
    delete greenStyle;


    

    return 0;
}