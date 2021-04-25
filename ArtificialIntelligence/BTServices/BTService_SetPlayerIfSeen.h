// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetPlayerIfSeen.generated.h"

class AAIController;
class ASpaceMarineCharacter;

/**
 * 
 */
UCLASS()
class W40BLOODHAVEN_API UBTService_SetPlayerIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
	AAIController* EnemyAIController;
	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY()
	APawn* AIPawn;
	UPROPERTY()
	ASpaceMarineCharacter* AISpaceMarineCharacter;

	float RangeToPlayer;
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UBTService_SetPlayerIfSeen();
};
