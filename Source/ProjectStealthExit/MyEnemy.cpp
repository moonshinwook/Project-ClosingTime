// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "CharacterStateComponent.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CharacterStateComponent = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("적 상태"));

}

// Called when the game starts or when spawned
void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("적 상태 : %d, %d"),
		CharacterStateComponent->CurrentLifeState,
		CharacterStateComponent->CurrentStealthState);
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

