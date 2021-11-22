// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Handgun.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component
	MainCharacterCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(MainCharacterCameraComponent != nullptr);

	// Attach the camera component to our capsule component
	MainCharacterCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes
	MainCharacterCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation
	MainCharacterCameraComponent->bUsePawnControlRotation = true;

	gunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	gunMesh->AttachToComponent(MainCharacterCameraComponent, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

	gunMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("GunMuzzle"));
	gunMuzzle->AttachToComponent(gunMesh, FAttachmentTransformRules::KeepRelativeTransform);

	currentHealth = maxHealth;
	playerScore = currentScore;

	enemiesKilled = 0;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	Handgun = GetWorld()->SpawnActor<AHandgun>(HandgunClass);
	Handgun->SetOwner(this);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setup movement bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// Setup Look Bindings
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

	// Setup Weapon Shooting
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMainCharacter::Shoot);
}

void AMainCharacter::MoveForward(float value)
{
	// Find out which way is "forward" and reocrd that the player wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AMainCharacter::MoveRight(float value)
{
	// Find out which way is "right" and record that the player wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AMainCharacter::Shoot()
{
	Handgun->bCanShoot();
}

float AMainCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(currentHealth, DamageToApply);
	currentHealth -= DamageToApply;

	if (currentHealth <= 0.0f)
	{
		UWorld* World = GetWorld();
		APlayerController* pController = World->GetFirstPlayerController();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("You're Dead!"));
		pController->ConsoleCommand("quit");
	}

	return DamageAmount;
}






