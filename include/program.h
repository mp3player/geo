#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <shader.h>

using Status = Shader::ShaderStatus;

class Program {

public:

    Shader * vertexShader;

    Shader * fragmentShader;

    unsigned int program;

    Status status;

    std::string programInfo;

    explicit Program( std::string vpath , std::string fpath );

    ~Program();

public:

    void setStatus( Status status , std::string info );

    void compile();

    void deleteProgram();

};

#endif