// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RCharacterAnimInstance.h"
#include "Character/RCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


URCharacterAnimInstance::URCharacterAnimInstance()
{
}

void URCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CharacterSpeedSq = Pawn->GetMovementComponent()->Velocity.SizeSquared2D();
		bIsFalling = Pawn->GetMovementComponent()->IsFalling();
	}

}

bool URCharacterAnimInstance::IsJumpEndStopPlaying() const
{
	return bIsPlayingJumpStop;
}
