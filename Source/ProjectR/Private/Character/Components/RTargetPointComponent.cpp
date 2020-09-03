// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/RTargetPointComponent.h"

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

	// ...
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

