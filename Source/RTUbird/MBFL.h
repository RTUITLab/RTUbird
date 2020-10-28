// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MBFL.generated.h"

class UTexture2D;
/**
 * 
 */
UCLASS()
class RTUBIRD_API UMBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintCallable)
		static UTexture2D* GenerateQrCode(UObject* parent, FString string);
};
