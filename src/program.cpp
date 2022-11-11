#include <program.h>
#include <iostream>


Program::Program( std::string vpath , std::string fpath ) {
    this->vertexShader = new Shader( vpath , GL_VERTEX_SHADER ) ;
    this->fragmentShader = new Shader( fpath , GL_FRAGMENT_SHADER );
    this->setStatus( false , "not compile" );
}

Program::~Program(){

    this->deleteProgram();

}


void Program::setStatus( bool status , std::string info ){
    this->programStatus = status;
    this->programInfo = info;
}


void Program::compile(){

    vertexShader->compile();
    fragmentShader->compile();

    if( !vertexShader->shaderStatus || !fragmentShader->shaderStatus ){
        this->setStatus( false , "shader error" );
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
        this->setStatus( status , info );
        std::cout << info << std::endl;
        return ;
    }
    this->setStatus( status , "OK" );
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

    this->setStatus( false , "deleted" );

}