// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AdaptiveWorldAnimInstance.h"
#include "EnemyController.h"



// Sets default values
AEnemy::AEnemy()
{
	//PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));

	/*static ConstructorHelpers::FObjectFinder<UBlueprint> blueprint_finder(
		TEXT("Blueprint'/Game/TopDown/Blueprints/BP_Hammer.BP_Hammer'"));

	if (blueprint_finder.Object)
	{
		_WeaponClass = (UClass*)blueprint_finder.Object->GeneratedClass;
	}*/
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	_Weapon = Cast<AWeapon>(GetWorld()->SpawnActor(WeaponClass));
	if (_Weapon && GetMesh() && GetMesh()->DoesSocketExist("hand_r"))
	{
		_Weapon->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetIncludingScale,
			FName("hand_r"));
		_Weapon->Holder = this;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Attach failed: Weapon or Mesh or Socket is invalid"));
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//타겟 설정 갱신
	if (_chasedTarget != nullptr && _AnimInstance->State == ECharacterState::Locomotion)
	{
		auto enemyController = Cast<AEnemyController>(GetController());
		enemyController->MakeAttackDecision(_chasedTarget);
	}

	//_AnimInstance->Speed = GetCharacterMovement()->Velocity.Size2D();

	//공격관련 상태 갱신
	/*if (_AttackCountingDown == AttackInterval)
	{
		_AnimInstance->State = ECharacterState::Attack;
	}

	if (_AttackCountingDown > 0.0f)
	{
		_AttackCountingDown -= DeltaTime;
	}*/

	
}

void AEnemy::DieProcess()
{
	Super::DieProcess();
	_Weapon->Destroy();
}

void AEnemy::Chase(APawn* targetPawn)
{
	if (targetPawn != nullptr && _AnimInstance->State == ECharacterState::Locomotion)
	{
		auto enemyController = Cast<AEnemyController>(GetController());
		enemyController->MoveToActor(targetPawn, 90.0f);
	}
	_chasedTarget = targetPawn;

	/*auto animInst = GetMesh()->GetAnimInstance();
	auto enemyAnimInst = Cast<UAdaptiveWorldAnimInstance>(animInst);
	if (enemyAnimInst->State == ECharacterState::Locomotion)
	{
		auto enemyController = Cast<AEnemyController>(GetController());
		enemyController->MoveToActor(targetPawn, 90.0f);
	}
	_chasedTarget = targetPawn;*/
}