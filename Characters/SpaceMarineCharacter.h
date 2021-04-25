// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceMarineCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ABackpack;
class ABolter;
class APatrolPoint;
class USoundBase;
class AW40BloodHavenGameModeBase;

UCLASS()
class W40BLOODHAVEN_API ASpaceMarineCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	// COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* SpringArm;

	// ACTORS
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABackpack> BackpackClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABolter> WeaponSlot_0;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABolter> WeaponSlot_1;
	UPROPERTY()
	ABackpack* Backpack;
	UPROPERTY()
	ABolter* Bolter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol", meta = (AllowPrivateAccess = "true"))
	APatrolPoint* PatrolPointStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol", meta = (AllowPrivateAccess = "true"))
	APatrolPoint* PatrolPointEnd;
	UPROPERTY()
	AW40BloodHavenGameModeBase* GameMode;

	// SOUNDS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundBase* WeaponSwap;


	bool bDeadSoundPlayed = false;

	// EFFECTS
	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UMatineeCameraShake> ShootShake;

	// FUNCTIONS
	void MoveForward(float Value);
	void MoveRight(float Value);
	void GetWeapon_1();
	void GetWeapon_2();
	void SpawnWeaponsInTheWorld();
	void StopFire();
	void RegenerateHealth();
	void GainHealth();
	void DieAfterIntro();

	UFUNCTION()
	void SwapWeapon(ABolter* Weapon, FString& WeaponName);

	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics", meta = (AllowPrivateAccess = "true"));
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics", meta = (AllowPrivateAccess = "true"));
	float HealthRegenerationRate = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistics", meta = (AllowPrivateAccess = "true"));
	float TimeToRegenerateHealthAfterDamage = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Death Condition", meta = (AllowPrivateAccess = "true"));
	bool bDieAfterIntro = false;

	float Health;

	bool bIsReloading = false;
	bool bIsSwaping = false;

	FString WeaponName;

	TArray<ABolter*> Weapons;

	FTimerDelegate WeaponSwapDelegate;
	FTimerHandle WeaponSwapTimer;
	FTimerHandle RegenerateHealthRateTimer;
	FTimerHandle StartRegenerateHealthTimer;

public:
	// Sets default values for this character's properties
	ASpaceMarineCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();
	void ReloadAmmo();
	void ReplenishAmmoInWeapons();

	// Set Reload Bool Value
	void SetIsReloading(bool Reload);

	APatrolPoint* GetPatrolPointStart();
	APatrolPoint* GetPatrolPointEnd();

	UFUNCTION(BlueprintPure)
	int32 CurrentAmmoInMagazine();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure)
	bool IsDead();
	UFUNCTION(BlueprintPure)
	bool IsReloading();
	UFUNCTION(BlueprintPure)
	bool IsSwaping();
	UFUNCTION(BlueprintPure)
	float GetHealthPercentage();
	UFUNCTION(BlueprintPure)
	int32 CurrentAmmoWithYou();
	UFUNCTION(BlueprintPure)
	FString CurrentWeaponName();
};