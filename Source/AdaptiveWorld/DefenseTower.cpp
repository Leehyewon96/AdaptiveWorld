// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseTower.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerAvatar.h"
#include "Projectile.h"
#include "Weapon.h"
#include "HealthBarWidget.h"
#include "AdaptiveWorldGameMode.h"
#include "AdaptiveWorldGameState.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <Net/UnrealNetwork.h>

// Sets default values
ADefenseTower::ADefenseTower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(_SphereComponent);

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_MeshComponent->SetupAttachment(_SphereComponent);

	_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenseTower::OnBeginOverlap);
	_SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADefenseTower::OnEndOverlap);

	static ConstructorHelpers::FObjectFinder<UBlueprint> blueprint_finder(
		TEXT("Blueprint'/Game/TopDown/Blueprints/BP_Fireball.BP_Fireball'"));
	if (blueprint_finder.Object)
	{
		_FireballClass = (UClass*)blueprint_finder.Object->GeneratedClass;
	}
	
}

void ADefenseTower::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ADefenseTower, _HealthPoints);
}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	//_SphereComponent->SetSphereRadius(AttackRange);
	SetActorTickInterval(0.5f);

	_AdaptiveWorldGameMode = Cast<AAdaptiveWorldGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	_HealthPoints = HealthPoints;
	OnHealthPointsChanged();
}

void ADefenseTower::OnHealthPointsChanged()
{
	if (HealthBarWidget != nullptr)
	{
		float normalizedHealth = FMath::Clamp(
			(float)_HealthPoints / HealthPoints, 0.0f, 1.0f);
		auto healthBar = Cast<UHealthBarWidget>(HealthBarWidget);
		healthBar->HealthProgressBar->SetPercent(normalizedHealth);
	}

	if (IsKilled())
	{
		PrimaryActorTick.bCanEverTick = false;
	}
}

void ADefenseTower::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerAvatar* player = Cast<APlayerAvatar>(OtherActor);
	if (player)
	{
		_Target = player;
	}
}

void ADefenseTower::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OhterComponent, int32 OtherBodyIndex)
{
	APlayerAvatar* player = Cast<APlayerAvatar>(OtherActor);
	if (_Target != nullptr && player == _Target)
	{
		_Target = nullptr;
	}
}

void ADefenseTower::OnMeshBeginOverlap(AActor* OtherActor)
{
	AWeapon* weapon = Cast<AWeapon>(OtherActor);
	if (weapon == nullptr || weapon->Holder == nullptr)
	{
		return;
	}

	AAdaptiveWorldCharacter* character = Cast<AAdaptiveWorldCharacter>(weapon->Holder);
	if (character->IsA(APlayerAvatar::StaticClass()) &&
		character->IsAttacking() &&
		weapon->IsWithinAttackRange(character->AttackRange, this) &&
		CanBeDamaged())
	{
		Hit(character->Strength);
	}
}

void ADefenseTower::DestroyProcess()
{

}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_Target != nullptr && GetNetMode() != NM_Client)
	{
		Fire();
	}
}

int ADefenseTower::GetHealthPoints()
{
	return _HealthPoints;
}

bool ADefenseTower::IsDestroyed()
{
	return (_HealthPoints > 0.0f);
}

bool ADefenseTower::CanFire()
{
	return (_ReloadCountingDown <= 0.0f);
}

void ADefenseTower::Fire()
{
	auto fireball = _AdaptiveWorldGameMode->SpawnOrGetFireball(_FireballClass);

	FVector startLocation = GetActorLocation();
	startLocation.Z += 100.0f;
	FVector targetLocation = _Target->GetActorLocation();
	targetLocation.Z = startLocation.Z;
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(
		startLocation, targetLocation);
	fireball->SetActorLocation(startLocation);
	fireball->SetActorRotation(rotation);
}

void ADefenseTower::Hit(int damage)
{
	if (IsKilled())
	{
		return;
	}

	if (GetNetMode() == ENetMode::NM_ListenServer && HasAuthority())
	{
		_HealthPoints -= damage;
		OnHealthPointsChanged();

		if (_HealthPoints <= 0)
		{
			if (IsBase)
			{
				AAdaptiveWorldGameState* gameState = Cast<AAdaptiveWorldGameState>
					(UGameplayStatics::GetGameState(GetWorld()));
				gameState->OnGameWin();
			}
			else
			{
				Destroy();
			}
		}
	}
}

bool ADefenseTower::IsKilled()
{
	return (_HealthPoints <= 0.0f);
}

