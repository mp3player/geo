#include <shader.h>
#include <iostream>


Shader::Shader( std::string path , unsigned int type ) : type( type ) {
    std::ifstream ifs( path , std::ios::in );
    std::string info ;
    if( !ifs.is_open() ){
        info = "load code failed";
    }else{
        std::stringstream ss;
        ss << ifs.rdbuf() ;
        this->code = ss.str();
        info = "shader isn't compiled";
    }
    this->setStatus( false , info );
}

Shader::~Shader(){
    this->deleteShader();
}

void Shader::setStatus( bool status , std::string info ){
    this->shaderStatus = status ;
    this->shaderInfo = info;
}

void Shader::compile(){
    
    if( this->shaderStatus == true ){
        this->deleteShader();
    }

    if( this->code.size() < 0 ) {
        this->setStatus( false , "no code" );
        return;
    }

    this->shader = glCreateShader( this->type );
    const char * c = this->code.c_str() ;

    glShaderSource( this->shader, 1 , &c , NULL);
    glCompileShader( this->shader );

    int status ;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if( !status ){

        char info[512];
        glGetShaderInfoLog(shader, 512, NULL, info);
        
        std::string detailInfo = ( ( this->type == GL_VERTEX_SHADER ) ? "Vertex : " : "Fragment : ") + std::string( info );
        this->setStatus( status , detailInfo );
        std::cout << detailInfo << std::endl;
        return ;
    }
    this->setStatus( true , "OK" );
}

void Shader::deleteShader( ){
    if( glIsShader( this->shader ) ){
        glDeleteShader( this->shader );
        this->setStatus( false , "deleted" );
    }
}