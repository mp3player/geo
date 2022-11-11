#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <shape.h>
#include <style.h>


#define VERTEX_SHADER \ 
"#version 330 core \n" \
"precision mediump float; \n" \
"uniform float width;\n" \
"uniform float height;\n" \
"layout(location=0) in vec2 position; \n" \
"void main(){ \n" \
"\tgl_Position = vec4(position / vec2( width , height ) , 0.0f , 1.0f); \n" \ 
"} \n"

#define FRAGMENT_SHADER \
"#version 330 core \n"\
"precision mediump float; \n" \
"void main(){ \n" \
"\tgl_FragColor = vec4(1.0f,1.0f, 1.0f , 1.0f);\n" \
"}"


class Window {

public:
    struct CacheData{
        unsigned int vao;
        unsigned int vbo;
        int count;
        bool indexed;
    };

public:

    int x , y , width , height ;
    GLFWwindow * frame ;
    bool inited ;
    bool visible ;
    bool valid ;
    unsigned int program;

    std::unordered_map< Shape * , CacheData > caches;

public:
    
    explicit Window( int width , int height , int x = 0 , int y = 0 );

    ~Window();

    bool createShader();

    bool createWindow();

    void destoryWindow();

    void draw( Shape * shape );

    void draw( Shape * shape , Style * style );

    void display();

private:

    bool getCache( Shape * , CacheData& );

    CacheData makeCache( Shape * );

    void clearCache( Shape * );

    void clearAllCache();

};


#endif