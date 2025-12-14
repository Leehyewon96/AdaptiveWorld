// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "PlayerAvatar.h"
#include "DefenseTower.h"
#include "AdaptiveWorldCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("Static Mesh"));
	SetRootComponent(_StaticMesh);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBeginOverlap);
}

void AWeapon::OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	auto character = Cast<ACharacter>(OtherActor);
	if (character == nullptr)
	{
		return;
	}

	if (Holder == nullptr)
	{
		auto playerAvatar = Cast<APlayerAvatar>(character);
		if (playerAvatar != nullptr)
		{
			Holder = character;
			TArray<AActor*> attachedActors;
			OtherActor->GetAttachedActors(attachedActors, true);

			//플레이어가 기존에 들고 있던 무기 장착 해제
			for (int i = 0; i < attachedActors.Num(); ++i)
			{
				attachedActors[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				attachedActors[i]->SetActorRotation(FQuat::Identity);
				AWeapon* weapon = Cast<AWeapon>(attachedActors[i]);
				weapon->Holder = nullptr;
			}

			AttachToComponent(Holder->GetMesh(),
				FAttachmentTransformRules::SnapToTargetIncludingScale,
				FName("hand_r"));
		}
	}
	else
	{
		// 공격자(Holder)와 피해자(OtherActor)를 가져옴
		auto Attacker = Cast<AAdaptiveWorldCharacter>(Holder);
		auto Victim = Cast<AAdaptiveWorldCharacter>(OtherActor);

		// 피해자가 캐릭터이고, 공격자가 아니며(자해 방지), 공격자가 공격 모션 중일 때만
		if (Attacker && Victim && Attacker != Victim)
		{
			if (Attacker->IsAttacking())
			{
				// 피해자에게 데미지 적용
				Victim->Hit(Strength);
			}
		}
	}
}

bool AWeapon::IsWithinAttackRange(float AttackRange, AActor* Target)
{
	float distance = FVector::Distance(Target->GetActorLocation(), GetActorLocation());
	return (AttackRange <= 0.0f || distance <= AttackRange);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Holder == nullptr)
	{
		FQuat rotQuat = FQuat(FRotator(0, 300.0f * DeltaTime, 0));
		AddActorLocalRotation(rotQuat);
	}
}

