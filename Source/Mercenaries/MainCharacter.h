// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacter.generated.h"

class AHandgun;

UCLASS()
class MERCENARIES_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AHandgun> HandgunClass;

	UPROPERTY()
		AHandgun* Handgun;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Handles Input for moving FORWARD and BACK
	UFUNCTION()
		void MoveForward(float value);

	//Handles input for moving RIGHT and LEFT
	UFUNCTION()
		void MoveRight(float value);

	UFUNCTION()
		void Shoot();

	UFUNCTION()
		void printHealth();

	//FPS camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* MainCharacterCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY()
		int32 playerScore;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		int32 currentScore;

	UPROPERTY()
		float maxHealth = 1.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float currentHealth;

};
