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
#include "HealthBarWidget.h"
#include <Net/UnrealNetwork.h>

AAdaptiveWorldCharacter::AAdaptiveWorldCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AAdaptiveWorldCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto components = GetComponents();

	_AnimInstance = Cast<UAdaptiveWorldAnimInstance>(GetMesh()->GetAnimInstance());
	_HealthPoints = HealthPoints;
}

void AAdaptiveWorldCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAdaptiveWorldCharacter, _HealthPoints);
}

void AAdaptiveWorldCharacter::OnHealthPointsChanged()
{
	if (HealthBarWidget != nullptr)
	{
		float normalizedHealth = FMath::Clamp(
			(float)_HealthPoints / HealthPoints, 0.0f, 1.0f);
		auto healthBar = Cast<UHealthBarWidget>(HealthBarWidget);
		healthBar->HealthProgressBar->SetPercent(normalizedHealth);
	}

	if (_AnimInstance != nullptr)
	{
		_AnimInstance->State = ECharacterState::Hit;
	}

	if (IsKilled())
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void AAdaptiveWorldCharacter::Attack_Broadcast_RPC_Implementation()
{
	Attack();
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

	if (GetNetMode() == NM_ListenServer && HasAuthority())
	{
		_HealthPoints -= damage;
		OnHealthPointsChanged();
	}
}

void AAdaptiveWorldCharacter::DieProcess()
{
	PrimaryActorTick.bCanEverTick = false;
	Destroy();
	GEngine->ForceGarbageCollection(true);
}


