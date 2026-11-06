

#include "MyEnemy.h"
#include "CharacterStateComponent.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"


AMyEnemy::AMyEnemy()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	CharacterStateComponent = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("적 상태"));

}


void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
}

bool AMyEnemy::CanSeePlayer() const
{
	if (!IsValid(Player))
	{
		return false;
	}

	bool bAngleValid = false;

	return !Player->CheckAssassinationAngle(this, bAngleValid) && bAngleValid;
}

void AMyEnemy::UpdateEnemyState(float DeltaTime)
{
	if (!IsValid(Player))
	{
		ContinuousDetectionTime = 0.0f;
		return;
	}

	UCharacterStateComponent* EnemyState = CharacterStateComponent.Get();
	UCharacterStateComponent* PlayerCharacterState = IsValid(Player) ? Player->GetCharacterStateComponent() : nullptr;
	
	if (!IsValid(EnemyState) || !IsValid(PlayerCharacterState)
		|| EnemyState->CurrentLifeState != LifeState::Alive
		|| PlayerCharacterState->CurrentLifeState != LifeState::Alive)
	{
		ContinuousDetectionTime = 0.0f;
		return;
	}

	if (CanSeePlayer())
	{
		if (ContinuousDetectionTime < 0.0f)
		{
			ContinuousDetectionTime = 0.0f;
		}
		ContinuousDetectionTime = FMath::Min(ContinuousDetectionTime + DeltaTime, 3.0f);

		if (EnemyState->CurrentAlertState == AlertState::Unaware)
		{
			EnemyState->CurrentAlertState = AlertState::Suspicious;
			UE_LOG(LogTemp, Log, TEXT("%s: Unaware -> Suspicious"), *GetName());
		}

		if (ContinuousDetectionTime >= 3.0f && EnemyState->CurrentAlertState == AlertState::Suspicious)
		{
			EnemyState->CurrentAlertState = AlertState::Alerted;
			UE_LOG(LogTemp, Log, TEXT("%s: Suspicious -> Alerted"), *GetName());
		}
	}

	else
	{
		if (ContinuousDetectionTime > 0.0f)
		{
			ContinuousDetectionTime = 0.0f;
		}
		ContinuousDetectionTime = FMath::Max(ContinuousDetectionTime - DeltaTime, -10.0f);

		if (ContinuousDetectionTime <= -10.0f
			&& EnemyState->CurrentAlertState != AlertState::Unaware)
		{
			EnemyState->CurrentAlertState = AlertState::Unaware;
			UE_LOG(LogTemp, Log, TEXT("%s: -> Unaware"), *GetName());
		}
		else if (ContinuousDetectionTime <= -5.0f
			&& EnemyState->CurrentAlertState == AlertState::Alerted)
		{
			EnemyState->CurrentAlertState = AlertState::Suspicious;
			UE_LOG(LogTemp, Log, TEXT("%s: Alerted -> Suspicious"), *GetName());
		}
	}
	Player->UpdatePlayerState(EnemyState->CurrentAlertState);
}

// Called every frame
void AMyEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateEnemyState(DeltaTime);
}

// Called to bind functionality to input
void AMyEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

