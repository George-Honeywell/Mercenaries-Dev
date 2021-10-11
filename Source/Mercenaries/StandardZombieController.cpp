// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardZombieController.h"

#include "Kismet/GameplayStatics.h"

void AStandardZombieController::BeginPlay()
{
	Super::BeginPlay();
	mainCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AStandardZombieController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveToActor(mainCharacter);

	bool lineOfSight = LineOfSightTo(mainCharacter);

	if (lineOfSight)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, TEXT("[AI DEBUG] - In Sight"));
		SetFocus(mainCharacter);
		MoveToActor(mainCharacter);
	}
	else 
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, TEXT("[AI DEBUG] - Not in Sight"));
		StopMovement();
	}
}