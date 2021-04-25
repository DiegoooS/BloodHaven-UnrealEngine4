// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SMPlayerController.generated.h"

class UUserWidget;
class AW40BloodHavenGameModeBase;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API ASMPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<UUserWidget> BloodOnScreenWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"));
	TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY()
	UUserWidget* HUD;
	UPROPERTY()
	UUserWidget* BloodOnScreen;
	UPROPERTY()
	UUserWidget* MainMenu;
	UPROPERTY()
	AW40BloodHavenGameModeBase* GameMode;
	UPROPERTY()
	APawn* PlayerPawn;

	FVector StartLocation;
	bool bPlayerPositionWasSet = false;

	void SetStartOfTheGame();
	void SetPlayerPositionAfterIntro();
	void OpenMainMenu();
	void CloseMainMenu();

public:
	ASMPlayerController();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
};
