// Fill out your copyright notice in the Description page of Project Settings.


#include "SMAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASMAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!BehaviorTree) { return; }
	
	RunBehaviorTree(BehaviorTree);
}
