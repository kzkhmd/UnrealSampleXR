package com.example.mylibrary;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.Environment;

import androidx.annotation.Keep;

import java.io.File;
import java.lang.String;
import java.util.ArrayList;
import java.util.List;


public class WifiScanner {

    WifiManager wifiManager;

    BroadcastReceiver wifiScanReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            boolean success = intent.getBooleanExtra(WifiManager.EXTRA_RESULTS_UPDATED, false);

            if (success) {
                scanSuccess();
            } else {
                scanFailure();
            }
        }
    };

    private void scanSuccess() {
        List<ScanResult> scanResults = wifiManager.getScanResults();

        List<String> scanSsidResults = new ArrayList<String>();
        for(ScanResult scanResult : scanResults) {
            scanSsidResults.add(scanResult.BSSID);
        }

        String[] ssids = scanSsidResults.toArray(new String[scanSsidResults.size()]);

        dispatchSSID(ssids[0]);
    }

    private void scanFailure() {
        List<ScanResult> scanResults = wifiManager.getScanResults();
    }

    public void startScan(Activity activity) {
        wifiManager = (WifiManager) activity.getSystemService(Context.WIFI_SERVICE);

        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION);
        activity.registerReceiver(wifiScanReceiver, intentFilter);
    }

    public String getPicturesPath() {
        File f = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
        dispatchSSID(f.getPath());
        return f.getPath();
    }

    public native void dispatchSSID(String ssid);

}
