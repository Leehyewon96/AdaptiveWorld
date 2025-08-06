// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AdaptiveWorldCharacter.h"
#include "Weapon.h"
#include "PlayerAvatar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerIsKilledDelegate);

UCLASS(Blueprintable)
class ADAPTIVEWORLD_API APlayerAvatar : public AAdaptiveWorldCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAvatar();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|PlayerAvatar")
	void AttachWeapon(AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|PlayerAvatar")
	void DropWeapon();

	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const
	{
		return _springArmComponent;
	}

	FORCEINLINE UCameraComponent* GetCameraComponent() const
	{
		return _cameraComponent;
	}
	
	UFUNCTION(Server, Reliable)
	void Attack_RPC();

	UPROPERTY(BlueprintAssignable, Category = "AdaptiveWorld|PlayerAvatar")
	FOnPlayerIsKilledDelegate OnPlayerIsKilledDelegate;

	void DieProcess() override;
};
