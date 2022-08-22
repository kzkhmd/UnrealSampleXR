// Fill out your copyright notice in the Description page of Project Settings.


#include "WifiScanner.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#endif


#if PLATFORM_ANDROID
void dispatchSSID(JNIEnv* Env, jobject Obj, jstring ssid)
{
	;
}
#endif

void UWifiScanner::StartScan()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	if (Env != nullptr)
	{
		jclass WifiScannerClass = FAndroidApplication::FindJavaClass("com/example/mylibrary/WifiScanner");	// 使用するクラスを取得
		jmethodID WifiScannerConstructor = Env->GetMethodID(WifiScannerClass, "<init>", "()V");				// コンストラクタを取得

		JNINativeMethod NativeMethod = {"dispatchSSID", "(Ljava/lang/String)V", (void*)dispatchSSID};		// コールバック関数を登録
		Env->RegisterNatives(WifiCannerClass, &NativeMethod, 1);											// コールバック関数を登録

		jobject WifiScannerObj = Env->NewObject(WifiScannerClass, WifiScannerConstructor);					// インスタンス化

		jmethodID StartScanID = Env->GetMethodID(WifiScannerClass, "StartScan", "(Landroid/app/Activity;)V");	// インスタンスメソッドIDを取得

		extern struct android_app* GNativeAndroidApp;
		Env->CallVoidMethod(WifiScannerObj, StartScanID, GNativeAndroidApp->activity->clazz);
	}
	
#endif
}
