#include <window.h>
#include <iostream>
#include <functional>


Window::Window( int width , int height , int x , int y ) 
: width( width ) 
, height( height ) 
, x( x ) 
, y( y )
 {
    if( !glfwInit() ) inited = false;
    else inited = true;
    this->valid = this->createWindow();
    this->program = new Program("./assets/vertex.vert" , "./assets/fragment.frag");
    this->program->compile();
}

Window::~Window(){
    if( program != nullptr ){
        delete program;
    }
    this->clearAllCache();
    this->destoryWindow();
}

bool Window::createWindow(){
    if( !inited ){
        return false;
    }

    frame = glfwCreateWindow( width , height , "123" , NULL , NULL );
    glfwSetWindowPos(this->frame , x , y);

    if( frame == NULL ){
        return false;
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_COMPAT_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(this->frame);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return false;
    }
    return true;
}

void Window::destoryWindow(){
    if( !this->inited )
        glfwDestroyWindow( this->frame );
    glfwTerminate();
}

void Window::draw( Shape * shape , Style * style ){

    // draw 
    CacheData data;
    bool cached = this->getCache( shape , data );

    if( !cached ){
        data = this->makeCache( shape );
    }

    glUseProgram( this->program->program );
    unsigned int wLoc = glGetUniformLocation(this->program->program , "width");
    unsigned int hLoc = glGetUniformLocation(this->program->program , "height");
    glUniform1f(wLoc , width );
    glUniform1f(hLoc , height);

    // style
    unsigned int mode = this->setStyle( style );

    glBindVertexArray( data.vao );
    glDrawArrays( mode , 0 , data.count );

    glBindVertexArray(0);


}

void Window::display(){
    glfwPollEvents();
}

bool Window::getCache( Shape * shape , CacheData & data){
    std::unordered_map<Shape * , CacheData >::iterator result = this->caches.find(shape);
    if( result == this->caches.end() ){
        return false;
    }
    data = this->caches[ shape ];
    return true ;
}

Window::CacheData Window::makeCache( Shape * shape ){
    std::unordered_map<Shape * , CacheData >::iterator result = this->caches.find(shape);

    if( result != this->caches.end() ){ // buffer exist
        CacheData data = result->second;
        return data;
    }

    // create buffer
    std::vector< glm::vec2 > points = shape->getPoints();
    unsigned int vao , vbo ;
    glGenVertexArrays( 1 , &vao );
    glGenBuffers( 1 , &vbo );

    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER , vbo );

    glBufferData( GL_ARRAY_BUFFER , points.size() * sizeof(glm::vec2) , (void*)(&points.at(0)) , GL_STATIC_DRAW );

    glVertexAttribPointer( 0 , 2 , GL_FLOAT , GL_FALSE , sizeof(glm::vec2) , (void*)0);
    glEnableVertexAttribArray(0);

    CacheData data = { vao , vbo , points.size() , false };

    this->caches.emplace( shape , data);
    
    return data;

}

void Window::clearCache( Shape * shape ){
    CacheData data;
    bool cached = this->getCache( shape , data );
    if(cached){
        this->caches.erase( shape );
        if( glIsBuffer( data.vbo ) ) glDeleteBuffers( 1 , &data.vbo );
        if( glIsVertexArray(data.vao) ) glDeleteVertexArrays( 1 , &data.vao );
    }
}

void Window::clearAllCache(){
    typedef std::unordered_map< Shape * , CacheData >::iterator CacheIterator;

    CacheIterator begin = this->caches.begin();
    CacheIterator end = this->caches.end();
    
    while( begin != end ){

        CacheData data = begin->second;

        glBindVertexArray(0);
        if( glIsBuffer(data.vbo) ) glDeleteBuffers( 1 , &data.vbo );
        if( glIsVertexArray(data.vao) ) glDeleteVertexArrays( 1 , &data.vao );

        CacheIterator tmp = begin;
        begin ++;
        this->caches.erase( tmp );
        
    }
}

unsigned int Window::setStyle( Style * style ){
    std::function< void(Program * , Color *)> setColor = [](Program * program , Color * color){
        glm::vec3 c = glm::vec3(color->r , color->g , color->b);
        program->setUniform("color" , c);
    };
    switch( style->getType() ){
        case Style::POINT : {
            PointStyle * pStyle = (PointStyle *)style;
            glPointSize( pStyle->pointSize );
            setColor( program , pStyle->color );
            return GL_POINTS;
        }break;
        case Style::LINE : {
            LineStyle * lStyle = (LineStyle *)style;
            glLineWidth( lStyle->lineWidth );
            setColor( program , lStyle->color );
            if( lStyle->closed ) return GL_LINE_LOOP;
            return GL_LINE_STRIP;
        }break;
        case Style::FACE : {
            FaceStyle * fStyle = (FaceStyle *)style;
            return GL_TRIANGLES;
        }
    }
}











