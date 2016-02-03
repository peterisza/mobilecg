#include "ShaderBuilder.h"
#include "Helper.h"

ShaderBuilder::ShaderBuilder(){
    
}

ShaderBuilder& ShaderBuilder::instance(){
    static ShaderBuilder i;
    return i;
}

int ShaderBuilder::buildShader(const std::string &name, const std::string &vert, const std::string &frag){
    NameMap::iterator it = nameMap.find(name);
    if (it!=nameMap.end())
        return it->second;

    shaders.push_back(helper::createGlProgram(vert, frag));
    int shaderIndex=shaders.size()-1;
    nameMap[name]=shaderIndex;

    return shaderIndex;
}

GLint ShaderBuilder::useProgram(int shaderId){
    GLint shader=shaders[shaderId];
    glUseProgram(shader);
    return shader;
}

GLint ShaderBuilder::getShader(int shaderId){
    return shaders[shaderId];
}
