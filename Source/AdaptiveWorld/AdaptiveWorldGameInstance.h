// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdaptiveWorldGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ADAPTIVEWORLD_API UAdaptiveWorldGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AdativeWorld")
	void StartListenServer();
	UFUNCTION(BlueprintCallable, Category = "AdativeWorld")
	void JoinAsCient(FString IPAddress);
	UFUNCTION(BlueprintCallable, Category = "AdativeWorld")
	void Leaveame();
};
