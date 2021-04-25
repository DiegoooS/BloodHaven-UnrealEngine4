// Copyright Epic Games, Inc. All Rights Reserved.


#include "W40BloodHavenGameModeBase.h"
#include "MovieSequences/Intro.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/SMPlayerController.h"

AW40BloodHavenGameModeBase::AW40BloodHavenGameModeBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AW40BloodHavenGameModeBase::BeginPlay()
{
	
}

void AW40BloodHavenGameModeBase::StartIntro()
{
	Intro = GetWorld()->SpawnActor<AIntro>(IntroClass);

	if (!Intro) { return; }

	bGameStart = true;

	Intro->SequencePlayer->Play();
}

void AW40BloodHavenGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateIntroFrame(DeltaSeconds);
}

void AW40BloodHavenGameModeBase::UpdateIntroFrame(float& DeltaSeconds)
{
	if (!Intro) { return; }

	Intro->SequencePlayer->Update(DeltaSeconds);
}

bool AW40BloodHavenGameModeBase::IntroHasEnded()
{
	if (!Intro) { return true; }

	return Intro->SequencePlayer->IsPlaying();
}

bool AW40BloodHavenGameModeBase::IsGameStarted()
{
	return bGameStart;
}