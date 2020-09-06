// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPlayerCameraManager.h"
#include "Character/RPlayerControllerBase.h"

ARPlayerCameraManager::APlayerCameraManager()
{
}

void ARPlayerCameraManager::InitializeFor(APlayerController * PC)
{
	Super.InitializeFor(PC);

	ARPlayerControllerBase* NewPC = Cast<ARPlayerControllerBase>(PC);
	if (NewPC)
	{
		CachedPlayerController = NewPC;
	}
}

void ARPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	
}

void ARPlayerCameraManager::UpdateRotationToLockOnTarget(float DeltaTime)
{
}

bool ARPlayerCameraManager::CheckTargetIsValid()
{
	return false;
}
