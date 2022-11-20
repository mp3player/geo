#include <iostream>
#include <functional>

#include <window.h>
#include <gmath.h>
#include <program.h>
#include <bst.h>
#include <avl.h>
#include <rbtree.h>



int main(){
    /*
    using Comparer = std::function< bool(float , float ) >  ;

    Comparer comparer = []( float v0 , float v1 ){
        return v0 < v1;
    };

    RBTree< float , Comparer> tree = RBTree< float , Comparer >( comparer );
    tree.add(49);
    tree.add( 4);
    tree.add( 7);
    tree.add(10);
    tree.add(22);
    tree.add(23);
    tree.add(47);
    tree.add(48);

    tree.add(59);
    tree.add(71);
    tree.add(82);
    tree.add(84);

    std::cout << std::endl;

    tree.preOrder();
    tree.inOrder();

    tree.remove(59);

    tree.preOrder();
    tree.inOrder();

    std::cout << std::endl;
    */
    std::function< void(float) > handler = [](float v){
        std::cout << v << " ";
    };
    using Comparer = std::function< bool(float , float ) >  ;

    Comparer comparer = []( float v0 , float v1 ){
        return v0 < v1;
    };

    AVLTree< float , Comparer> tree = AVLTree< float , Comparer >( comparer );

    tree.add(4);
    tree.add(7);
    tree.add(10);
    tree.add(22);
    tree.add(23);
    tree.add(47);
    tree.add(48);
    tree.add(49);
    tree.add(59);
    tree.add(71);
    tree.add(82);
    tree.add(84);

    std::cout << std::endl;

    tree.preOrder( handler );
    tree.inOrder( handler );

    tree.remove(59);

    tree.preOrder( handler );
    tree.inOrder( handler );

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