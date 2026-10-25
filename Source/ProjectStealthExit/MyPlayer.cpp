// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "MyEnemy.h"
#include "Engine/EngineTypes.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
}



// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	Enemy = Cast<AMyEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyEnemy::StaticClass()));
	

}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDistanceToEnemy();
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AMyPlayer::CheckDistanceToEnemy()
{

	if (!IsValid(Enemy))
	{
		printf("Enemy가 유효하지 않습니다.");
		return false;
	}

	float DistanceToEnemy = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());

	return DistanceToEnemy <= AssassinationRange;

}
