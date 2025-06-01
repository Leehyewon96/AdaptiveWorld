// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AdaptiveWorldGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerChangedDelegate, float, Timer);

UCLASS()
class ADAPTIVEWORLD_API AAdaptiveWorldGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld")
	void OnTimerChanged();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnTimerChanged, Category = "AdaptiveWorld")
	float Timer = 0;
	

public:
	UPROPERTY(BlueprintAssignable, Category = "AdaptiveWorld")
	FOnTimerChangedDelegate OnTimerChangedDelegate;
};
