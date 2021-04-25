// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMarineCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "W40BloodHaven/Actors/Backpack.h"
#include "W40BloodHaven/Actors/Bolter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../W40BloodHavenGameModeBase.h"

// Sets default values
ASpaceMarineCharacter::ASpaceMarineCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ASpaceMarineCharacter::BeginPlay()
{
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<AW40BloodHavenGameModeBase>();

	Health = MaxHealth;

	SpawnWeaponsInTheWorld();
	GetWeapon_1();
	
	// Attach Backpack and bolter in the world
	Backpack = GetWorld()->SpawnActor<ABackpack>(BackpackClass);

	if (!Backpack) { return; }

	Backpack->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("BackpackSocket"));
	Backpack->SetOwner(this);
}

void ASpaceMarineCharacter::SpawnWeaponsInTheWorld()
{
	Weapons.Add(GetWorld()->SpawnActor<ABolter>(WeaponSlot_0));
	Weapons.Add(GetWorld()->SpawnActor<ABolter>(WeaponSlot_1));

	Weapons[0]->SetActorHiddenInGame(true);
	Weapons[1]->SetActorHiddenInGame(true);
}

bool ASpaceMarineCharacter::IsDead()
{
	return Health <= 0;
}

bool ASpaceMarineCharacter::IsReloading()
{
	return bIsReloading;
}

bool ASpaceMarineCharacter::IsSwaping()
{
	return bIsSwaping;
}

void ASpaceMarineCharacter::SetIsReloading(bool Reload)
{
	bIsReloading = Reload;
}

float ASpaceMarineCharacter::GetHealthPercentage()
{
	return Health / MaxHealth;
}

int32 ASpaceMarineCharacter::CurrentAmmoInMagazine()
{
	if (!Bolter) { return 0; }

	return Bolter->GetAmmoInMagazineValue();
}

int32 ASpaceMarineCharacter::CurrentAmmoWithYou()
{
	if (!Bolter) { return 0; }

	return Bolter->GetAmmoWithYouValue();
}

FString ASpaceMarineCharacter::CurrentWeaponName()
{
	return WeaponName;
}

// Called every frame
void ASpaceMarineCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DieAfterIntro();
}

void ASpaceMarineCharacter::DieAfterIntro()
{
	if (bDieAfterIntro && !GameMode->IntroHasEnded())
	{
		this->Destroy();
		Backpack->Destroy();
		Weapons[0]->Destroy();
	}
}

// Called to bind functionality to input
void ASpaceMarineCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASpaceMarineCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASpaceMarineCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &ASpaceMarineCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &ASpaceMarineCharacter::StopFire);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ASpaceMarineCharacter::ReloadAmmo);
	PlayerInputComponent->BindAction(TEXT("GetWeapon_1"), IE_Pressed, this, &ASpaceMarineCharacter::GetWeapon_1);
	PlayerInputComponent->BindAction(TEXT("GetWeapon_2"), IE_Pressed, this, &ASpaceMarineCharacter::GetWeapon_2);
}

void ASpaceMarineCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASpaceMarineCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASpaceMarineCharacter::GetWeapon_1()
{
	if (!Weapons[0]->IsHidden() || IsReloading()) { return; }

	if (Bolter != nullptr)
	{
		if (Bolter->IsShooting()) { return; }
	}

	FString WName = TEXT("Bolter");
	Weapons[1]->SetActorHiddenInGame(true);
	Weapons[0]->SetActorHiddenInGame(false);
	bIsSwaping = true;

	UGameplayStatics::PlaySoundAtLocation(this, WeaponSwap, this->GetTargetLocation());

	WeaponSwapDelegate.BindUFunction(this, TEXT("SwapWeapon"), Weapons[0], WName);
	GetWorldTimerManager().SetTimer(WeaponSwapTimer, WeaponSwapDelegate, 0.203f, false);
}

void ASpaceMarineCharacter::GetWeapon_2()
{
	if (!Weapons[1]->IsHidden() || IsReloading()) { return; }

	if (Bolter != nullptr)
	{
		if (Bolter->IsShooting()) { return; }
	}

	FString WName = TEXT("Chapter Bolter");
	Weapons[0]->SetActorHiddenInGame(true);
	Weapons[1]->SetActorHiddenInGame(false);
	bIsSwaping = true;

	UGameplayStatics::PlaySoundAtLocation(this, WeaponSwap, this->GetTargetLocation());

	WeaponSwapDelegate.BindUFunction(this, TEXT("SwapWeapon"), Weapons[1], WName);
	GetWorldTimerManager().SetTimer(WeaponSwapTimer, WeaponSwapDelegate, 0.203f, false);
}

void ASpaceMarineCharacter::SwapWeapon(ABolter* Weapon, FString& Name)
{
	bIsSwaping = false;

	Bolter = Weapon;

	if (!Bolter) { return; }

	WeaponName = Name;

	Bolter->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("BolterSocket"));
	Bolter->SetOwner(this);
}

void ASpaceMarineCharacter::Shoot()
{
	if (!Bolter || IsReloading() || IsSwaping() || GameMode->IntroHasEnded()) { return; }

	Bolter->PullTrigger();


	if (Bolter->GetAmmoInMagazineValue() > 0 )
	{
		// Play Camera Shake
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(ShootShake);
	}
}

void ASpaceMarineCharacter::StopFire()
{
	if (!Bolter) { return; }

	Bolter->StopFireRate();
}

void ASpaceMarineCharacter::ReloadAmmo()
{
	if (!Bolter || IsReloading() || IsSwaping()) { return; }

	Bolter->Reload();
}

float ASpaceMarineCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (GetWorldTimerManager().IsTimerActive(RegenerateHealthRateTimer))
	{
		GetWorldTimerManager().ClearTimer(RegenerateHealthRateTimer);
	}
	if (GetWorldTimerManager().IsTimerActive(StartRegenerateHealthTimer))
	{
		GetWorldTimerManager().ClearTimer(StartRegenerateHealthTimer);
	}

	GetWorldTimerManager().SetTimer(StartRegenerateHealthTimer, this, &ASpaceMarineCharacter::RegenerateHealth, TimeToRegenerateHealthAfterDamage, false);

	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Health > 0)
	{
		Health -= DamageApplied;
	}

	if (IsDead())
	{
		if (Bolter != nullptr) 
		{
			Bolter->StopFireRate(); 
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (!bDeadSoundPlayed)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, this->GetTargetLocation());

			bDeadSoundPlayed = !bDeadSoundPlayed;
		}
	}

	return DamageApplied;
}

void ASpaceMarineCharacter::RegenerateHealth()
{
	if (Health < MaxHealth && !IsDead())
	{
		GetWorldTimerManager().SetTimer(RegenerateHealthRateTimer, this, &ASpaceMarineCharacter::GainHealth, HealthRegenerationRate, true, 0.f);
	}
}

void ASpaceMarineCharacter::GainHealth()
{
	if (Health >= MaxHealth || IsDead())
	{
		GetWorldTimerManager().ClearTimer(RegenerateHealthRateTimer);
	}
	else
	{
		Health += 1;
	}
}

APatrolPoint* ASpaceMarineCharacter::GetPatrolPointStart()
{
	if (!PatrolPointStart) { return nullptr; }

	return PatrolPointStart;
}

APatrolPoint* ASpaceMarineCharacter::GetPatrolPointEnd()
{
	if (!PatrolPointEnd) { return nullptr; }

	return PatrolPointEnd;
}

void ASpaceMarineCharacter::ReplenishAmmoInWeapons()
{
	for (ABolter* Weapon : Weapons)
	{
		Weapon->ReplenishAmmo();
	}
}