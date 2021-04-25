// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "../../Characters/SpaceMarineCharacter.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AIEnemyPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!AIEnemyPawn) { return EBTNodeResult::Failed; }

	EnemySpaceMarineCharacter = Cast<ASpaceMarineCharacter>(AIEnemyPawn);
	if (!EnemySpaceMarineCharacter) { return EBTNodeResult::Failed; }

	EnemySpaceMarineCharacter->Shoot();

	return EBTNodeResult::Succeeded;
}