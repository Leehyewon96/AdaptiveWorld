// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerAvatarAnimInstance.h"

// Sets default values
APlayerAvatar::APlayerAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	UPlayerAvatarAnimInstance* animInst = Cast<UPlayerAvatarAnimInstance>(
		GetMesh()->GetAnimInstance());
	animInst->Speed = GetCharacterMovement()->Velocity.Size2D();

}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int APlayerAvatar::GetHealthPoints()
{
	return 0;
}

bool APlayerAvatar::IsKilled()
{
	return false;
}

bool APlayerAvatar::CanAttack()
{
	return false;
}

void APlayerAvatar::Attack()
{
}

void APlayerAvatar::Hit(int damage)
{
}

void APlayerAvatar::DieProcess()
{
}

