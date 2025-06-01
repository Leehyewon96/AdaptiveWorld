// Fill out your copyright notice in the Description page of Project Settings.


#include "AdaptiveWorldGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UAdaptiveWorldGameInstance::StartListenServer()
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, "TopDownMap", true, "?listen");
}

void UAdaptiveWorldGameInstance::JoinAsCient(FString IPAddress)
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, *IPAddress, true, "?join");
}

void UAdaptiveWorldGameInstance::Leaveame()
{
	auto world = GEngine->GetCurrentPlayWorld();
	UGameplayStatics::OpenLevel(world, "LobbyMap");
}
