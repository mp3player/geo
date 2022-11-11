#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <shader.h>

class Program {

public:

    Shader * vertexShader;

    Shader * fragmentShader;

    unsigned int program;

    bool programStatus;

    std::string programInfo;

    explicit Program( std::string vpath , std::string fpath );

    ~Program();

public:

    void setStatus( bool status , std::string info );

    void compile();

    void deleteProgram();

};

#endif