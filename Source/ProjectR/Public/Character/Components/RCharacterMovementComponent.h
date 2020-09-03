// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API URCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	URCharacterMovementComponent();
	
	virtual void PhysicsRotation(float DeltaTime) override;


};
