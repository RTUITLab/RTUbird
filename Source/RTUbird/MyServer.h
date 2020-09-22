// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/NoExportTypes.h"
#include "Networking/Public/Networking.h"

#include "MyServer.generated.h"

/**
 * 
 */
UCLASS()
class RTUBIRD_API UMyServer : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UMyServer() {};
	~UMyServer() {};

	//UFUNCTION(BluePrintCallable, Category = Sockets)
	UFUNCTION(BlueprintCallable, Category = Sockets)
	static bool SendMessage(const FString IP_addr, const FString Message);
	
};
