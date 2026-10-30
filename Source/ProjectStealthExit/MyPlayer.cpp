// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "MyEnemy.h"
#include "Engine/EngineTypes.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "CharacterStateComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	CharacterStateComponent = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("플레이어 상태"));
	
}





// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	Enemy = Cast<AMyEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyEnemy::StaticClass()));
	BeginAssassionation();
	UE_LOG(LogTemp, Log, TEXT("플레이어 상태 : %d, %d"), 
		CharacterStateComponent->CurrentLifeState, 
		CharacterStateComponent->CurrentStealthState);

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
	LifeState* PlayerLifeState;
	PlayerLifeState = &CharacterStateComponent->CurrentLifeState;
	StealthState* PlayerStealthState;
	PlayerStealthState = &CharacterStateComponent->CurrentStealthState;

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

	if (!CheckAssassinationAngle())
	{
		UE_LOG(LogTemp, Warning, TEXT("암살 각도 조건 불충족"));
		return false;
	}

	if(*PlayerLifeState == LifeState::Dead || *PlayerStealthState == StealthState::Detected)
	{
		UE_LOG(LogTemp, Warning, TEXT("플레이어 상태 불가"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("암살 시작 통과"));
	bIsAssassinating = true;
	SetAssassinationCollisionIgnored(true);
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

bool AMyPlayer::CheckAssassinationAngle()
{
	if (!IsValid(Enemy))
	{
		return false;
	}

	FVector DirectionToPlayer = GetActorLocation() - Enemy->GetActorLocation();
	DirectionToPlayer.Z = 0.0f;

	FVector EnemyForward = Enemy->GetActorForwardVector();
	EnemyForward.Z = 0.0f;

	if (!DirectionToPlayer.Normalize() || !EnemyForward.Normalize())
	{
		return false;
	}

	float Dot = FVector::DotProduct(EnemyForward, DirectionToPlayer);
	float FrontThreshold = FMath::Cos(FMath::DegreesToRadians(70.0f));

	return Dot < FrontThreshold;
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

