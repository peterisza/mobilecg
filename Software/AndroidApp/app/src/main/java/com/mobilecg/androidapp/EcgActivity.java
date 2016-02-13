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

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.util.DisplayMetrics;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;


public class EcgActivity extends Activity {

    private GLSurfaceView mView;
    private DisplayMetrics displayMetrics;
    private ConnectThread receiver;
    private final int BLUETOOTH_SELECTED=1;


    private void disconnect(){
        if (receiver!=null){
            if (receiver.isConnected())
                return;

            if (receiver.isAlive())
                receiver.interrupt();

            receiver=null;
        }
    }
    private boolean connect(){
        disconnect();
        String mac=getPairedMac();
        if (mac!="") {
            receiver = new ConnectThread();
            receiver.connect(mac);

            return true;
        }

        return false;
    }

    private void openScanWindow(){
        disconnect();
        Intent scannerIntent = new Intent(getBaseContext(), BluetoothDeviceList.class);
        startActivityForResult(scannerIntent,BLUETOOTH_SELECTED);
    }

    private void setPairedMac(String mac){
        SharedPreferences sharedPref = getPreferences(getBaseContext().MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPref.edit();
        editor.putString("MAC", mac);
        editor.commit();
    }

    private String getPairedMac(){
        SharedPreferences sharedPref = getPreferences(getBaseContext().MODE_PRIVATE);
        return sharedPref.getString("MAC","");
    }

    @Override
    protected void onCreate(Bundle icicle) {
        receiver=null;
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


        if (!connect()){
            openScanWindow();
        }

        displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);

        mView = new GLSurfaceView(getApplication());
        mView.setEGLContextClientVersion(2);
        mView.setEGLConfigChooser(new MultisampleConfig());

        mView.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View v) {
                openOptionsMenu();
                return true;
            }
        });

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


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main_menu, menu);//Menu Resource, Menu
        return true;
    }
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.reconnect:
                connect();
                return true;
            case R.id.scan:
                openScanWindow();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    protected void onActivityResult (int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case BLUETOOTH_SELECTED:
                // When BluetoothDeviceList returns with a device to connect
                if (resultCode == Activity.RESULT_OK) {
                    String mac = (String) data.getExtras()
                            .get(BluetoothDeviceList.EXTRA_DEVICE);

                    setPairedMac(mac);
                    connect();
                }
                break;
        }
    }
}
