//
// Created by isza on 2016.02.04..
//

#include "TextDrawer.h"
#include "Helper.h"
#include "EcgArea.h"
#include "log.h"

#include <jni.h>

extern JavaVM* cachedJVM;

void TextDrawer::drawText(const char* text){
    JNIEnv *env;
    (cachedJVM)->AttachCurrentThread(&env, NULL);

    jclass jTextRenderer = env->FindClass("com/android/sensorgraph/TextRenderer");
    jmethodID constructor = env->GetMethodID(jTextRenderer, "<init>", "()V");
    jmethodID setText = env->GetMethodID(jTextRenderer, "setText", "(Ljava/lang/String;II)V");
    jmethodID getHeight = env->GetMethodID(jTextRenderer, "getHeight", "()I");
    jmethodID getWidth = env->GetMethodID(jTextRenderer, "getWidth", "()I");
    jmethodID renderToBitmap = env->GetMethodID(jTextRenderer, "renderToBitmap", "([B)V");

    jobject obj = env->NewObject(jTextRenderer, constructor);
    jstring jText = env->NewStringUTF(text);
    env->CallVoidMethod(obj, setText, jText, 60, 0xFF0000FF);
    int height = (int)env->CallIntMethod(obj, getHeight);
    int width = (int)env->CallIntMethod(obj, getWidth);

    jbyteArray bitmap = env->NewByteArray(height*width*4);
    env->CallVoidMethod(obj, renderToBitmap, bitmap);

    const char* data = (const char*) env->GetByteArrayElements(bitmap, 0);
    setBitmap(data, width, height);

    env->DeleteLocalRef(bitmap);
}

void TextDrawer::setBitmap(const char* data, int width, int height) {
    setSize(width, height);
    textImage.resize(width, height);
    textImage.setBitmap(data);
    //textImage.fill(Image::BLACK);

    redraw(&textImage);
}
