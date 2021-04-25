// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "Intro.generated.h"

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API AIntro : public ALevelSequenceActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
