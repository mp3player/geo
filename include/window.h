#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <shape.h>
#include <style.h>
#include <program.h>


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
    Program * program = nullptr;

    std::unordered_map< Shape * , CacheData > caches;

public:
    
    explicit Window( int width , int height , int x = 0 , int y = 0 );

    ~Window();

    bool createWindow();

    void destoryWindow();

    void draw( Shape * shape , Style * style );

    void display();

private:

    bool getCache( Shape * , CacheData& );

    CacheData makeCache( Shape * );

    void clearCache( Shape * );

    void clearAllCache();

};


#endif