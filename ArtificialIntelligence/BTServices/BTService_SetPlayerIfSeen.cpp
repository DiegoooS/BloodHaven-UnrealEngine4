// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SetPlayerIfSeen.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Characters/SpaceMarineCharacter.h"

UBTService_SetPlayerIfSeen::UBTService_SetPlayerIfSeen()
{
	NodeName = TEXT("Set Player If Seen");
}

void UBTService_SetPlayerIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	EnemyAIController = OwnerComp.GetAIOwner();
	if (!EnemyAIController) { return; }
	AIPawn = EnemyAIController->GetPawn();
	if (!AIPawn) { return; }
	AISpaceMarineCharacter = Cast<ASpaceMarineCharacter>(AIPawn);
	if (!AISpaceMarineCharacter) { return; }

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn) { return; }

	RangeToPlayer = Cast<AActor>(EnemyAIController)->GetDistanceTo(PlayerPawn);

	EnemyAIController->GetBlackboardComponent()->SetValueAsVector(TEXT("HomeLocation"), EnemyAIController->GetTargetLocation());

	if (EnemyAIController->LineOfSightTo(PlayerPawn) && RangeToPlayer <= 3200.f)
	{
		AISpaceMarineCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.f;

		EnemyAIController->GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
		EnemyAIController->GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetTargetLocation());
	}
	else
	{
		AISpaceMarineCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.f;

		EnemyAIController->GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}