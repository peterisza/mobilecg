package com.mobilecg.androidapp;

// Wrapper for native library

import android.content.res.AssetManager;

public class EcgJNI {

     static {
         System.loadLibrary("ecg");
     }

     public static native void init(AssetManager assetManager);
     public static native void surfaceCreated();
     public static native void surfaceChanged(int width, int height);
     public static native void setDotPerCM(float xdpcm, float ydpcm);
     public static native void drawFrame();
     public static native void pause();
     public static native void resume();
     public static native void processEcgData(byte[] data, int size);
     public static native void onDeviceConnected();
     public static native void onDeviceDisconnected();
}
