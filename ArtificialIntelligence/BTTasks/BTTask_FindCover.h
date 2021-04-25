// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindCover.generated.h"

class ACover;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API UBTTask_FindCover : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
	AAIController* OwnerAI;
	UPROPERTY()
	APawn* PawnAI;
	UPROPERTY()
	ACover* ClosestCover;

	float ClosestDistance;
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTTask_FindCover();
};
