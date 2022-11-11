#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <glad.h>
#include <fstream>
#include <sstream>

class Shader {

public:
    unsigned int type ;
    std::string code;
    unsigned int shader;

    bool valid = false;

    bool shaderStatus = false ;

    std::string shaderInfo = "not inited";

    explicit Shader( std::string path , unsigned int type );

    ~Shader();

public:

    void compile( );

    void deleteShader();

};

#endif