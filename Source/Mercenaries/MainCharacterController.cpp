// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

void AMainCharacterController::BeginPlay()
{
	Super::BeginPlay();

	worldRef = GetWorld();
	mainCharacter = Cast<AMainCharacter>(worldRef->GetFirstPlayerController()->GetCharacter());

	UUserWidget* HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}

	UUserWidget* Ammo = CreateWidget(this, AmmoClass);
	if (Ammo != nullptr)
	{
		Ammo->AddToViewport();
	}
}

void AMainCharacterController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	UUserWidget* GameOver = CreateWidget(this, GameOverHUD);
	if (GameOver != nullptr)
	{
		GameOver->AddToViewport();
		UGameplayStatics::SetGamePaused(worldRef, true);
		bShowMouseCursor       = true;
		bEnableClickEvents     = true;
		bEnableMouseOverEvents = true;
	}
}

