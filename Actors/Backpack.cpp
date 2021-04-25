// Fill out your copyright notice in the Description page of Project Settings.


#include "Backpack.h"

// Sets default values
ABackpack::ABackpack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABackpack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABackpack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

