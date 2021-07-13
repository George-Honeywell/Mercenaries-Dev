// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicZombie.h"
#include "MainCharacter.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

// Sets default values
ABasicZombie::ABasicZombie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	//BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnCollision);

	health = maxHealth;


	
}

// Called when the game starts or when spawned
void ABasicZombie::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ABasicZombie::DamageOnOverlap);	
}

float ABasicZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(health, DamageToApply);
	health -= DamageToApply;
	UE_LOG(LogTemp, Warning, (TEXT("Health Remaining: %f")), health);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Health Remaining: %f"), health));
	
	Destroy();

	return DamageToApply;
}

void ABasicZombie::DamageOnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("[BasicZombie Debug] - Overlapped!"));
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString::Printf(TEXT("[BasicZombie Debug] - Overlapped Actor is %s, other is %s "), *OverlappedActor->GetName(), *OtherActor->GetName()));
	UGameplayStatics::ApplyDamage(OtherActor, 25.0f, GetWorld()->GetFirstPlayerController(), this, UDamageType::StaticClass());
	
}



void ABasicZombie::Destroy()
{
	if (health <= 0)
	{
		UWorld* WorldRef = GetWorld();
		AMainCharacter* mainCharacter = Cast<AMainCharacter>(WorldRef->GetFirstPlayerController()->GetCharacter());
		mainCharacter->currentScore += 500;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Score: %i"), mainCharacter->currentScore));
		AActor::Destroy();
	}
}

// Called every frame
void ABasicZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


