#include <jni.h>
#include <GLES2/gl2.h>

#include <android/log.h>

#include <android/sensor.h>

#include <cstdint>
#include <cassert>
#include <string>

#include "EcgArea.h"
#include "Helper.h"

#define  LOG_TAG    "sensorgraph"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

const int LOOPER_ID_USER = 3;
const int SENSOR_HISTORY_LENGTH = 100;
const int SENSOR_REFRESH_RATE = 100;
const float SENSOR_FILTER_ALPHA = 0.1f;


class sensorgraph {
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    ASensorManager *sensorManager;
    const ASensor *accelerometer;
    ASensorEventQueue *accelerometerEventQueue;
    ALooper *looper;

    GLuint shaderProgram;
    GLuint vPositionHandle;
    GLuint vSensorValueHandle;
    GLuint uFragColorHandle;
    GLfloat xPos[SENSOR_HISTORY_LENGTH];

    struct AccelerometerData {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };
    AccelerometerData sensorData[SENSOR_HISTORY_LENGTH*2];
    AccelerometerData sensorDataFilter;
    int sensorDataIndex;


 public:
    sensorgraph() : sensorDataIndex(0) {}


    void init(AAssetManager *assetManager) {
        EcgArea::instance().init(assetManager);

        vertexShaderSource=helper::loadAsset(assetManager, "shader.vert");
        fragmentShaderSource=helper::loadAsset(assetManager, "shader.frag");


        sensorManager = ASensorManager_getInstance();
        assert(sensorManager != NULL);
        accelerometer = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
        assert(accelerometer != NULL);
        looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
        assert(looper != NULL);
        accelerometerEventQueue = ASensorManager_createEventQueue(sensorManager, looper,
                                                                  LOOPER_ID_USER, NULL, NULL);
        assert(accelerometerEventQueue != NULL);
        int setEventRateResult = ASensorEventQueue_setEventRate(accelerometerEventQueue,
                                                                accelerometer,
                                                                int32_t(1000000 /
                                                                        SENSOR_REFRESH_RATE));
        int enableSensorResult = ASensorEventQueue_enableSensor(accelerometerEventQueue,
                                                                accelerometer);
        assert(enableSensorResult >= 0);

        generateXPos();
    }

    void surfaceCreated() {
        LOGI("GL_VERSION: %s", glGetString(GL_VERSION));
        LOGI("GL_VENDOR: %s", glGetString(GL_VENDOR));
        LOGI("GL_RENDERER: %s", glGetString(GL_RENDERER));
        LOGI("GL_EXTENSIONS: %s", glGetString(GL_EXTENSIONS));

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        EcgArea::instance().glInit();
        EcgArea::instance().setZOrder(1);

        shaderProgram = helper::createGlProgram(vertexShaderSource, fragmentShaderSource);
        assert(shaderProgram != 0);
        vPositionHandle = helper::getGlAttributeWithAssert(shaderProgram, "vPosition");
        vSensorValueHandle = helper::getGlAttributeWithAssert(shaderProgram, "vSensorValue");
        uFragColorHandle = helper::getGlUniformWithAssert(shaderProgram, "uFragColor");
    }

    void surfaceChanged(int w, int h) {
        glViewport(0, 0, w, h);
        EcgArea::instance().contextResized(w,h);
    }

    void generateXPos() {
        for (auto i = 0; i < SENSOR_HISTORY_LENGTH; i++) {
            float t = static_cast<float>(i) / static_cast<float>(SENSOR_HISTORY_LENGTH - 1);
            xPos[i] = -1.f * (1.f - t) + 1.f * t;
        }
    }

    void update() {
        ALooper_pollAll(0, NULL, NULL, NULL);
        ASensorEvent event;
        float a = SENSOR_FILTER_ALPHA;
        while (ASensorEventQueue_getEvents(accelerometerEventQueue, &event, 1) > 0) {
            sensorDataFilter.x = a * event.acceleration.x + (1.0f - a) * sensorDataFilter.x;
            sensorDataFilter.y = a * event.acceleration.y + (1.0f - a) * sensorDataFilter.y;
            sensorDataFilter.z = a * event.acceleration.z + (1.0f - a) * sensorDataFilter.z;
        }
        sensorData[sensorDataIndex] = sensorDataFilter;
        sensorData[SENSOR_HISTORY_LENGTH+sensorDataIndex] = sensorDataFilter;
        sensorDataIndex = (sensorDataIndex + 1) % SENSOR_HISTORY_LENGTH;
    }

    void render() {
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        EcgArea::instance().draw();

        glUseProgram(shaderProgram);

        glEnableVertexAttribArray(vPositionHandle);
        glVertexAttribPointer(vPositionHandle, 1, GL_FLOAT, GL_FALSE, 0, xPos);

        glEnableVertexAttribArray(vSensorValueHandle);
        glVertexAttribPointer(vSensorValueHandle, 1, GL_FLOAT, GL_FALSE, sizeof(AccelerometerData),
                              &sensorData[sensorDataIndex].x);

        glUniform4f(uFragColorHandle, 1.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, SENSOR_HISTORY_LENGTH);

        glVertexAttribPointer(vSensorValueHandle, 1, GL_FLOAT, GL_FALSE, sizeof(AccelerometerData),
                              &sensorData[sensorDataIndex].y);
        glUniform4f(uFragColorHandle, 1.0f, 0.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, SENSOR_HISTORY_LENGTH);

        glVertexAttribPointer(vSensorValueHandle, 1, GL_FLOAT, GL_FALSE, sizeof(AccelerometerData),
                              &sensorData[sensorDataIndex].z);
        glUniform4f(uFragColorHandle, 0.0f, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_LINE_STRIP, 0, SENSOR_HISTORY_LENGTH);
    }

    void pause() {
        ASensorEventQueue_disableSensor(accelerometerEventQueue, accelerometer);
    }

    void resume() {
        ASensorEventQueue_enableSensor(accelerometerEventQueue, accelerometer);
    }
};

sensorgraph gSensorGraph;

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
    Java_com_android_sensorgraph_SensorGraphJNI_drawFrame(JNIEnv *env, jclass type) {
        (void)env;
        (void)type;
        gSensorGraph.update();
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
}
