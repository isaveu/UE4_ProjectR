// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RGameMode.h"
#include "Character/RCharacter.h"

ARGameMode::ARGameMode()
{
	DefaultPawnClass = ARCharacter::StaticClass();

}
