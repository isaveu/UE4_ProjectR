// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RCharacter.generated.h"

UCLASS()
class PROJECTR_API ARCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// ~ Begin ACharacter Interface
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;;
	// ~ End ACharacter Interface

	UFUNCTION(BlueprintCallable, Exec)
	void SetWasTargeted(bool bTargeted);

private:
	// Axis Mapping
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);
	
	// Action Mapping
	void StartJump();
	void EndJump();
	void StartSprint();
	void StopSprint();
	void ToggleLockOnTarget();

private:
	void LockOnTarget();
	void UpdateRotationToLockOnTarget(float DeltaTime);
	bool CheckLockOnTargetIsValid();
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	uint8 bSprinting : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	uint8 bLockOnTarget: 1;

	UPROPERTY(EditAnywhere, Category = Character)
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, Category = Character)
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, Category = Component)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Component)
	class UCameraComponent* MainCamera;

	// {{ Later
	//UPROPERTY(VisibleAnywhere, Category = Component)
	//class URTargetPointComponent* TargetPointComponent;
	// }} Later

	// {{ For test
	UPROPERTY(EditDefaultsOnly, Category = Test)
	class UStaticMeshComponent* TargetPointComponent;
	// }} For test

	UPROPERTY()
	class ARPlayerControllerBase* CachedPlayerController;

	TWeakObjectPtr<class URCharacterAnimInstance> CharacterAnim;

	TWeakObjectPtr<ARCharacter> LockOnCharacter;
};
