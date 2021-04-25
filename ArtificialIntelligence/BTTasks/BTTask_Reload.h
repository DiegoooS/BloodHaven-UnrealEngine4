// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Reload.generated.h"

class ASpaceMarineCharacter;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API UBTTask_Reload : public UBTTaskNode
{
	GENERATED_BODY()

private:
	APawn* AIPawn;
	ASpaceMarineCharacter* AISpaceMarineCharacter;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UBTTask_Reload();
};
