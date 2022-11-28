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

    // std::vector< LineSegment * > lines ;
    // for( int i = 0 ; i < 4 ; ++ i ){
    //     LineSegment * line = randLine(-400,400);
    //     lines.push_back( line );
    // }

    // sweepLineAlgorithm( lines );

    
    // /*

    // 随机种子 
    srand(time(NULL));

    Window window = Window(800,800,400,100);

    LineStyle * redStyle = new LineStyle();
    redStyle->lineWidth = 10;
    LineStyle * greenStyle = new LineStyle();

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

    LineStyle * style = redStyle;
                LineSegment * l0 = randLine(-400,400);
            LineSegment * l1 = randLine(-400,400);
    
    int k = 0;
    while( !glfwWindowShouldClose( window.frame ) ){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {



            // bool intersected = isLineSegmentIntersected( l0 , l1 );
            // std::cout << "intersected : " << intersected << std::endl;
            // if( intersected ){
            //     style = redStyle;
            // }else{
            //     style = greenStyle;
            // }
            l0->rotate(.01f);

            window.draw(l0,style);
            window.draw(l1,style);

            // delete l0;delete l1;
        }
    

        glfwPollEvents();
        glfwSwapBuffers( window.frame );

        glfwSwapInterval(1);
        
    }


    delete redStyle;
    delete greenStyle;


    // */

    return 0;
}