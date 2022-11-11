#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <glad.h>
#include <fstream>
#include <sstream>

class Shader {

public:
    enum ShaderStatus {
        NO_CODE ,           // no code
        NO_FILE ,           // no shader file
        NOT_INITED ,        // don't read shader file
        NOT_COMPILED ,      // don't compile the shader program
        DELETED ,           // shader has been deleted
        ERROR ,             // error
        OK 
    };

public:

    unsigned int type ;

    std::string code;

    unsigned int shader;

    bool valid = false;

    bool shaderStatus = false ;

    ShaderStatus status = NOT_INITED;

    // TODO : use enum to represent the message
    std::string shaderInfo = "not inited";

    explicit Shader( std::string path , unsigned int type );

    ~Shader();

public:

    bool getStatus();

    void setStatus( ShaderStatus status , std::string info );

    void compile( );

    void deleteShader();

    

};

#endif