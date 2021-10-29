// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBasic.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AZombieBasic::AZombieBasic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMesh->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	boxCollider->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
}

// Called when the game starts or when spawned
void AZombieBasic::BeginPlay()
{
	Super::BeginPlay();
	currentHealth = maxHealth;
	OnActorBeginOverlap.RemoveDynamic(this, &AZombieBasic::DamageOnOverlap);
	OnActorBeginOverlap.AddDynamic(this, &AZombieBasic::DamageOnOverlap);	
}

float AZombieBasic::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(currentHealth, DamageToApply);
	currentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, (TEXT("Zombie Health Remaining: %f.")), currentHealth);

	Destroy();

	return DamageToApply;
}

void AZombieBasic::DamageOnOverlap(AActor* HitActor, AActor* OtherActor)
{	
	if (OtherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(OtherActor, 25.0f, GetWorld()->GetFirstPlayerController(), this, UDamageType::StaticClass());
	}	
}

void AZombieBasic::Destroy()
{
	if (currentHealth <= 0)
	{
		WorldRef = GetWorld();
		mainCharacter = Cast<AMainCharacter>(WorldRef->GetFirstPlayerController()->GetCharacter());
		mainCharacter->currentScore += 500;
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

