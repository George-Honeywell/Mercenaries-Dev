// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "Handgun.generated.h"

UCLASS()
class MERCENARIES_API AHandgun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandgun();

	UFUNCTION()
		void Shoot();
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int currentAmmo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int ammoReserve;

	UFUNCTION()
		bool bCanShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		float power = 25.0f;

	UPROPERTY(EditAnywhere)
		int maxCapacity = 10;

	UPROPERTY(EditAnywhere)
		float weaponRange = 10000.0f;

	UFUNCTION()
		void Reload();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
