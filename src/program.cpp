#include <program.h>


Program::Program( std::string vpath , std::string fpath ) 
: vertexShader( new Shader( vpath , GL_VERTEX_SHADER ) ) , 
fragmentShader( new Shader( fpath , GL_FRAGMENT_SHADER ) ) {}

Program::~Program(){
    this->deleteProgram();
}


void Program::compile(){
    if( !vertexShader->shaderStatus || !fragmentShader->shaderStatus ){
        vertexShader->compile();
        fragmentShader->compile();
    }
}

void Program::deleteProgram(){
    if( this->vertexShader->shaderStatus ){
        delete vertexShader;
    }
    if( this->fragmentShader->shaderStatus ){
        delete fragmentShader;
    }
    if( glIsProgram( this->program ) ){
        glDeleteProgram( this->program );
    }
}