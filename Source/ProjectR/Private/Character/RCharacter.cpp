// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ARCharacter::ARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WalkSpeed = 300.f;
	SprintSpeed = 800.f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 450.f;
	SpringArm->SetupAttachment(RootComponent);

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ARCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ARCharacter::LookUp);

}

void ARCharacter::MoveForward(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void ARCharacter::MoveRight(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void ARCharacter::Turn(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	AddControllerYawInput(AxisValue);
}

void ARCharacter::LookUp(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		return;
	}

	AddControllerPitchInput(AxisValue);
}

