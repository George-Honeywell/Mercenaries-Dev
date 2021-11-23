// Fill out your copyright notice in the Description page of Project Settings.


#include "MercenariesGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

void AMercenariesGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//Display Debug message for five seconds.
	//The -1 "Key" value argument prevents the message from being updated or refreshed.
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("[DEBUG] - Game Started!"));

}