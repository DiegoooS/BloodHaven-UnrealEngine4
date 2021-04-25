// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

class ATriggerVolume;
class ASpaceMarineCharacter;

UCLASS()
class W40BLOODHAVEN_API AAmmoBox : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Volumes", meta = (AllowPrivateAccess = "true"))
	ATriggerVolume* TriggerVolume;
	UPROPERTY()
	APawn* PlayerPawn;
	UPROPERTY()
	ASpaceMarineCharacter* PlayerSpaceMarine;

	void TakeAmmo();

public:	
	// Sets default values for this actor's properties
	AAmmoBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
