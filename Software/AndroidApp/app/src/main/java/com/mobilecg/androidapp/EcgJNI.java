/*
 * This file is part of MobilECG, an open source clinical grade Holter
 * ECG. For more information visit http://mobilecg.hu
 *
 * Copyright (C) 2016  Robert Csordas, Peter Isza
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
