// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "WPN_Handgun.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MERCENARIES_API UWPN_Handgun : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWPN_Handgun();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UInputComponent* InputComponent = nullptr;
	float Range = 10000.0f;

	//Gun Attributes
	UPROPERTY(EditAnywhere, Category = "Handgun Stats")
	float hgPower = 10;

	UPROPERTY(EditAnywhere, Category = "Handgun Stats")
	int hgCapacity = 10;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Shoot();

		
};