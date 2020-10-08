// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/ActorComponent.h>
#include "Networking/Public/Networking.h"
#include "TCP_Server.generated.h"

UCLASS()
class RTUBIRD_API UTCP_Server : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UTCP_Server();

	UFUNCTION(BlueprintCallable)
		bool ReceiveData(FString& Message);
	UFUNCTION(BlueprintCallable)
		void SendData(FString Message);

	bool AcceptConnection(FSocket*, const FIPv4Endpoint&);
	FSocket* ConnectionSocket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
