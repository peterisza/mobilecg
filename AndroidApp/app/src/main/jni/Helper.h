#ifndef ANDROIDAPP_HELPER_H
#define ANDROIDAPP_HELPER_H

#include <android/asset_manager_jni.h>
#include <string>
#include <GLES2/gl2.h>

namespace helper {
    std::string loadAsset(AAssetManager *assetManager, std::string name);
    GLuint createGlProgram(const std::string& pVertexSource, const std::string& pFragmentSource);
    GLuint getGlUniformWithAssert(GLuint shader, const char *name);
    GLuint getGlAttributeWithAssert(GLuint shader, const char *name);
};


#endif //ANDROIDAPP_HELPER_H
