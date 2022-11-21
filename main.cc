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
    typedef std::function< bool(float,float)> _Comp;
    _Comp _comp = [](float a, float b){ return a - b > 0; };

    Heap< float , _Comp >heap = Heap<float , _Comp >( _comp , 10 );

    for( int i = 0 ; i < 15 ; ++ i ){
        float v = randFloat();
        heap.add( v );
        std::cout << v << " " ;
    }
    std::cout << std::endl;

    std::cout << heap._size << std::endl;

    while( heap._size > 0 ){
        float v ;
        bool res = heap.pop(v);
        if( res ) std::cout  << v << " ";
    }
    std::cout << std::endl;

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

   /*
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
*/


    /*

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
            std::vector<Vector2f> v0 = randVector2f(2 , -400,400);
            std::vector<Vector2f> v1 = randVector2f(2 , -400,400);

            LineSegment * l0 = new LineSegment(v0.at(0),v0.at(1));
            LineSegment * l1 = new LineSegment(v1.at(0),v1.at(1));


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


    */

    return 0;
}