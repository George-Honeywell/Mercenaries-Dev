// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterHUD.h"
#include "Blueprint/UserWidget.h"


void AMainCharacterHUD::DrawHUD()
{
	Super::DrawHUD();

	if (CrosshairTexture != nullptr)
	{
		//Find the centre of the canvas
		FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		//Offset bu half of the texture's diemensions so that the centre of the textire aligns with the centre of the canvas
		FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

		//Draw the crosshair at the centre point
		FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}
}

