// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetPatrolRoute.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Characters/SpaceMarineCharacter.h"
#include "../../Actors/PatrolPoint.h"

UBTService_SetPatrolRoute::UBTService_SetPatrolRoute()
{
	NodeName = TEXT("Set Patrol Route");
}

void UBTService_SetPatrolRoute::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AISpaceMarineCharacter = Cast<ASpaceMarineCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	EnemyAIController = OwnerComp.GetAIOwner();

	if (!AISpaceMarineCharacter || !EnemyAIController) { return; }

	PatrolPointStart = AISpaceMarineCharacter->GetPatrolPointStart();
	PatrolPointEnd = AISpaceMarineCharacter->GetPatrolPointEnd();

	if (!PatrolPointStart || !PatrolPointEnd) { return; }

	EnemyAIController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLocationStart"), PatrolPointStart->GetActorLocation());
	EnemyAIController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLocationEnd"), PatrolPointEnd->GetActorLocation());
}