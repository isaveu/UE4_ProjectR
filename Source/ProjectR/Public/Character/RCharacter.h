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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


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

	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bSprinting;

	UPROPERTY(EditAnywhere, Category = Character)
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, Category = Character)
	float SprintSpeed;

	UPROPERTY(VisibleAnywhere, Category = Component)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Component)
	class UCameraComponent* MainCamera;

	TWeakObjectPtr<class URCharacterAnimInstance> CharacterAnim;

};
