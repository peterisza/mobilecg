#include "Helper.h"
#include <cassert>
#include "log.h"
#include <vector>

namespace helper {
    std::string loadAsset(AAssetManager *assetManager, std::string name){
        AAsset *asset = AAssetManager_open(assetManager, name.c_str(), AASSET_MODE_BUFFER);
        assert(asset != NULL);
        const void *assetBuf = AAsset_getBuffer(asset);
        assert(assetBuf != NULL);
        off_t assetLen = AAsset_getLength(asset);
        std::string assetData = std::string((const char*)assetBuf, (size_t)assetLen);
        AAsset_close(asset);

        return assetData;
    }

    GLuint loadShader(GLenum shaderType, const std::string& pSource) {
        GLuint shader = glCreateShader(shaderType);
        assert(shader != 0);
        const char *sourceBuf = pSource.c_str();
        glShaderSource(shader, 1, &sourceBuf, NULL);
        glCompileShader(shader);
        GLint shaderCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled == GL_FALSE){
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            LOGE("Failed to compiler shader: %s",errorLog.data());

            assert(false);
        }
        return shader;
    }

    GLuint createGlProgram(const std::string& pVertexSource, const std::string& pFragmentSource) {
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
        GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
        GLuint program = glCreateProgram();
        assert(program != 0);
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        GLint programLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &programLinked);
        assert(programLinked != 0);
        glDeleteShader(vertexShader);
        glDeleteShader(pixelShader);
        return program;
    }


    GLuint getGlUniformWithAssert(GLuint shader, const char *name){
        GLuint result=glGetUniformLocation(shader, name);
        if (result==-1){
            LOGE("Uniform not found: %s",name);
            assert(false);
        }
        return result;
    }

    GLuint getGlAttributeWithAssert(GLuint shader, const char *name){
        GLuint result=glGetAttribLocation(shader, name);
        if (result==-1){
            LOGE("Attribute not found: %s",name);
            assert(false);
        }
        return result;
    }

}