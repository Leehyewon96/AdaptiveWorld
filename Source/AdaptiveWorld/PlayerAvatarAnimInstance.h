// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAvatarAnimInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Locomotion,
	Attack,
	Hit,
	Die
};

UCLASS()
class ADAPTIVEWORLD_API UPlayerAvatarAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttackking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPlayerState State;

public:
	UFUNCTION(BlueprintCallable)
	void OnStateAnimationEnds();
};
