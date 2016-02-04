//
// Created by isza on 2016.02.04..
//

#include "TextDrawer.h"
#include "Helper.h"
#include "EcgArea.h"

#include <jni.h>


void TextDrawer::drawText(const char* text){
    /*JNIEnv *env;
    (*cachedJVM)->AttachCurrentThread(jvm, (void **)&env, NULL);

    jclass jTextRenderer = (*env)->FindClass('com/android/sensorgraph/TextRenderer');
    jmethodID renderMethod = (*env)->GetMethodID(env, jTextRenderer, );*/
}

void TextDrawer::setBitmap(const char* data, int width, int height) {
    setSize(width, height);
    textImage.resize(width, height);
    textImage.setBitmap(data);
    redraw(&textImage);
}
