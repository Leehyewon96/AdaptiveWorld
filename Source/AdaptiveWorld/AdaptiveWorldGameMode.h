// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Projectile.h"
#include "AdaptiveWorldGameMode.generated.h"

UCLASS(minimalapi)
class AAdaptiveWorldGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAdaptiveWorldGameMode();
	~AAdaptiveWorldGameMode();

	AProjectile* SpawnOrGetFireball(UClass* ProjectileClass);
	void RecycleFireball(AProjectile* projectile);

protected:
	TQueue<AProjectile*, EQueueMode::Spsc> _FireballPool;
};



