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
	float Strength = 50;

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
	virtual void DieProcess();

protected:
	virtual void BeginPlay() override;

	class UAdaptiveWorldAnimInstance* _AnimInstance;

	UPROPERTY(ReplicatedUsing = OnHealthPointsChanged)
	int _HealthPoints;

	float _AttackCountingDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserWidget* HealthBarWidget;

public:
	UFUNCTION(NetMulticast, Reliable)
	void Attack_Broadcast_RPC();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnHealthPointsChanged();

};

