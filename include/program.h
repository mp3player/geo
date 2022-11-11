#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <shader.h>

class Program {

public:
    Shader * vertexShader;
    Shader * fragmentShader;

    unsigned int program;

    explicit Program( std::string vpath , std::string fpath );

    ~Program();

public:

    void compile();

    void deleteProgram();

};

#endif