// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStateComponent.generated.h"

enum class LifeState : uint8
{
	Alive,
	Dead
};

enum class StealthState : uint8
{
	Hidden,
	Detected
};

enum class AlertState : uint8
{
	Unaware,
	suspicious,
	Alerted
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )



class PROJECTSTEALTHEXIT_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	LifeState CurrentLifeState = LifeState::Alive;
	StealthState CurrentStealthState = StealthState::Hidden;
	AlertState CurrentAlertState = AlertState::Unaware;
};
