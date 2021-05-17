// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <thread>
#include "GetSettings.generated.h"

USTRUCT()
struct FTest {
	GENERATED_BODY()

	UPROPERTY()
		FString Serv_addr;
	UPROPERTY()
		FString Cli_addr;
	UPROPERTY()
		FString NPath;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTUBIRD_API UGetSettings : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGetSettings();

	UFUNCTION(BlueprintCallable) 
		FString ReadFile(FString filename, FString key);
	UFUNCTION(BlueprintCallable)
		void WriteInFile(FString filename, FString text);

	std::thread t;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		// ...
	}
		
};
