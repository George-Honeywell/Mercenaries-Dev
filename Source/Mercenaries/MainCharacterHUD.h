// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "MainCharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class MERCENARIES_API AMainCharacterHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	//Primary draw call for the HUD
	virtual void DrawHUD() override;

protected:
	//This will be Drawn at the centre of the screen
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrosshairTexture;
};
