// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPlayerControllerBase.h"
#include "Character/RPlayerCameraManager.h"

ARPlayerControllerBase::ARPlayerControllerBase()
{
	PlayerCameraManagerClass = ARPlayerCameraManager::StaticClass();

}
