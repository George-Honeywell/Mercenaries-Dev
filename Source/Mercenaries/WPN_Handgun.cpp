// Fill out your copyright notice in the Description page of Project Settings.


#include "WPN_Handgun.h"

// Sets default values for this component's properties
UWPN_Handgun::UWPN_Handgun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWPN_Handgun::BeginPlay()
{
	Super::BeginPlay();

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent != nullptr)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &UWPN_Handgun::Shoot);
	}
	
}

void UWPN_Handgun::Shoot()
{
	FVector getPlayerViewLocation;
	FRotator getPlayerViewRotation;
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn == nullptr) return;
	AController* OwnerController = OwnerPawn->GetInstigatorController();
		if (OwnerController == nullptr) return;


	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(getPlayerViewLocation, getPlayerViewRotation);

	//Draw a line from the player
	FVector LineTraceEnd = getPlayerViewLocation + getPlayerViewRotation.Vector() * Range;

	//Reach out to a certain distance
	FHitResult hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	
	//Store the hit in a Variable
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(hit, getPlayerViewLocation, LineTraceEnd, ECC_GameTraceChannel2, TraceParams);

	//Store the hit result 
	AActor* HitActor = hit.GetActor();
	if (bIsHit)
	{
		DrawDebugLine(GetWorld(), getPlayerViewLocation, hit.Location, FColor(255, 0, 0), false, 3.0f, 0.0f, 5.0f);
		DrawDebugPoint(GetWorld(), hit.Location, 20.0f, FColor::Green, false, 3.0f, 0.0f);
		if (HitActor != nullptr) 
		{
			FPointDamageEvent DamageEvent(hgPower, hit, LineTraceEnd, nullptr);
			//HitActor->TakeDamage(hgPower, DamageEvent, OwnerController);
		}
		UE_LOG(LogTemp, Warning, TEXT("Actor hit is: %s"), *(HitActor->GetName()));
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("[WEAPON] - Headgun Fired."));

	hgCapacity--;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, FString::Printf(TEXT("Current Ammo: %i"), hgCapacity));

	if (hgCapacity <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Out of Ammo!"));
	}
}

// Called every frame
void UWPN_Handgun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

