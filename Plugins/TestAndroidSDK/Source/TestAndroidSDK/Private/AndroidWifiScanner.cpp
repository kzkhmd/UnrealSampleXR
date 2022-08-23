// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidWifiScanner.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJavaEnv.h"
#endif


void UAndroidWifiScanner::StartScan()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	if (Env != nullptr)
	{
		jclass WifiScannerClass = FAndroidApplication::FindJavaClass("com/example/mylibrary/WifiScanner");	// 使用するクラスを取得

		JNINativeMethod NativeMethod = {"dispatchSSID", "(Ljava/lang/String)V", (void*)DispatchSSID};		// コールバック関数を登録
		Env->RegisterNatives(WifiScannerClass, &NativeMethod, 1);											// コールバック関数を登録

		jmethodID WifiScannerConstructor = Env->GetMethodID(WifiScannerClass, "<init>", "()V");				// コンストラクタを取得
		jobject WifiScannerObj = Env->NewObject(WifiScannerClass, WifiScannerConstructor);					// インスタンス化
		jmethodID StartScanID = Env->GetMethodID(WifiScannerClass, "startScan", "(Landroid/app/Activity;)V");	// インスタンスメソッドIDを取得

		jobject GameActivityThis = FAndroidApplication::GetGameActivityThis();								// GameActivityのインスタンスを取得
		Env->CallVoidMethod(WifiScannerObj, StartScanID, GameActivityThis);									// インスタンスメソッドを実行
	}
	
#endif
}

#if PLATFORM_ANDROID
void UAndroidWifiScanner::OnReceive(JNIEnv* Env, jobject Obj, jstring Ssid)
{
	;
}
#endif
