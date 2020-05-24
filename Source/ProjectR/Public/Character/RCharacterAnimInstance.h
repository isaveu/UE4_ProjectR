// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API URCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	URCharacterAnimInstance();

public:
	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	//UPROPERTY()
	//TWeakObjectPtr<class ARCharacter> OwnerCharacter;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= Character, Meta=(AllowPrivateAccess =true))
	float CharacterSpeedSq = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	bool bSprinting = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool bIsFalling = false;

};
