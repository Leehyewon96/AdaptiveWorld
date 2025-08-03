// Fill out your copyright notice in the Description page of Project Settings.


#include "AdaptiveWorldGameState.h"
#include <Net/UnrealNetwork.h>

void AAdaptiveWorldGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAdaptiveWorldGameState, Timer);
}

void AAdaptiveWorldGameState::OnTimerChanged()
{
	OnTimerChangedDelegate.Broadcast(Timer);
}

void AAdaptiveWorldGameState::OnGameWin()
{
	GameWin = true;
	OnGameWinLoseDelegate.Broadcast(true);
}
