// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardZombie.h"


// Sets default values
AStandardZombie::AStandardZombie()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
}

// Called when the game starts or when spawned
void AStandardZombie::BeginPlay()
{
	Super::BeginPlay();
	health = maxHealth;
	OnActorBeginOverlap.AddDynamic(this, &AStandardZombie::DamageOnOverlap);
	
}

float AStandardZombie::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(health, DamageToApply);
	health -= DamageToApply;
	UE_LOG(LogTemp, Warning, (TEXT("Health Remaining: %f")), health);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Health Remaining: %f"), health));

	Destroy();

	return DamageToApply;
}

void AStandardZombie::DamageOnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("[BasicZombie Debug] - Overlapped!"));
	GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString::Printf(TEXT("[BasicZombie Debug] - Overlapped Actor is %s, other is %s "), *OverlappedActor->GetName(), *OtherActor->GetName()));
	UGameplayStatics::ApplyDamage(OtherActor, 0.1f, GetWorld()->GetFirstPlayerController(), this, UDamageType::StaticClass());

}

void AStandardZombie::Destroy()
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
void AStandardZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStandardZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

