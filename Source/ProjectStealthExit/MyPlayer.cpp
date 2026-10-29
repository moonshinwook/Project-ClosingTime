// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "MyEnemy.h"
#include "Engine/EngineTypes.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

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
	BeginAssassionation();

}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AMyPlayer::BeginAssassionation()
{
	SetAssassinationCollisionIgnored(true);
	if (bIsAssassinating == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("암살 중 상태라 차단"));
		return false;
	}

	if (!CheckDistanceToEnemy())
	{
		UE_LOG(LogTemp, Warning, TEXT("대상 무효 또는 거리 초과"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("암살 시작 통과"));
	bIsAssassinating = true;
	bUseControllerRotationYaw = false;

	return true;
}

bool AMyPlayer::SetAssassinationCollisionIgnored(bool Ignore)
{
	if (!IsValid(Enemy))
	{
		return false;
	}

	UCapsuleComponent* PlayerCapsule = GetCapsuleComponent();
	UCapsuleComponent* EnemyCapsule = Enemy->GetCapsuleComponent();

	if (!IsValid(PlayerCapsule) || !IsValid(EnemyCapsule))
	{
		return false;
	}

	PlayerCapsule->IgnoreActorWhenMoving(Enemy, Ignore);
	EnemyCapsule->IgnoreActorWhenMoving(this, Ignore);

	return true;
}

void AMyPlayer::EndAssassionation()
{
	bIsAssassinating = false;
	SetAssassinationCollisionIgnored(false);
	bUseControllerRotationYaw = true;
}

bool AMyPlayer::CanProcessActionInput()
{
	if (bIsAssassinating == true)
	{
		return false;
	}
	else
	{
		return true;
	}

}

bool AMyPlayer::CheckDistanceToEnemy()
{

	if (!IsValid(Enemy))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy가 유효하지 않습니다."));
		return false;
	}

	float DistanceToEnemy = FVector::Distance(GetActorLocation(), Enemy->GetActorLocation());

	UE_LOG(LogTemp, Warning, TEXT("Enemy: %s / Distance: %.1f / Range: %.1f"),
		*GetNameSafe(Enemy), DistanceToEnemy, AssassinationRange);

	return DistanceToEnemy <= AssassinationRange;

}

