// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AdaptiveWorldAnimInstance.h"

// Sets default values
APlayerAvatar::APlayerAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	auto characterMovement = GetCharacterMovement();
	characterMovement->bOrientRotationToMovement = true;
	characterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	characterMovement->bConstrainToPlane = true;
	characterMovement->bSnapToPlaneAtStart = true;

	_springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_springArmComponent->SetupAttachment(RootComponent);
	_springArmComponent->SetUsingAbsoluteRotation(true);
	_springArmComponent->TargetArmLength = 800.0f;
	_springArmComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	_springArmComponent->bDoCollisionTest = false;

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_cameraComponent->SetupAttachment(_springArmComponent, USpringArmComponent::SocketName);
	_cameraComponent->bUsePawnControlRotation = false;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	
}

// Called when the game starts or when spawned
void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_AnimInstance->Speed = GetCharacterMovement()->Velocity.Size2D();

	if (_AttackCountingDown == AttackInterval)
	{
		_AnimInstance->State = ECharacterState::Attack;
	}

	if (_AttackCountingDown > 0.0f)
	{
		_AttackCountingDown -= DeltaTime;
	}

}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerAvatar::AttachWeapon(AWeapon* Weapon)
{
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
}

void APlayerAvatar::DropWeapon()
{
	TArray<AActor*> attachedActors;
	GetAttachedActors(attachedActors, true);
	for (int i = 0; i < attachedActors.Num(); ++i)
	{
		attachedActors[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		attachedActors[i]->SetActorRotation(FQuat::Identity);
		AWeapon* weapon = Cast<AWeapon>(attachedActors[i]);
		if (weapon != nullptr)
		{
			weapon->Holder = nullptr;
		}
	}
}

void APlayerAvatar::DieProcess()
{
	ENetMode netMode = GetNetMode();
	if (netMode == ENetMode::NM_ListenServer)
	{
		DropWeapon();
	}

	if ((netMode == ENetMode::NM_ListenServer || netMode == ENetMode::NM_Client) && IsLocallyControlled())
	{
		OnPlayerIsKilledDelegate.Broadcast();
	}

	Super::DieProcess();
}

void APlayerAvatar::Attack_RPC_Implementation()
{
	Attack_Broadcast_RPC();
}

