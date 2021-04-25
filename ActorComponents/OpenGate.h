// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenGate.generated.h"

class ATriggerVolume;
class USoundBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class W40BLOODHAVEN_API UOpenGate : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Volumes", meta = (AllowPrivateAccess = "true"))
	ATriggerVolume* TriggerVolume;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Volumes", meta = (AllowPrivateAccess = "true"))
	APawn* ActorThatOpens;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", meta = (AllowPrivateAccess = "true"))
	USoundBase* OpenGateSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Proparties", meta = (AllowPrivateAccess = "true"))
	float OpenHeight = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Proparties", meta = (AllowPrivateAccess = "true"))
	float OpenSpeed = 2.f;

	float InitialZ;
	float CurrentZ;
	float TargetZ;

	bool SoundPlayed = false;

public:	
	// Sets default values for this component's properties
	UOpenGate();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
