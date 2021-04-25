// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "W40BloodHavenGameModeBase.generated.h"

class AIntro;
class ULevelSequencePlayer;
class ASMPlayerController;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API AW40BloodHavenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly);
	TSubclassOf<AIntro> IntroClass;

	UPROPERTY()
	AIntro* Intro;

	UPROPERTY()
	ULevelSequencePlayer* IntroPlayer;

	bool bGameStart = false;

	void UpdateIntroFrame(float& DeltaSeconds);

public:
	AW40BloodHavenGameModeBase();

	virtual void Tick(float DeltaSeconds) override;

	bool IntroHasEnded();

	UFUNCTION(BlueprintCallable)
	void StartIntro();

	bool IsGameStarted();

protected:
	virtual void BeginPlay() override;
};
