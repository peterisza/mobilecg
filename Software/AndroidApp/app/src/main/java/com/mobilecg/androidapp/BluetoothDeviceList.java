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

package com.mobilecg.androidapp;

import java.util.ArrayList;
import java.util.Set;

import android.os.Bundle;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothClass;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class BluetoothDeviceList extends Activity {
    public static String EXTRA_DEVICE = "device";


    private static class BluetoothDeviceAdapter extends BaseAdapter{
        private LayoutInflater inflater=null;
        private ArrayList<BluetoothDevice> devices;

        public BluetoothDeviceAdapter(final Activity owner, ArrayList<BluetoothDevice> devices) {
            inflater = (LayoutInflater)owner.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            this.devices=devices;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            View view;
            if(convertView==null)
                view = inflater.inflate(R.layout.devicetable_row, null);
            else
                view = convertView;

            if (view!=null){
                TextView name = (TextView)view.findViewById(R.id.deviceName);
                TextView mac = (TextView)view.findViewById(R.id.macAddress);
                ImageView icon= (ImageView)view.findViewById(R.id.deviceIcon);

                BluetoothDevice device=(BluetoothDevice)getItem(position);
                String n=device.getName();
                name.setText(n);
                mac.setText(device.getAddress());


                if (n.startsWith("MobilECG")) {
                    icon.setImageResource(R.mipmap.ic_launcher);
                } else {
                    icon.setImageResource(R.mipmap.action_help);
                }

            }
            view.setClickable(false);
            return view;
        }

        @Override
        public int getCount() {
            return devices.size();
        }

        @Override
        public Object getItem(int position) {
            return devices.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }
    }


    private BluetoothDeviceAdapter deviceAdapter;
    private ArrayList<BluetoothDevice> deviceList;
    private BluetoothAdapter bluetoothAdapter;
    private RelativeLayout rescanLayout;

    private void addDevice(BluetoothDevice device){
        deviceList.add(device);
        deviceAdapter.notifyDataSetChanged();
    }

    private void removeDeviceList(){
        deviceList.clear();
        deviceAdapter.notifyDataSetChanged();
    }

    private final BroadcastReceiver eventReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();

            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                // If it's already paired, skip it, because it's been listed already
                if (device.getBondState() != BluetoothDevice.BOND_BONDED) {
                    addDevice(device);
                }
            } else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(action)) {
                hideScanningIndicator();
            }
        }
    };

    void showScanningIndicator(){
        setProgressBarIndeterminateVisibility(true);
        setProgressBarVisibility(true);
        rescanLayout.setVisibility(View.GONE);
    }

    void hideScanningIndicator(){
        setProgressBarIndeterminateVisibility(false);
        setProgressBarVisibility(false);
        rescanLayout.setVisibility(View.VISIBLE);
    }

    private void fetchPairedDevices(){
        // Get a set of currently paired devices
        Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();

        // If there are paired devices, add each one to the ArrayAdapter
        if (pairedDevices.size() > 0) {
            for (BluetoothDevice device : pairedDevices) {
                addDevice(device);
            }
        }
    }

    private void itemSelected(int position){
        BluetoothDevice dev=deviceList.get(position);

        bluetoothAdapter.cancelDiscovery();

        // Create the result Intent and include the MAC address
        Intent intent = new Intent();
        intent.putExtra(EXTRA_DEVICE, dev.getAddress());

        // Set result and finish this Activity
        setResult(Activity.RESULT_OK, intent);

        removeDeviceList();
        finish();
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        bluetoothAdapter=BluetoothAdapter.getDefaultAdapter();

        requestWindowFeature(Window.FEATURE_INDETERMINATE_PROGRESS);
        requestWindowFeature(Window.FEATURE_PROGRESS);

        setContentView(R.layout.bluetooth_device_list);

        deviceList=new ArrayList<BluetoothDevice>();
        deviceAdapter=new BluetoothDeviceAdapter(this,deviceList);

        ListView deviceListView=(ListView)findViewById(R.id.bluetoothList);
        deviceListView.setAdapter(deviceAdapter);

        deviceListView.setOnItemClickListener(new OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View item, int position,
                                    long id) {

                itemSelected(position);
            }

        });


        // Register for broadcasts when discovery has finished
        IntentFilter filter = new IntentFilter(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        this.registerReceiver(eventReceiver, filter);

        // Register for broadcasts when a device is discovered
        filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        this.registerReceiver(eventReceiver, filter);



        rescanLayout=(RelativeLayout)findViewById(R.id.RescanLayout);

        rescanLayout.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                startScanning();
            }
        });


        setResult(Activity.RESULT_CANCELED);

        startScanning();
    }




    private void startScanning(){
        showScanningIndicator();

        deviceList.clear();
        fetchPairedDevices();

        if (bluetoothAdapter.isDiscovering()) {
            bluetoothAdapter.cancelDiscovery();
        }

        bluetoothAdapter.startDiscovery();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        removeDeviceList();

        if (bluetoothAdapter != null) {
            bluetoothAdapter.cancelDiscovery();
        }

        // Unregister broadcast listeners
        this.unregisterReceiver(eventReceiver);
    }

}