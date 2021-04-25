// Fill out your copyright notice in the Description page of Project Settings.


#include "Bolter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "../Characters/SpaceMarineCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

// Sets default values
ABolter::ABolter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABolter::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmoWithYou = FMath::DivideAndRoundUp(MaxAmmoCarry, 2);
	CurrentAmmoInMagazine = MaxAmmoMagazine;
	CurrentAmmoWithYou -= CurrentAmmoInMagazine;
}

// Called every frame
void ABolter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABolter::PullTrigger()
{
	if (CanRapidFire)
	{
		GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ABolter::Fire, FireRate, true, 0.f);
	}
	else
	{
		Fire();
	}
}

void ABolter::Fire()
{
	if (CurrentAmmoInMagazine <= 0)
	{
		UGameplayStatics::PlaySoundAtLocation(SkeletalMesh, EmptyMagazineSound, this->GetActorLocation(), this->GetActorRotation());
		return;
	}

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::PlaySoundAtLocation(SkeletalMesh, FireSound, this->GetActorLocation(), this->GetActorRotation());

	--CurrentAmmoInMagazine;

	SetPlayerController();
	if (!OwnerController) { return; }

	SetHitResult();

	if (HitResult.IsValidBlockingHit())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletHitFlash, HitResult.Location, PlayerRotation);

		AActor* HittedActor = HitResult.GetActor();

		if (HittedActor)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, PlayerRotation.Vector(), nullptr);

			float AmountOfDamage = HittedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

void ABolter::StopFireRate()
{
	if (!GetWorldTimerManager().IsTimerActive(FireRateTimerHandle)) { return; }

	GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
}

bool ABolter::IsShooting()
{
	return GetWorldTimerManager().IsTimerActive(FireRateTimerHandle);
}

void ABolter::Reload()
{
	OwnerCharacterSpaceMarine = Cast<ASpaceMarineCharacter>(GetOwner());

	if (CurrentAmmoWithYou > 0 && CurrentAmmoInMagazine != MaxAmmoMagazine && !IsShooting())
	{
		if (!OwnerCharacterSpaceMarine) { return; }

		OwnerCharacterSpaceMarine->SetIsReloading(true);
		OwnerCharacterSpaceMarine->GetCharacterMovement()->MaxWalkSpeed = 300.f;

		UGameplayStatics::PlaySoundAtLocation(SkeletalMesh, ReloadSound, this->GetActorLocation(), this->GetActorRotation());
		GetWorldTimerManager().SetTimer(ReloadTimer, this, &ABolter::CalculateBulletsAmountToReload, ReloadTime);
	}
}

void ABolter::CalculateBulletsAmountToReload()
{
	OwnerCharacterSpaceMarine->SetIsReloading(false);
	OwnerCharacterSpaceMarine->GetCharacterMovement()->MaxWalkSpeed = 600.f;

	int32 AmmoToReload = MaxAmmoMagazine - CurrentAmmoInMagazine;

	if (CurrentAmmoWithYou < AmmoToReload)
	{
		CurrentAmmoInMagazine += CurrentAmmoWithYou;
		CurrentAmmoWithYou = 0;
	}
	else
	{
		CurrentAmmoInMagazine += AmmoToReload;
		CurrentAmmoWithYou -= AmmoToReload;

		if (CurrentAmmoWithYou < 0)
		{
			CurrentAmmoWithYou = 0;
		}
	}
}

void ABolter::SetPlayerController()
{
	OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) { return; }
	OwnerController = OwnerPawn->GetController();
}

void ABolter::SetHitResult()
{
	OwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	PlayerShootRange = PlayerLocation + PlayerRotation.Vector() * MaxDistance;

	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActor(this);

	PlayerShootRange.X += FMath::RandRange(AccuracyMin, AccuracyMax);
	PlayerShootRange.Y += FMath::RandRange(AccuracyMin, AccuracyMax);
	PlayerShootRange.Z += FMath::RandRange(AccuracyMin, AccuracyMax);

	GetWorld()->LineTraceSingleByChannel(HitResult, PlayerLocation, PlayerShootRange, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

int32 ABolter::GetAmmoInMagazineValue()
{
	return CurrentAmmoInMagazine;
}

int32 ABolter::GetAmmoWithYouValue()
{
	return CurrentAmmoWithYou;
}

void ABolter::ReplenishAmmo()
{
	if (CurrentAmmoWithYou < MaxAmmoCarry)
	{
		UGameplayStatics::PlaySoundAtLocation(SkeletalMesh, TakeAmmo, this->GetActorLocation(), this->GetActorRotation());

		CurrentAmmoWithYou = MaxAmmoCarry;
	}
}