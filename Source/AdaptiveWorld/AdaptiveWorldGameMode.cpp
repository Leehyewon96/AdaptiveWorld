// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdaptiveWorldGameMode.h"
#include "AdaptiveWorldPlayerController.h"
#include "AdaptiveWorldCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AdaptiveWorldGameState.h"

AAdaptiveWorldGameMode::AAdaptiveWorldGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAdaptiveWorldPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_PlayerAvatar"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	GameStateClass = AAdaptiveWorldGameState::StaticClass();
}

AAdaptiveWorldGameMode::~AAdaptiveWorldGameMode()
{
	AProjectile* fireball;
	while (!_FireballPool.IsEmpty() && _FireballPool.Dequeue(fireball))
	{
		fireball->Destroy();
	}

	_FireballPool.Empty();
}

AProjectile* AAdaptiveWorldGameMode::SpawnOrGetFireball(UClass* ProjectileClass)
{
	AProjectile* fireball = nullptr;
	if (_FireballPool.IsEmpty())
	{
		fireball = Cast<AProjectile>(GetWorld()->SpawnActor(ProjectileClass));
	}
	else
	{
		_FireballPool.Dequeue(fireball);
		fireball->Reset();
	}

	return fireball;
}

void AAdaptiveWorldGameMode::RecycleFireball(AProjectile* projectile)
{
	if (projectile == nullptr)
	{
		return;
	}

	projectile->SetActorHiddenInGame(true);
	projectile->SetActorEnableCollision(false);
	projectile->SetActorTickEnabled(false);

	_FireballPool.Enqueue(projectile);
}