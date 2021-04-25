// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenGate.h"
#include "Engine/TriggerVolume.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UOpenGate::UOpenGate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenGate::BeginPlay()
{
	Super::BeginPlay();

	// SET VALUES TO OPEN DOOR
	InitialZ = GetOwner()->GetActorLocation().Z;
	CurrentZ = InitialZ;
	TargetZ = InitialZ + OpenHeight;

	// SET ACTOR THAT OPENS AS PLAYER IF NOT PICKED FROM THE WORLD
	if (!ActorThatOpens)
	{
		ActorThatOpens = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
}

// Called every frame
void UOpenGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!TriggerVolume || !ActorThatOpens || !OpenGateSound) { return; }

	if (TriggerVolume->IsOverlappingActor(ActorThatOpens))
	{
		if (!SoundPlayed)
		{
			UGameplayStatics::PlaySoundAtLocation(GetOwner(), OpenGateSound, GetOwner()->GetActorLocation());
			SoundPlayed = !SoundPlayed;
		}

		CurrentZ = FMath::Lerp(CurrentZ, TargetZ, DeltaTime * OpenSpeed);

		FVector GateLocation = GetOwner()->GetActorLocation();
		GateLocation.Z = CurrentZ;

		GetOwner()->SetActorLocation(GateLocation);
	}
}