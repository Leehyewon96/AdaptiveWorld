// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AdaptiveWorldGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerChangedDelegate, float, Timer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameWinLoseDelegate, bool, Win);

UCLASS()
class ADAPTIVEWORLD_API AAdaptiveWorldGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, Category = "AdaptiveWorld")
	FOnTimerChangedDelegate OnTimerChangedDelegate;

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld")
	void OnTimerChanged();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnTimerChanged, Category = "AdaptiveWorld")
	float Timer = 0;
	

public:

	UPROPERTY(BlueprintAssignable, Category = "AdaptiveWorld")
	FOnGameWinLoseDelegate OnGameWinLoseDelegate;
	
	UFUNCTION(BlueprintCallable, Category = "AdativeWorld")
	void OnGameWin();


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnGameWin, Category = "AdaptiveWorld")
	bool GameWin;
};
