// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MERCENARIES_API AMainCharacterController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player HUD")
		TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player HUD")
		TSubclassOf<class UUserWidget> AmmoClass;	
};
