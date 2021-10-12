// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

void AMainCharacterController::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
		//GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("Added to viewport!"));
	}

	UUserWidget* Ammo = CreateWidget(this, AmmoClass);
	if (Ammo != nullptr)
	{
		Ammo->AddToViewport();
	}
}

