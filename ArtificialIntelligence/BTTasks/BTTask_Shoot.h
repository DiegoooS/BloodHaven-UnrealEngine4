// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Shoot.generated.h"

class ASpaceMarineCharacter;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
private:
	UPROPERTY()
	ASpaceMarineCharacter* EnemySpaceMarineCharacter;
	UPROPERTY()
	APawn* AIEnemyPawn;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
