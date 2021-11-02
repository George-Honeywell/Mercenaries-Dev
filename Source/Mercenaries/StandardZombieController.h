// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Perception/PawnSensingComponent.h"
#include "ZombieBasic.h"

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/Engine.h"
#include "StandardZombieController.generated.h"

/**
 * 
 */
UCLASS()
class MERCENARIES_API AStandardZombieController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	APawn* mainCharacter;

	UPROPERTY()
		AZombieBasic* zombieBasic;

	void OnSeePawn(APawn* OtherPawn);

protected:
	virtual void BeginPlay() override;
};
