#ifndef ANDROIDAPP_SHADERBUILDER_H
#define ANDROIDAPP_SHADERBUILDER_H

#include <vector>
#include <map>
#include <GLES2/gl2.h>

class ShaderBuilder {
    private:
        typedef std::map<std::string, int> NameMap;
        ShaderBuilder();

        std::vector<GLint> shaders;
        NameMap nameMap;
    public:
        static ShaderBuilder& instance();
        int buildShader(const std::string &name, const std::string &vert, const std::string &frag);
        GLint getShader(int shaderId);
        GLint useProgram(int shaderId);
};


#endif //ANDROIDAPP_SHADERBUILDER_H
