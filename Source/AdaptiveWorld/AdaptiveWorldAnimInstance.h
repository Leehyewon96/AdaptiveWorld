// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AdaptiveWorldAnimInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Locomotion,
	Attack,
	Hit,
	Die
};

UCLASS()
class ADAPTIVEWORLD_API UAdaptiveWorldAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdaptiveWorldAnimInstance Params")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AdaptiveWorldAnimInstance Params")
	ECharacterState State;

	UFUNCTION(BlueprintCallable)
	void OnStateAnimationEnds();

};
