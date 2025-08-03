// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Projectile.h"
#include "DefenseTower.generated.h"

UCLASS(Blueprintable)
class ADAPTIVEWORLD_API ADefenseTower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADefenseTower();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int HealthPoints = 100;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	int ShellDefense = 2;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float AttackRange = 15.0f;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	float ReloadInterval = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUserWidget* HealthBarWidget;

	UPROPERTY(EditAnywhere, Category = "Tower Params")
	bool IsBase = false;

	class APlayerAvatar* _Target = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Replicatedusing = OnHealthPointsChanged)
	int _HealthPoints;

	UFUNCTION()
	void OnHealthPointsChanged();

	float _ReloadCountingDown;

	class AAdaptiveWorldGameMode* _AdaptiveWorldGameMode;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower component", meta = (AllowPrivateAccess = "true"))
	USphereComponent* _SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tower Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* _MeshComponent;

	UClass* _FireballClass;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|Defense Tower", meta = (DisplayName = "GetHP"))
	int GetHealthPoints();

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|Defense Tower", meta = (DisplayName = "IsDestroyed"))
	bool IsDestroyed();

	UFUNCTION(BlueprintCallable, Category = "AdaptiveWorld|Defense Tower", meta = (DisplayName = "CanFire"))
	bool CanFire();
	void Fire();
	void Hit(int damage);
	bool IsKilled();

	FORCEINLINE USphereComponent* GetBoxComponent() const
	{
		return _SphereComponent;
	}
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const
	{
		return _MeshComponent;
	}

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OhterComponent,
		int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void OnMeshBeginOverlap(AActor* OtherActor);

protected:
	void DestroyProcess();
};
