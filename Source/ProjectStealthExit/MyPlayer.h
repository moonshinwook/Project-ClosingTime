
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterStateComponent.h"
#include "MyPlayer.generated.h"

class UCharacterStateComponent;

class AMyEnemy;

UCLASS()
class PROJECTSTEALTHEXIT_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()
	
public:
	AMyPlayer();
private:
	UPROPERTY()
	TObjectPtr<UCharacterStateComponent> CharacterStateComponent;
public:
	UFUNCTION(BlueprintCallable)
	bool BeginAssassionation();
	UFUNCTION(BlueprintCallable)
	bool SetAssassinationCollisionIgnored(bool Ignore);
	UFUNCTION(BlueprintCallable)
	void EndAssassionation();
	UFUNCTION(BlueprintPure)
	bool CanProcessActionInput();
public:
	bool CheckDistanceToEnemy();
	bool CheckAssassinationAngle();
	bool CheckAssassinationAngle(const AMyEnemy* TargetEnemy, bool& bOutAngleValid) const;
	bool CheckAssassinationPath();
	void UpdatePlayerState(AlertState EnemyAlertState);
	UCharacterStateComponent* GetCharacterStateComponent() const { return CharacterStateComponent.Get(); }
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Assassination", meta = (ClampMin = "0.0"))
	float AssassinationRange = 150.0f;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assassination")
	AMyEnemy* Enemy = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Assassination")
	bool bIsAssassinating = false;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
