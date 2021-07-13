// Fill out your copyright notice in the Description page of Project Settings.


#include "Handgun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values
AHandgun::AHandgun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	currentAmmo = maxCapacity;

}


void AHandgun::Shoot()
{
	
	UE_LOG(LogTemp, Warning, TEXT("Weapon Fired!"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetController();
		if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	FHitResult hit;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * weaponRange;
	
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(hit, Location, End, ECC_GameTraceChannel2);
	if (bIsHit)
	{
		FVector ShotDirection = -Rotation.Vector();
		DrawDebugPoint(GetWorld(), hit.Location, 20, FColor::Green, false, 3.0f);
		DrawDebugLine(GetWorld(), Location, hit.Location, FColor::Red, false, 3.0f, 0.0f, 2.0f);

		AActor* hitActor = hit.GetActor();
		if (hitActor != nullptr) 
		{
			FPointDamageEvent DamageEvent(power, hit, ShotDirection, nullptr);
			hit.GetActor()->TakeDamage(power, DamageEvent, OwnerController, this);
		}
	}
	currentAmmo--;
	//CanShoot();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("[Handgun Debug] - Ammo Remaining: %i"), currentAmmo));
}

// Called when the game starts or when spawned
void AHandgun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHandgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



