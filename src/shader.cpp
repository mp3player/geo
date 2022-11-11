#include <shader.h>


Shader::Shader( std::string path , unsigned int type ) : type( type ) {
    std::ifstream ifs( path , std::ios::in );
    if( !ifs.is_open() ){
        // do nothing 
    }else{
        std::stringstream ss;
        ss << ifs.rdbuf() ;
        std::string code = ss.str();
    }
}

Shader::~Shader(){
    this->deleteShader();
}

void Shader::compile(){
    
    if( this->shaderStatus == true ){
        this->deleteShader();
    }

    if( this->code.size() <0 ) {
        this->shaderStatus = false;
        this->shaderInfo = "no code";
        return;
    }

    this->shader = glCreateShader( this->type );
    const char * const code = this->code.c_str() ;

    glShaderSource( this->shader, 1 , &code , NULL);
    glCompileShader( this->shader );

    int status ;
    char info[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if( !status ){
        glGetShaderInfoLog(shader, 512, NULL, info);
        this->shaderInfo = ( ( this->type == GL_VERTEX_SHADER ) ? "Vertex : " : "Fragment : ") + std::string( info );
        this->shaderStatus = status;
    }
    this->shaderStatus = true;
    this->shaderInfo = "OK";
}

void Shader::deleteShader( ){
    if( glIsShader( this->shader ) ){
        glDeleteShader( this->shader );
        this->shaderStatus = false;
        this->shaderInfo = "deleted";
    }
}