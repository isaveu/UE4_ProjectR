// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RGameMode.h"
#include "Character/RCharacter.h"
#include "Character/RPlayerControllerBase.h"

ARGameMode::ARGameMode()
{
	DefaultPawnClass = ARCharacter::StaticClass();
	PlayerControllerClass = ARPlayerControllerBase::StaticClass();

}
