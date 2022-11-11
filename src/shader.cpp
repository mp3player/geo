#include <shader.h>
#include <iostream>


Shader::Shader( std::string path , unsigned int type ) : type( type ) {
    std::ifstream ifs( path , std::ios::in );
    if( !ifs.is_open() ){
        this->setStatus( NO_FILE , "load code failed");
    }else{
        std::stringstream ss;
        ss << ifs.rdbuf() ;
        this->code = ss.str();
        this->setStatus( NOT_COMPILED , "shader isn't compiled" );
    }
    ifs.close();
}

Shader::~Shader(){
    this->deleteShader();
}

bool Shader::getStatus(){
    return this->status == OK;
}

void Shader::setStatus( ShaderStatus status , std::string info ){
    this->status = status ;
    this->shaderInfo = info;
}

void Shader::compile(){
    
    if( this->getStatus() ){
        this->deleteShader();
    }

    if( this->code.size() < 0 ) {
        this->setStatus( NO_CODE , "no code" );
        return;
    }

    this->shader = glCreateShader( this->type );
    const char * c = this->code.c_str() ;

    glShaderSource( this->shader, 1 , &c , NULL);
    glCompileShader( this->shader );

    int compileStatus ;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if( !compileStatus ){

        char info[512];
        glGetShaderInfoLog(shader, 512, NULL, info);
        
        std::string detailInfo = ( ( this->type == GL_VERTEX_SHADER ) ? "Vertex : " : "Fragment : ") + std::string( info );
        this->setStatus( ERROR , detailInfo );
        std::cout << detailInfo << std::endl;
        return ;
    }
    this->setStatus( OK , "OK" );
}

void Shader::deleteShader( ){
    if( glIsShader( this->shader ) ){
        glDeleteShader( this->shader );
        this->setStatus( DELETED , "deleted" );
    }
}