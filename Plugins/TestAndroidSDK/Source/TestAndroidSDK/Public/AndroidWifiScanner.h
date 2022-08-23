// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJavaEnv.h"
#endif
#include "AndroidWifiScanner.generated.h"

/**
 * 
 */
UCLASS()
class TESTANDROIDSDK_API UAndroidWifiScanner : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartScan();

	UFUNCTION(BlueprintImplementableEvent)
	void OnReceiveWifiScanData(const FString& Ssid);

#if PLATFORM_ANDROID
private:
	void OnReceive(JNIEnv* Env, jobject Obj, jstring Ssid);
#endif
};
