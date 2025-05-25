// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "PlayerAvatar.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(_MeshComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	_LifeCountingDown = Lifespan;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_LifeCountingDown > 0.0f)
	{
		//이동
		FVector currentLocation = GetActorLocation();
		FVector val = GetActorRotation().RotateVector(FVector::ForwardVector) * Speed * DeltaTime;
		FVector nextLocation = currentLocation + val;
		SetActorLocation(nextLocation);

		//충돌 감지
		FHitResult hitResult;
		FCollisionObjectQueryParams objCollisionQueryParams;
		objCollisionQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

		if (GetWorld()->LineTraceSingleByObjectType(hitResult,
			currentLocation,
			nextLocation,
			objCollisionQueryParams))
		{
			auto playerAvatar = Cast<APlayerAvatar>(hitResult.GetActor());
			if (playerAvatar != nullptr)
			{
				playerAvatar->Hit(Damage);
				PrimaryActorTick.bCanEverTick = false;
				Destroy();
			}
		}


		_LifeCountingDown -= DeltaTime;
	}
	else
	{
		PrimaryActorTick.bCanEverTick = false;
		Destroy();
	}
}

