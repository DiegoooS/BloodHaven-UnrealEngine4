// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"
#include "../Characters/SpaceMarineCharacter.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAmmoBox::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerSpaceMarine = Cast<ASpaceMarineCharacter>(PlayerPawn);
}

// Called every frame
void AAmmoBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TakeAmmo();
}

void AAmmoBox::TakeAmmo()
{
	if (!PlayerPawn || !TriggerVolume || !PlayerSpaceMarine) { return; }

	if (TriggerVolume->IsOverlappingActor(PlayerPawn))
	{
		PlayerSpaceMarine->ReplenishAmmoInWeapons();
	}
}