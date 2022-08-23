// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif
#include "WifiScanner.generated.h"

/**
 * 
 */
UCLASS()
class TESTANDROIDSDK_API UWifiScanner : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void StartScan();

	UFUNCTION(BlueprintImplementableEvent)
	void NotifySSID(FString ssid);

private:
#if PLATFORM_ANDROID
	void DispatchSSID(JNIEnv* Env, jobject Obj, jstring ssid);
#endif
};
