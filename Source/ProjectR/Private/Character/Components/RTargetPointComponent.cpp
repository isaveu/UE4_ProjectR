// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/RTargetPointComponent.h"
#include "Character/RCharacter.h"

// Sets default values for this component's properties
URTargetPointComponent::URTargetPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void URTargetPointComponent::BeginPlay()
{
	Super::BeginPlay();

	// Test
	if (IsValid(PointMesh))
	{
		
	}

}


// Called every frame
void URTargetPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CheckTargetIsValid())
	{
		UpdateRotationToLockOnTarget(DeltaTime);
	}
}

void URTargetPointComponent::SetOwnerTargeting(bool bTargeting)
{
	if (bTargeting)
	{

	}
	else
	{

	}

}

void URTargetPointComponent::LockOnTarget()
{
}

void URTargetPointComponent::UpdateRotationToLockOnTarget(float DeltaTime)
{
}

bool URTargetPointComponent::CheckTargetIsValid()
{
	if (!IsValid(LockOnCharacter) || !IsValid(CachedOwner))
	{
		return false;
	}

	//float DistSq = FVector::DistSquared(LockOnCharacter->GetActorLocation(), CachedOwner->GetActorLocation());
	//if (DistSq > FMath::Square(MaxDistanceLockOn) && bLockOnTarget) // Magic Number
	//{
	//	ToggleLockOnTarget();
	//	return false;
	//}


	return true;
}

