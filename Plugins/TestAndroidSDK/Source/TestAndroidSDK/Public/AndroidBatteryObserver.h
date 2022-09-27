// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AndroidBatteryObserver.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnReceiveBatteryStatusDelegate, int, status);


/**
 * 
 */
UCLASS()
class TESTANDROIDSDK_API UAndroidBatteryObserver : public UObject
{
	GENERATED_BODY()
	
public:
	static void ExecuteOnReceiveBatteryStatusDelegate(int status);

	UFUNCTION(BlueprintCallable)
	static void BindToOnReceiveBatteryStatusDelegate(const FOnReceiveBatteryStatusDelegate& delegate);

	UFUNCTION(BlueprintCallable)
	static void StartReceiver();

private:
	static FOnReceiveBatteryStatusDelegate OnReceiveBatteryStatusDelegate;
};
