// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Reload.h"
#include "AIController.h"
#include "../../Characters/SpaceMarineCharacter.h"

UBTTask_Reload::UBTTask_Reload()
{
	NodeName = TEXT("Reload");
}

EBTNodeResult::Type UBTTask_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!AIPawn) { return EBTNodeResult::Failed; }
	AISpaceMarineCharacter = Cast<ASpaceMarineCharacter>(AIPawn);
	if (!AISpaceMarineCharacter) { return EBTNodeResult::Failed; }

	AISpaceMarineCharacter->ReloadAmmo();

	return EBTNodeResult::Succeeded;
}