#include <program.h>
#include <iostream>


Program::Program( std::string vpath , std::string fpath ) {
    this->vertexShader = new Shader( vpath , GL_VERTEX_SHADER ) ;
    this->fragmentShader = new Shader( fpath , GL_FRAGMENT_SHADER );
    this->setStatus( Shader::NOT_COMPILED , "not compile" );
}

Program::~Program(){
    this->deleteProgram();
}

void Program::setStatus( Status status , std::string info ){
    this->status = status;
    this->programInfo = info;
}

void Program::compile(){

    vertexShader->compile();
    fragmentShader->compile();

    if( !vertexShader->getStatus() || !fragmentShader->getStatus() ){
        this->setStatus( Shader::ERROR , "shader error" );
        return ;
    }

    this->program = glCreateProgram();
    glAttachShader( program , this->vertexShader->shader );
    glAttachShader( program , this->fragmentShader->shader );
    glLinkProgram( this->program );

    int status;
    glGetProgramiv( this->program , GL_LINK_STATUS , &status );
    if( !status ){
        char info[512];
        glGetProgramInfoLog( this->program , 512 , NULL , info );
        this->setStatus( Shader::ERROR , info );
        std::cout << info << std::endl;
        return ;
    }
    this->setStatus( Shader::OK , "OK" );
}

void Program::deleteProgram(){

    if( this->vertexShader->getStatus() ){
        delete vertexShader;
    }
    if( this->fragmentShader->getStatus() ){
        delete fragmentShader;
    }
    if( glIsProgram( this->program ) ){
        glDeleteProgram( this->program );
    }

    this->setStatus( Shader::DELETED , "deleted" );

}