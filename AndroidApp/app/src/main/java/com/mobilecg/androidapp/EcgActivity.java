package com.mobilecg.androidapp;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.util.DisplayMetrics;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.view.View;
import android.view.WindowManager;

import java.nio.ByteBuffer;

public class EcgActivity extends Activity {

    GLSurfaceView mView;
    DisplayMetrics displayMetrics;

    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // Hide both the navigation bar and the status bar.
        // SYSTEM_UI_FLAG_FULLSCREEN is only available on Android 4.1 and higher, but as
        // a general rule, you should design your app to hide the status bar whenever you
        // hide the navigation bar.
        if(Build.VERSION.SDK_INT > 11 && Build.VERSION.SDK_INT < 19) { // lower api
            View v = this.getWindow().getDecorView();
            v.setSystemUiVisibility(View.GONE);
        } else if(Build.VERSION.SDK_INT >= 19) {
            //for new api versions.
            View decorView = getWindow().getDecorView();
            int uiOptions = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
            decorView.setSystemUiVisibility(uiOptions);
        }


        BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();
        BluetoothDevice device = btAdapter.getRemoteDevice("00:17:E9:B5:D8:7C");

        //BluetoothDevice device = btAdapter.getRemoteDevice("00:17:E9:B6:13:0E");

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
                EcgJNI.surfaceCreated();
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                gl.glEnable(gl.GL_LINE_SMOOTH);
                gl.glHint(gl.GL_LINE_SMOOTH_HINT, gl.GL_NICEST);
                EcgJNI.setDotPerCM(displayMetrics.xdpi / 2.54f, displayMetrics.ydpi / 2.54f);
                EcgJNI.surfaceChanged(width, height);
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                EcgJNI.drawFrame();
            }
        });
        mView.queueEvent(new Runnable() {
            @Override
            public void run() {
                EcgJNI.init(getAssets());
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
                EcgJNI.pause();
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
                EcgJNI.resume();
            }
        });
    }
}
