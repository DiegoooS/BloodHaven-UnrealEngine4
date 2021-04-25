// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SMAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API ASMAIController : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

protected:
	virtual void BeginPlay() override;
};
