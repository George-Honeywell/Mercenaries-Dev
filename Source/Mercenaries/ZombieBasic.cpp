// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBasic.h"

// Sets default values
AZombieBasic::AZombieBasic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
}

// Called when the game starts or when spawned
void AZombieBasic::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;
	OnActorBeginOverlap.AddDynamic(this, &AZombieBasic::DamageOnOverlap);
}

float AZombieBasic::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(currentHealth, DamageToApply);
	currentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, (TEXT("Health Remaining: %f")), currentHealth);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("Health Remaining: %f"), health));

	Destroy();

	return DamageToApply;
}

void AZombieBasic::DamageOnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("[BasicZombie Debug] - Overlapped!"));
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("[ZombieBasic Debug] - Overlapped Actor is %s, other is %s "), *OverlappedActor->GetName(), *OtherActor->GetName()));
	UGameplayStatics::ApplyDamage(OtherActor, 25.0f, GetWorld()->GetFirstPlayerController(), this, UDamageType::StaticClass());

}

void AZombieBasic::Destroy()
{
	if (currentHealth <= 0)
	{
		UWorld* WorldRef = GetWorld();
		AMainCharacter* mainCharacter = Cast<AMainCharacter>(WorldRef->GetFirstPlayerController()->GetCharacter());
		mainCharacter->currentScore += 500;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Score: %i"), mainCharacter->currentScore));
		AActor::Destroy();
	}
}

// Called every frame
void AZombieBasic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombieBasic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

