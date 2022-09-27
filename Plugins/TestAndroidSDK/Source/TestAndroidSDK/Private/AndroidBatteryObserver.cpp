// Fill out your copyright notice in the Description page of Project Settings.


#include "AndroidBatteryObserver.h"

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJavaEnv.h"
#endif


FOnReceiveBatteryStatusDelegate UAndroidBatteryObserver::OnReceiveBatteryStatusDelegate;


void UAndroidBatteryObserver::ExecuteOnReceiveBatteryStatusDelegate(int status)
{
	OnReceiveBatteryStatusDelegate.ExecuteIfBound(status);
}

void UAndroidBatteryObserver::BindToOnReceiveBatteryStatusDelegate(const FOnReceiveBatteryStatusDelegate& delegate)
{
	OnReceiveBatteryStatusDelegate = delegate;
}

void UAndroidBatteryObserver::StartReceiver()
{
#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	if (Env != nullptr)
	{
		jclass BatteryObserverClass = FAndroidApplication::FindJavaClass("com/example/mylibrary/BatteryObserver");

		jmethodID BatteryObserverConstructor = Env->GetMethodID(BatteryObserverClass, "<init>", "()V");
		jobject BatteryObserverObj = Env->NewObject(BatteryObserverClass, BatteryObserverConstructor);
		jmethodID StartReceiverID = Env->GetMethodID(BatteryObserverClass, "startReceiver", "(Landroid/app/Activity;)V");

		jobject GameActivityThis = FAndroidApplication::GetGameActivityThis();
		Env->CallVoidMethod(BatteryObserverObj, StartReceiverID, GameActivityThis);
	}
#endif
}

#if PLATFORM_ANDROID
extern "C" JNIEXPORT void JNICALL
Java_com_example_mylibrary_BatteryObserver_dispatchEvent(JNIEnv* env, jobject obj, jint status, jint level, jint temperature)
{
	if(env != nullptr)
	{
		UAndroidBatteryObserver::ExecuteOnReceiveBatteryStatusDelegate(temperature);
	}
}
#endif
