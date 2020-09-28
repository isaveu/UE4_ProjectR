// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RCharacter.h"
#include "Character/Components/RCharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/RCharacterAnimInstance.h"
#include "Character/Components/RTargetPointComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Character/RPlayerControllerBase.h"
#include "HUD/RHUD.h"


// Sets default values
ARCharacter::ARCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bSprinting = false;
	bLockOnTarget = false;

	WalkSpeed = 300.f;
	SprintSpeed = 800.f;
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 450.f;
	SpringArm->SetupAttachment(RootComponent);

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(SpringArm);
	
	// Later
	//TargetPointComponent = CreateDefaultSubobject<URTargetPointComponent>(TEXT("TargetPointComponent"));
	
	// {{ Test
	TargetPointComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TargetPointComponent"));
	TargetPointComponent->SetupAttachment(RootComponent);

	TargetRectangleWidth = 250.f;
	TargetRectangleHeight = 150.f;

	// }} Test

}

// Called when the game starts or when spawned
void ARCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Caching Anim Instance
	auto NewAnim = Cast<URCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	if (::IsValid(NewAnim))
	{
		CharacterAnim = NewAnim;
	}

	// Target Point Test 
	TargetPointComponent->SetHiddenInGame(true);

}

// Called every frame
void ARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CheckLockOnTargetIsValid())
	{
		UpdateRotationToLockOnTarget(DeltaTime);
	}

}

// Called to bind functionality to input
void ARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis Mapping
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ARCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ARCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ARCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ARCharacter::LookUp);

	// Action Mapping
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ARCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ARCharacter::EndJump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ARCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ARCharacter::StopSprint);
	PlayerInputComponent->BindAction(TEXT("LockOnTarget"), EInputEvent::IE_Released, this, &ARCharacter::ToggleLockOnTarget);

}

void ARCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	ARPlayerControllerBase* NewPlayerController = Cast<ARPlayerControllerBase>(NewController);
	if (NewPlayerController)
	{
		CachedPlayerController = NewPlayerController;
	}

}

void ARCharacter::UnPossessed()
{
	CachedPlayerController = nullptr;

	Super::UnPossessed();
}

void ARCharacter::SetWasTargeted(bool bTargeted)
{
	// {{ Test
	if (!IsValid(TargetPointComponent))
	{
		return;
	}

	TargetPointComponent->SetHiddenInGame(!bTargeted);

	// }} Test

}

void ARCharacter::MoveForward(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		if (CharacterAnim.IsValid())
		{
			CharacterAnim->bInputMoveToward = false;
		}
		return;
	}

	if (CharacterAnim.IsValid())
	{
		//if (CharacterAnim->IsJumpEndStopPlaying())
		//{
		//	return;
		//}
		//else
		{
			CharacterAnim->bInputMoveToward = true;
		}
	}


	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void ARCharacter::MoveRight(float AxisValue)
{
	if (AxisValue == 0.f)
	{
		if (CharacterAnim.IsValid())
		{
			CharacterAnim->bInputMoveRight = false;
		}
		return;
	}

	if (CharacterAnim.IsValid())
	{
		//if (CharacterAnim->IsJumpEndStopPlaying())
		//{
		//	return;
		//}
		//else
		{
			CharacterAnim->bInputMoveRight = true;
		}
	}

	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void ARCharacter::Turn(float AxisValue)
{
	// If LockOnActor is valid, do nothing
	if (CheckLockOnTargetIsValid())
	{
		return;
	}

	// If character is falling, can not turn.
	if (GetCharacterMovement())
	{
		if(GetCharacterMovement()->IsFalling() 
			&& GetCharacterMovement()->bOrientRotationToMovement)
		{ 
			GetCharacterMovement()->bOrientRotationToMovement = false;
		}
		else if (!GetCharacterMovement()->IsFalling()
			&& !GetCharacterMovement()->bOrientRotationToMovement)
		{
			GetCharacterMovement()->bOrientRotationToMovement = true;
		}
	}
	
	// If value is zero, do nothing.
	if (AxisValue == 0.f)
	{
		return;
	}

	AddControllerYawInput(AxisValue);
}

void ARCharacter::LookUp(float AxisValue)
{
	// If LockOnActor is valid, do nothing
	if (CheckLockOnTargetIsValid())
	{
		return;
	}

	// If value is zero, do nothing.
	if (AxisValue == 0.f)
	{
		return;
	}

	AddControllerPitchInput(AxisValue);
}

void ARCharacter::StartJump()
{
	Jump();
}

void ARCharacter::EndJump()
{
	StopJumping();
}

void ARCharacter::StartSprint()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (Movement && Movement->IsFalling())
	{
		return;
	}

	Movement->MaxWalkSpeed = SprintSpeed;

}

void ARCharacter::StopSprint()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	if (!::IsValid(Movement))
	{
		return;
	}

	Movement->MaxWalkSpeed = WalkSpeed;

}

void ARCharacter::ToggleLockOnTarget()
{
	if (bLockOnTarget)
	{
		bLockOnTarget = false;
		LockOnCharacter->SetWasTargeted(false);
		LockOnCharacter.Reset();
	}
	else
	{
		LockOnTarget();
	}

}

// Lock on target
void ARCharacter::LockOnTarget()
{
	// Check is locally controlled
	if (!IsLocallyControlled())
	{
		return;
	}

	// Get local player controller
	APlayerController* LocalPlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	if (!IsValid(LocalPlayerController))
	{
		return;
	}

	// Get center position of screen & Check actors in rectangle on screen
	AHUD* MyHUD = LocalPlayerController->GetHUD();
	if (!IsValid(MyHUD))
	{
		return;
	}

	int32 Width, Height;
	LocalPlayerController->GetViewportSize(Width, Height);

	FVector2D ViewportCenter(Width / 2.f, Height / 2.f);
	TArray<ARCharacter*> ActorsOnRectangle;

	bool bSuccess = MyHUD->GetActorsInSelectionRectangle<ARCharacter>(
		FVector2D(ViewportCenter.X - (TargetRectangleWidth / 2.f), ViewportCenter.Y - (TargetRectangleHeight - 2.f)),
		FVector2D(ViewportCenter.X + (TargetRectangleWidth / 2.f), ViewportCenter.Y + (TargetRectangleHeight - 2.f)),
		ActorsOnRectangle);
	if (!bSuccess || !ActorsOnRectangle.Num())
	{
		return;
	}

	ARCharacter* Closest = nullptr;
	float DotResult = -1.f;
	float CachedDotResult = -1.f;
	FVector MyLocation = GetActorLocation();
	// Get closest actor to center of screen -> use dot product
	for (ARCharacter* InCharacter : ActorsOnRectangle)
	{
		if (!IsValid(InCharacter))
		{
			continue;
		}

		DotResult = FVector::DotProduct(MyLocation, InCharacter->GetActorLocation());
		if (DotResult > CachedDotResult)
		{
			CachedDotResult = DotResult;
			Closest = InCharacter;
		}
	}


	//// Raycast to target
	//FVector CamLoc;
	//FRotator CamRot;
	//LocalPlayerController->GetPlayerViewPoint(CamLoc, CamRot);

	//const FVector TraceStart = CamLoc;
	//const FVector TraceEnd = TraceStart + CamRot.Vector() * 100000.f; // Magic number

	//FHitResult Hit;
	//FCollisionObjectQueryParams CollisionObjectQueryParams(ECC_Pawn);

	//FCollisionQueryParams CollisionQueryParams;
	//CollisionQueryParams.bTraceComplex = false;
	//CollisionQueryParams.AddIgnoredActor(this);

	//bSuccess = GWorld->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, CollisionObjectQueryParams, CollisionQueryParams);
	//if (!bSuccess)
	//{
	//	return;
	//}

	// Cache locked on character
	//LockOnCharacter = Cast<ARCharacter>(Hit.Actor);
	LockOnCharacter = Closest;
	if (LockOnCharacter.IsValid())
	{
		bLockOnTarget = true;
		LockOnCharacter->SetWasTargeted(true);
	}
	else
	{
		bLockOnTarget = false;
	}


}

void ARCharacter::UpdateRotationToLockOnTarget(float DeltaTime)
{
	const FVector Dir = LockOnCharacter->GetActorLocation() - GetActorLocation();
	if (CachedPlayerController)
	{
		FVector CamLoc;
		FRotator CamRot;

		CachedPlayerController->GetPlayerViewPoint(CamLoc, CamRot);
		
		FRotator RotationDelta;
		RotationDelta = FMath::RInterpTo(CamRot, Dir.Rotation(), DeltaTime, 5.f);
		CachedPlayerController->SetControlRotation(RotationDelta);
	}
	
}

bool ARCharacter::CheckLockOnTargetIsValid()
{
	if (!LockOnCharacter.IsValid())
	{
		return false;
	}

	float DistSq = FVector::DistSquared(LockOnCharacter->GetActorLocation(), GetActorLocation());
	if (DistSq > 4000000.f && bLockOnTarget) // Magic Number
	{
		ToggleLockOnTarget();
		return false;
	}
	
	return true;
}
