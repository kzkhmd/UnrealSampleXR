package com.example.mylibrary;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;


public class BatteryObserver {

	private BroadcastReceiver batteryObserver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			processIntent(intent);
		}
	};

	private int batteryStatus = 0;
	private int batteryLevel = 0;
	private int batteryTemperature = 0;

	public void startReceiver(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		activity.registerReceiver(batteryObserver, filter);
	}

	private void processIntent(final Intent intent) {
		// TODO: The following functions should use the proper extra strings, ie BatteryManager.EXTRA_SCALE
		boolean isPresent = intent.getBooleanExtra("present", false);
		if (isPresent) 
		{
			int status = intent.getIntExtra("status", 0);
			int rawlevel = intent.getIntExtra("level", -1);
			int scale = intent.getIntExtra("scale", -1);
			// temperature is in tenths of a degree centigrade
			int temperature = intent.getIntExtra("temperature", 0);
			// always tell native code what the battery level is
			int level = 0;
			if ( rawlevel >= 0 && scale > 0) 
			{
				level = (rawlevel * 100) / scale;
			}
			if ( status != batteryStatus ||
				 level != batteryLevel ||
				 temperature != batteryTemperature) 
			{
				batteryStatus = status;
				batteryLevel = level;
				batteryTemperature = temperature;
				dispatchEvent(status,level,temperature);
			}
		}
	}

	public native void dispatchEvent(int status, int level, int temperature);

}