// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "Engine/Engine.h"
#include "GameFramework/DamageType.h"
#include "ZombieBasic.generated.h"

UCLASS()
class MERCENARIES_API AZombieBasic : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieBasic();

	//Components
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* staticMesh;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* boxCollider;

	UPROPERTY(VisibleAnywhere)
		UPawnSensingComponent* pawnSensor;

	//UPROPERTY(VisibleAnywhere)
		
		


	UFUNCTION()
		void Destroy();

	UFUNCTION()
		void DamageOnOverlap(AActor* HitActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly)
		float maxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere)
		float currentHealth = maxHealth;

	UPROPERTY()
		UWorld* WorldRef;

	UPROPERTY()
		AMainCharacter* mainCharacter;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
