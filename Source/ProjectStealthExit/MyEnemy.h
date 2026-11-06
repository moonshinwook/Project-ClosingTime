

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEnemy.generated.h"

class UCharacterStateComponent;
class AMyPlayer;

UCLASS()
class PROJECTSTEALTHEXIT_API AMyEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:
	
	AMyEnemy();
private:
	UPROPERTY()
	TObjectPtr<UCharacterStateComponent> CharacterStateComponent;
	UPROPERTY()
	TObjectPtr<AMyPlayer> Player;

	float ContinuousDetectionTime = 0.0f;
	bool CanSeePlayer() const;
protected:
	
	virtual void BeginPlay() override;

public:
	void UpdateEnemyState(float DeltaTime);
public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
