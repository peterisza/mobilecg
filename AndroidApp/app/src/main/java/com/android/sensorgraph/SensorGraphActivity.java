/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.sensorgraph;

import android.app.Activity;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.DisplayMetrics;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

public class SensorGraphActivity extends Activity {

    GLSurfaceView mView;
    DisplayMetrics displayMetrics;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);


        BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
        //BluetoothDevice device = btAdapter.getRemoteDevice("00:17:E9:B5:D8:7C");

        BluetoothDevice device = btAdapter.getRemoteDevice("00:17:E9:B6:13:0E");

        ConnectThread receiver=new ConnectThread(device);
        receiver.start();

        displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);

        mView = new GLSurfaceView(getApplication());
        mView.setEGLContextClientVersion(2);
        mView.setEGLConfigChooser(new MultisampleConfig());
        mView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                gl.glEnable(gl.GL_LINE_SMOOTH);
                gl.glHint(gl.GL_LINE_SMOOTH_HINT, gl.GL_NICEST);
                SensorGraphJNI.surfaceCreated();
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                gl.glEnable( gl.GL_LINE_SMOOTH );
                gl.glHint(gl.GL_LINE_SMOOTH_HINT, gl.GL_NICEST);
                SensorGraphJNI.setDotPerCM(displayMetrics.xdpi / 2.54f, displayMetrics.ydpi / 2.54f);
                SensorGraphJNI.surfaceChanged(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                SensorGraphJNI.drawFrame();
            }
        });
        mView.queueEvent(new Runnable() {
            @Override
            public void run() {
                SensorGraphJNI.init(getAssets());
            }
        });
        setContentView(mView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mView.onPause();
        mView.queueEvent(new Runnable() {
            @Override
            public void run() {
                SensorGraphJNI.pause();
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        mView.onResume();
        mView.queueEvent(new Runnable() {
            @Override
            public void run() {
                SensorGraphJNI.resume();
            }
        });
    }
}
