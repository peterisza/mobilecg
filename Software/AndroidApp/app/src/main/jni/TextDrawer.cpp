/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Peter Isza, Robert Csordas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "TextDrawer.h"
#include "Helper.h"
#include "EcgArea.h"
#include "log.h"

#include <jni.h>

extern JavaVM* cachedJVM;

TextDrawer::TextDrawer():
    textSizeMM(2),
    color(0xFF0000FF)
{
}

TextDrawer& TextDrawer::drawText(const char* text){
    const Vec2<float> &pixelDensity = EcgArea::instance().getPixelDensity();
    int pixelSize = pixelDensity[1]/10.0*textSizeMM;

    JNIEnv *env;
    (cachedJVM)->AttachCurrentThread(&env, NULL);

    jclass jTextRenderer = env->FindClass("com/mobilecg/androidapp/TextRenderer");
    jmethodID constructor = env->GetMethodID(jTextRenderer, "<init>", "()V");
    jmethodID setText = env->GetMethodID(jTextRenderer, "setText", "(Ljava/lang/String;II)V");
    jmethodID getHeight = env->GetMethodID(jTextRenderer, "getHeight", "()I");
    jmethodID getWidth = env->GetMethodID(jTextRenderer, "getWidth", "()I");
    jmethodID renderToBitmap = env->GetMethodID(jTextRenderer, "renderToBitmap", "([B)V");

    jobject obj = env->NewObject(jTextRenderer, constructor);
    jstring jText = env->NewStringUTF(text);

    env->CallVoidMethod(obj, setText, jText, pixelSize, color);
    int height = (int)env->CallIntMethod(obj, getHeight);
    int width = (int)env->CallIntMethod(obj, getWidth);

    jbyteArray bitmap = env->NewByteArray(height*width*4);
    env->CallVoidMethod(obj, renderToBitmap, bitmap);

    const char* data = (const char*) env->GetByteArrayElements(bitmap, 0);
    setBitmap(data, width, height);

    env->DeleteLocalRef(bitmap);
    return *this;
}

void TextDrawer::setBitmap(const char* data, int width, int height) {
    setSize(width, height);
    textImage.resize(width, height);
    textImage.setBitmap(data);
    redraw(&textImage);
}

TextDrawer& TextDrawer::setColor(const Image::Pixel& p) {
    color = (p.a << 24) + (p.r << 16) + (p.g << 8) + p.b;
    return *this;
}

TextDrawer& TextDrawer::setTextSizeMM(float isize) {
    textSizeMM = isize;
    return *this;
}
