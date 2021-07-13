// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MercenariesGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MERCENARIES_API AMercenariesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	//Function declaration allows us to override StartPlay so we can print a log message when game begins.
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<UUserWidget> WidgetClass;
	
};
