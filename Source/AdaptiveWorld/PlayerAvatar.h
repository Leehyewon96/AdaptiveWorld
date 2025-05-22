// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerAvatar.generated.h"

UCLASS(Blueprintable)
class ADAPTIVEWORLD_API APlayerAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAvatar();

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	int HealthPoints = 500;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float Strength = 10;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float Armer = 3;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float AttackRange = 6.0f;

	UPROPERTY(EditAnywhere, Category = "PlayerAvatar Params")
	float AttackInterval = 1.2f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int _HealthPoints;
	float _AttackCountingDown;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _cameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|PlayerCharacter", meta = (DisplayName = "GetHP"))
	int GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|PlayerCharacter", meta = (DisplayName = "GetHP"))
	bool IsKilled();

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|PlayerCharacter", meta = (DisplayName = "GetHP"))
	bool CanAttack();

	void Attack();
	void Hit(int damage);

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const
	{
		return _springArmComponent;
	}

	FORCEINLINE UCameraComponent* GetCameraComponent() const
	{
		return _cameraComponent;
	}

protected:
	void DieProcess();
};
