// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "AdaptiveWorldCharacter.h"
#include "Enemy.generated.h"

UCLASS()
class ADAPTIVEWORLD_API AEnemy : public AAdaptiveWorldCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APawn* _chasedTarget = nullptr;

	//UClass* _WeaponClass;
	AWeapon* _Weapon;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DieProcess() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|Enemy")
	void Chase(APawn* targetPawn);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* PawnSensingComponent;
};
