// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindCover.h"
#include "../../Actors/Cover.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_FindCover::UBTTask_FindCover()
{
	NodeName = TEXT("Find Cover");
}

EBTNodeResult::Type UBTTask_FindCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ClosestDistance = 2000.f;

	OwnerAI = OwnerComp.GetAIOwner();
	PawnAI = OwnerComp.GetAIOwner()->GetPawn();

	if (!OwnerAI || !PawnAI) { return EBTNodeResult::Failed; }

	for(ACover* Cover : TActorRange<ACover>(GetWorld()))
	{
		if (!Cover) { return EBTNodeResult::Failed; }
		float DistanceToCover = UKismetMathLibrary::Vector_Distance(PawnAI->GetActorLocation(), Cover->GetActorLocation());

		UE_LOG(LogTemp, Warning, TEXT("%f"), DistanceToCover);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Cover->GetName());

		if (ClosestDistance > DistanceToCover)
		{
			UE_LOG(LogTemp, Warning, TEXT("Changing"));
			ClosestCover = Cover;
			ClosestDistance = DistanceToCover;
		}
	}

	if (!ClosestCover) { return EBTNodeResult::Failed; }

	UE_LOG(LogTemp, Warning, TEXT("Closest: %s"), *ClosestCover->GetName());

	OwnerAI->GetBlackboardComponent()->SetValueAsVector(TEXT("CoverLocation"), ClosestCover->GetActorLocation());

	return EBTNodeResult::Succeeded;
}