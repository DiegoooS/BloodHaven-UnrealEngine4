// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetNeedReloadIfNoAmmo.h"
#include "AIController.h"
#include "../../Characters/SpaceMarineCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SetNeedReloadIfNoAmmo::UBTService_SetNeedReloadIfNoAmmo()
{
	NodeName = TEXT("Set Need Reload If No Ammo");
}

void UBTService_SetNeedReloadIfNoAmmo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	EnemyAIController = OwnerComp.GetAIOwner();
	if (!EnemyAIController) { return; }
	AIPawn = EnemyAIController->GetPawn();
	if (!AIPawn) { return; }
	AISpaceMarineCharacter = Cast<ASpaceMarineCharacter>(AIPawn);
	if (!AISpaceMarineCharacter) { return; }

	if (AISpaceMarineCharacter->CurrentAmmoInMagazine() <= 0)
	{
		EnemyAIController->GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		EnemyAIController->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}