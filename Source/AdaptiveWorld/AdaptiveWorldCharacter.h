// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AdaptiveWorldCharacter.generated.h"

UCLASS(Blueprintable)
class AAdaptiveWorldCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	AAdaptiveWorldCharacter();

	UPROPERTY(EditAnywhere, Category = "AdaptiveWorld Character Param")
	int HealthPoints = 100;

	UPROPERTY(EditAnywhere, Category = "AdaptiveWorld Character Params")
	float Strength = 5;

	UPROPERTY(EditAnywhere, Category = "AdaptiveWorld Character Params")
	float Armor = 1;

	UPROPERTY(EditAnywhere, Category = "AdaptiveWorld Character Params")
	float AttackRange = 200.0f;

	UPROPERTY(EditAnywhere, Category = "AdaptiveWorld Character Params")
	float AttackInterval = 3.0f;

public:
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|Character", meta = (Displayname = "Get HP"))
	float GetHealthPoints();
	
	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|Character")
	bool IsKilled();

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|Character")
	bool CanAttack();
	bool IsAttacking();

	

	virtual void Attack();
	virtual void Hit(int damage);
	void DieProcess();

protected:
	virtual void BeginPlay() override;

	class UAdaptiveWorldAnimInstance* _AnimInstance;
	int _HealthPoints;
	float _AttackCountingDown;
};

