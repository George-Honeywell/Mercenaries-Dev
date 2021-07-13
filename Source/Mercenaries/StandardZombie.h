// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainCharacter.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "GameFramework/DamageType.h"
#include "StandardZombie.generated.h"

UCLASS()
class MERCENARIES_API AStandardZombie : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStandardZombie();

	UFUNCTION()
		void Destroy();

	UFUNCTION()
		void DamageOnOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
		float maxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere)
		float health;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
