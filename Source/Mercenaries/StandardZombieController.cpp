// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardZombieController.h"

#include "Kismet/GameplayStatics.h"

AStandardZombieController::AStandardZombieController()
{
	//zombieBasic = CreateDefaultSubobject<AZombieBasic>(TEXT("zombieBasic"));
	//check(zombieBasic != nullptr);
}

void AStandardZombieController::BeginPlay()
{
	Super::BeginPlay();
	mainCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AStandardZombieController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	OnSeePawn(mainCharacter);
}

void AStandardZombieController::OnSeePawn(APawn* OtherPawn)
{
	bool lineOfSight = LineOfSightTo(mainCharacter);
	//zombieBasic->pawnSensor->SetPeripheralVisionAngle(20.0f);
	//float getPeripheralAngle = zombieBasic->pawnSensor->GetPeripheralVisionAngle();
	//UE_LOG(LogTemp, Warning, (TEXT("Peripheral Vision is: %f")), getPeripheralAngle);

	if (lineOfSight)
	{
		//FString message = TEXT("Saw Actor: %s" + OtherPawn->GetName());
		//GEngine->AddOnScreenDebugMessage(-1, 0.25f, FColor::Magenta, message);
		SetFocus(mainCharacter);
		MoveToActor(mainCharacter);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		//GEngine->AddOnScreenDebugMessage(-1, 0.25f, FColor::Magenta, TEXT("[AI DEBUG] - Not in Sight"));
		StopMovement();
	}
}