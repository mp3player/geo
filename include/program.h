#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <shader.h>
#include <glm/glm.hpp>

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

    void setUniform( std::string  , int  );

    void setUniform( std::string  , float  );

    void setUniform( std::string  , glm::vec2  );

    void setUniform( std::string  , glm::vec3  );

    void setUniform( std::string  , glm::vec4  );

    void setUniform( std::string  , glm::mat2  );

    void setUniform( std::string  , glm::mat3  );

    void setUniform( std::string  , glm::mat4  );

    void setDefine( );

};

#endif