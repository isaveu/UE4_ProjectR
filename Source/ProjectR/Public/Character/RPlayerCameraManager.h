// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "RPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ARPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ARPlayerCameraManager();

public:
	// ~ Begin APlayerCameraManager Interface

	/**
	 * Initialize this PlayerCameraManager for the given associated PlayerController.
	 * @param PC	PlayerController associated with this Camera.
	 */
	virtual void InitializeFor(class APlayerController* PC) override;
	/**
	 * Performs per-tick camera update. Called once per tick after all other actors have been ticked.
	 * Non-local players replicate the POV if bUseClientSideCameraUpdates is true.
	 */
	virtual void UpdateCamera(float DeltaTime) override;

	// ~ End APlayerCameraManager Interface

private:
	void UpdateRotationToLockOnTarget(float DeltaTime);

private:
	UPROPERTY()
	class ARPlayerControllerBase* CachedPlayerController;

	
};
