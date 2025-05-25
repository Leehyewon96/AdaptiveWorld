// Copyright Epic Games, Inc. All Rights Reserved.

#include "AdaptiveWorldCharacter.h"
#include "AdaptiveWorldAnimInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

AAdaptiveWorldCharacter::AAdaptiveWorldCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAdaptiveWorldCharacter::BeginPlay()
{
	Super::BeginPlay();

	_AnimInstance = Cast<UAdaptiveWorldAnimInstance>(GetMesh()->GetAnimInstance());
	_HealthPoints = HealthPoints;
}

void AAdaptiveWorldCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

float AAdaptiveWorldCharacter::GetHealthPoints()
{
	return _HealthPoints;
}

bool AAdaptiveWorldCharacter::IsKilled()
{
	return (_HealthPoints <= 0.0f);
}

bool AAdaptiveWorldCharacter::CanAttack()
{
	return (_AttackCountingDown <= 0.0f && _AnimInstance->State == ECharacterState::Locomotion);
}

bool AAdaptiveWorldCharacter::IsAttacking()
{
	return (_AnimInstance->State == ECharacterState::Attack);
}

void AAdaptiveWorldCharacter::Attack()
{
	_AttackCountingDown = AttackInterval;

}

void AAdaptiveWorldCharacter::Hit(int damage)
{
	if (IsKilled())
	{
		return;
	}

	_HealthPoints -= damage;

	_AnimInstance->State = ECharacterState::Hit;
	if (IsKilled())
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void AAdaptiveWorldCharacter::DieProcess()
{
	PrimaryActorTick.bCanEverTick = false;
	Destroy();
	GEngine->ForceGarbageCollection(true);
}


