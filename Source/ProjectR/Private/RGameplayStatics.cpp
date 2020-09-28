// Fill out your copyright notice in the Description page of Project Settings.


#include "RGameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"

bool URGameplayStatics::GetActorsInCircleOnScreen(TSubclassOf<AActor> ClassFilter, APlayerController * LocalPlayerController, FVector2D CenterPosition, float Radius, TArray<AActor*>& OutActors)
{
	if (!IsValid(LocalPlayerController))
	{
		return false;
	}

	if (Radius < KINDA_SMALL_NUMBER)
	{
		return false;
	}

	UWorld* World = LocalPlayerController->GetWorld();
	if (!IsValid(World))
	{
		return false;
	}

	OutActors.Empty();

	FVector2D ProjectedPosition;

	for (TActorIterator<AActor> It(World, ClassFilter); It; ++It)
	{
		if (It->WasRecentlyRendered())
		{
			LocalPlayerController->ProjectWorldLocationToScreen(It->GetActorLocation(), ProjectedPosition);
			if (FVector2D::Distance(ProjectedPosition, CenterPosition) < Radius)
			{
				OutActors.Add(*It);
			}
		}

	}

	return true;
}
