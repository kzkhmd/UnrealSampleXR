// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidWifiScanner.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJavaEnv.h"
#endif


FOnReceiveWifiScanDataDelegate UAndroidWifiScanner::OnReceiveWifiScanDataDelegate;


FString UAndroidWifiScanner::GetPath()
{
	UE_LOG(LogTemp, Error, TEXT("GetPath"));

	FString result = FString("");
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	if (Env != nullptr)
	{
		jclass WifiScannerClass = AndroidJavaEnv::FindJavaClassGlobalRef("com/example/mylibrary/WifiScanner");			// 使用するクラスを取得
		jmethodID WifiScannerConstructor = Env->GetMethodID(WifiScannerClass, "<init>", "()V");						// コンストラクタを取得
		jobject WifiScannerObj = Env->NewObject(WifiScannerClass, WifiScannerConstructor);							// インスタンス化
		jmethodID GetPicturesPathID = Env->GetMethodID(WifiScannerClass, "getPicturesPath", "()Ljava/lang/String;");		// インスタンスメソッドIDを取得
		jstring PathString = (jstring) Env->CallObjectMethod(WifiScannerObj, GetPicturesPathID);											// インスタンスメソッドを実行
		
		const char* nativePathString = Env->GetStringUTFChars(PathString, 0);
		result = FString(nativePathString);
	}
#endif

	return result;
}


FString UAndroidWifiScanner::StartScan()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	UE_LOG(LogTemp, Error, TEXT("StartScan"));

	if (Env != nullptr)
	{
		jclass WifiScannerClass = AndroidJavaEnv::FindJavaClassGlobalRef("com/example/mylibrary/WifiScanner");			// 使用するクラスを取得

		jmethodID WifiScannerConstructor = Env->GetMethodID(WifiScannerClass, "<init>", "()V");						// コンストラクタを取得
		jobject WifiScannerObj = Env->NewObject(WifiScannerClass, WifiScannerConstructor);							// インスタンス化
		jmethodID StartScanID = Env->GetMethodID(WifiScannerClass, "startScan", "(Landroid/app/Activity;)V");		// インスタンスメソッドIDを取得

		jobject GameActivityThis = FAndroidApplication::GetGameActivityThis();										// GameActivityのインスタンスを取得
		Env->CallVoidMethod(WifiScannerObj, StartScanID, GameActivityThis);											// インスタンスメソッドを実行

		UE_LOG(LogTemp, Error, TEXT("StartScan Did"));
	}
#endif

	return FString("StartScan");
}


void UAndroidWifiScanner::BindToOnReceiveWifiScanDataDelegate(const FOnReceiveWifiScanDataDelegate& delegate)
{
	OnReceiveWifiScanDataDelegate = delegate;
}


void UAndroidWifiScanner::ExecuteOnReceiveWifiScanDataDelegate(const FString& ssid)
{
	OnReceiveWifiScanDataDelegate.ExecuteIfBound(ssid);
}


#if PLATFORM_ANDROID
extern "C" JNIEXPORT void JNICALL
Java_com_example_mylibrary_WifiScanner_dispatchSSID(JNIEnv* Env, jobject Obj, jstring Ssid)
{
	UE_LOG(LogTemp, Warning, TEXT("dispatchSSID"));

	if (Env != nullptr)
	{
		const char* c_ssid = Env->GetStringUTFChars(Ssid, nullptr);
		const FString s_ssid = c_ssid;

		UE_LOG(LogTemp, Warning, TEXT("did dispatchSSID"));

		UAndroidWifiScanner::ExecuteOnReceiveWifiScanDataDelegate(s_ssid);
	}
}
#endif
