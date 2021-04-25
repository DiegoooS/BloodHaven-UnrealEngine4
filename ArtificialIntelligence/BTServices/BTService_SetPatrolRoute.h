// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetPatrolRoute.generated.h"

class APatrolPoint;
class ASpaceMarineCharacter;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API UBTService_SetPatrolRoute : public UBTService
{
	GENERATED_BODY()

private:
	UPROPERTY()
	APatrolPoint* PatrolPointStart;
	UPROPERTY()
	APatrolPoint* PatrolPointEnd;
	UPROPERTY()
	ASpaceMarineCharacter* AISpaceMarineCharacter;
	UPROPERTY()
	AAIController* EnemyAIController;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UBTService_SetPatrolRoute();
};
