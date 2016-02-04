#include <jni.h>
#include <GLES2/gl2.h>

#include <android/log.h>

#include <cstdint>
#include <cassert>
#include <string>

#include "EcgArea.h"
#include "Helper.h"
#include "log.h"
#include "PacketRouter.h"
#include "DataFormat/PacketReader.hpp"

const int LOOPER_ID_USER = 3;


class sensorgraph {

 public:
    sensorgraph() {}


    void init(AAssetManager *assetManager) {
        EcgArea::instance().init(assetManager);
    }

    void surfaceCreated() {
        LOGI("GL_VERSION: %s", glGetString(GL_VERSION));
        LOGI("GL_VENDOR: %s", glGetString(GL_VENDOR));
        LOGI("GL_RENDERER: %s", glGetString(GL_RENDERER));
        LOGI("GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        EcgArea::instance().glInit();
        EcgArea::instance().setZOrder(1);
    }

    void surfaceChanged(int w, int h) {
        glViewport(0, 0, w, h);
        EcgArea::instance().contextResized(w,h);
        EcgArea::instance().redraw();
    }

    void setDpcm(float x, float y){
        EcgArea::instance().setPixelDensity(Vec2<float>(x,y));
        EcgArea::instance().redraw();
    }

    void render() {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        EcgArea::instance().draw();
    }

    void pause() {

    }

    void resume() {
        EcgArea::instance().redraw();
    }
};

sensorgraph gSensorGraph;

static JavaVM* cachedJVM;

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_init(JNIEnv *env, jclass type, jobject assetManager) {
        (void)type;
        AAssetManager *nativeAssetManager = AAssetManager_fromJava(env, assetManager);
        gSensorGraph.init(nativeAssetManager);

    }

    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_surfaceCreated(JNIEnv *env, jclass type) {
        (void)env;
        (void)type;
        gSensorGraph.surfaceCreated();
    }

    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_surfaceChanged(JNIEnv *env, jclass type, jint width,
                                                     jint height) {
        (void)env;
        (void)type;
        gSensorGraph.surfaceChanged(width, height);
    }


    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_setDotPerCM(JNIEnv *env, jclass type, jfloat xdpcm,
                                                           jfloat ydpcm) {
        (void)env;
        (void)type;
        gSensorGraph.setDpcm(xdpcm, ydpcm);
    }


    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_drawFrame(JNIEnv *env, jclass type) {
        (void)env;
        (void)type;
        gSensorGraph.render();
    }

    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_pause(JNIEnv *env, jclass type) {
        (void)env;
        (void)type;
        gSensorGraph.pause();
    }

    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_resume(JNIEnv *env, jclass type) {
        (void)env;
        (void)type;
        gSensorGraph.resume();
    }

    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_processEcgData(JNIEnv *env, jclass type, jbyteArray jdata, jint size) {
        (void)type;

        jbyte* data = env->GetByteArrayElements(jdata, 0);
        char* chars = (char*) data;

        static PacketReader packetReader;
        for(int i=0; i < size; ++i) {
            packetReader.addByte(chars[i]);
            if(packetReader.isPacketReady()) {
                PacketRouter::instance().packetReceived(packetReader.getPacketHeader(), packetReader.getPacketData());
            }
        }
        env->ReleaseByteArrayElements(jdata, data, 0);
    }

    JNIEXPORT void JNICALL
    Java_com_android_sensorgraph_SensorGraphJNI_setTestBitmap(JNIEnv *env, jclass type, jbyteArray jdata, jint width, jint height) {
        (void)type;

        jbyte* data = env->GetByteArrayElements(jdata, 0);
        char* chars = (char*) data;

        EcgArea::instance().testText.setBitmap(chars, width, height);
    }
}
