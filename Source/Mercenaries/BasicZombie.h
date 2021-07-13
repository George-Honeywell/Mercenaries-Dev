// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Pawn.h"
#include "BasicZombie.generated.h"

UCLASS()
class MERCENARIES_API ABasicZombie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicZombie();

	UFUNCTION()
		void Destroy();

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollider;

	UFUNCTION()
		void DamageOnOverlap(AActor* OverlappedActor, AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;



private:
	UPROPERTY(EditDefaultsOnly)
		float maxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere)
		float health;

	void DealDamage();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
