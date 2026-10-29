// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

class UCharacterStateComponent;

class AMyEnemy;

enum State
{

};

UCLASS()
class PROJECTSTEALTHEXIT_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
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
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Assassination", meta = (ClampMin = "0.0"))
	float AssassinationRange = 150.0f;
	UFUNCTION(BlueprintCallable, Category = "Assassination")
	bool CheckDistanceToEnemy();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assassination")
	AMyEnemy* Enemy = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Assassination")
	bool bIsAssassinating = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
