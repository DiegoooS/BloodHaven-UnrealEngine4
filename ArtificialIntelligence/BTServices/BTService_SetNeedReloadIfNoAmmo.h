// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetNeedReloadIfNoAmmo.generated.h"

class ASpaceMarineCharacter;
class AAIController;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API UBTService_SetNeedReloadIfNoAmmo : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
private:
	AAIController* EnemyAIController;
	APawn* AIPawn;
	ASpaceMarineCharacter* AISpaceMarineCharacter;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UBTService_SetNeedReloadIfNoAmmo();
};
