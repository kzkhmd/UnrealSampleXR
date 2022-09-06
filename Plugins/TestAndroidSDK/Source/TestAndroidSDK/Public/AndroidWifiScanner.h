// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#if PLATFORM_ANDROID
#include "Android/AndroidJavaEnv.h"
#endif
#include "AndroidWifiScanner.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnReceiveWifiScanDataDelegate, const FString&, ssid);

/**
 * 
 */
UCLASS(Blueprintable)
class TESTANDROIDSDK_API UAndroidWifiScanner : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static FString GetPath();

	UFUNCTION(BlueprintCallable)
	static FString StartScan();

	UFUNCTION(BlueprintCallable)
	static void BindToOnReceiveWifiScanDataDelegate(const FOnReceiveWifiScanDataDelegate& delegate);

	static void ExecuteOnReceiveWifiScanDataDelegate(const FString& ssid);

private:
	static FOnReceiveWifiScanDataDelegate OnReceiveWifiScanDataDelegate;
};
