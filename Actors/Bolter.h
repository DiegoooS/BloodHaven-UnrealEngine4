// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bolter.generated.h"

class USoundBase;
class ASpaceMarineCharacter;

UCLASS()
class W40BLOODHAVEN_API ABolter : public AActor
{
	GENERATED_BODY()

private:

	// COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* SceneComponent;

	// SOUNDS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"));
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundBase* EmptyMagazineSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundBase* ReloadSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundBase* TakeAmmo;

	// PARTICLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"));
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"));
	UParticleSystem* BulletHitFlash;

	// VARIABLES
	UPROPERTY()
	APawn* OwnerPawn;
	UPROPERTY();
	AController* OwnerController;
	UPROPERTY()
	ASpaceMarineCharacter* OwnerCharacterSpaceMarine;
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"));
	bool CanRapidFire = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"));
	float FireRate = 0.3f;

	FHitResult HitResult;
	FVector PlayerLocation;
	FRotator PlayerRotation;
	FVector PlayerShootRange;
	FCollisionQueryParams Params;

	int32 CurrentAmmoWithYou;
	int32 CurrentAmmoInMagazine;

	UPROPERTY(EditAnywhere, Category = "Statistics")
	float ReloadTime = 1.6f;
	UPROPERTY(EditAnywhere, Category="Statistics")
	float MaxDistance = 100.f;
	UPROPERTY(EditAnywhere, Category = "Statistics")
	float Damage = 10.f;
	UPROPERTY(EditAnywhere, Category = "Statistics")
	int32 MaxAmmoCarry = 360;
	UPROPERTY(EditAnywhere, Category = "Statistics")
	int32 MaxAmmoMagazine = 15;
	UPROPERTY(EditAnywhere, Category = "Statistics")
	float AccuracyMin = 0;
	UPROPERTY(EditAnywhere, Category = "Statistics")
	float AccuracyMax = 0;

	FTimerHandle ReloadTimer;

	// FUNCTIONS
	void SetPlayerController();
	void SetHitResult();
	void CalculateBulletsAmountToReload();
	void Fire();

public:	
	// Sets default values for this actor's properties
	ABolter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();
	void Reload();
	void StopFireRate();
	bool IsShooting();
	void ReplenishAmmo();

	int32 GetAmmoInMagazineValue();
	int32 GetAmmoWithYouValue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
