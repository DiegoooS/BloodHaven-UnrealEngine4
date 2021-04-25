// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "../W40BloodHavenGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASMPlayerController::ASMPlayerController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = GetWorld()->GetAuthGameMode<AW40BloodHavenGameModeBase>();

	HUD = CreateWidget(this, HUDWidgetClass);
	BloodOnScreen = CreateWidget(this, BloodOnScreenWidgetClass);

	OpenMainMenu();
}

void ASMPlayerController::OpenMainMenu()
{
	MainMenu = CreateWidget(this, MainMenuClass);

	if (!MainMenu) { return; }

	MainMenu->AddToViewport();
	this->SetShowMouseCursor(true);
}

void ASMPlayerController::CloseMainMenu()
{
	this->SetShowMouseCursor(false);

	if (!MainMenu) { return; }

	MainMenu->RemoveFromViewport();
}

void ASMPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetStartOfTheGame();
}

void ASMPlayerController::SetStartOfTheGame()
{
	if (!GameMode) { return; }

	if (GameMode->IsGameStarted())
	{
		CloseMainMenu();
	}

	if (!HUD || !BloodOnScreen || GameMode->IntroHasEnded()) { return; }

	if (!HUD->IsInViewport() || !BloodOnScreen->IsInViewport())
	{
		HUD->AddToViewport();
		BloodOnScreen->AddToViewport();
	}

	if (GameMode->IntroHasEnded() || !bPlayerPositionWasSet)
	{
		SetPlayerPositionAfterIntro();
	}
}

void ASMPlayerController::SetPlayerPositionAfterIntro()
{
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn) { return; }

	PlayerPawn->SetActorLocation(FVector(-8399.000000, -12510.000000, 315.281616));

	bPlayerPositionWasSet = true;
}