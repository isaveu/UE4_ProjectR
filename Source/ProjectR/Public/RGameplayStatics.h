// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "RGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API URGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()
	
public:
	template <typename ClassFilter>
	static bool GetActorsInCircleOnScreen(class APlayerController* LocalPlayerController, FVector2D CenterPosition, float Radius, TArray<ClassFilter*>& OutActors)
	{
		if (!IsValid(LocalPlayerController))
		{
			return false;
		}

		if (Radius < KINDA_SMALL_NUMBER)
		{
			return false;
		}

		if (!ClassFilter::StaticClass()->IsChildOf(AActor::StaticClass()))
		{
			return false;
		}

		TArray<AActor*> OutActorsTemp;
		GetActorsInCircleOnScreen(ClassFilter::StaticClass(), LocalPlayerController, CenterPosition, Radius, OutActorsTemp);
		for (AActor* EachActor : OutActorsTemp)
		{
			OutActors.Add(CastChecked<ClassFilter>(EachActor));
		}


		return true;
	}
	static bool GetActorsInCircleOnScreen(TSubclassOf<AActor> ClassFilter, class APlayerController* LocalPlayerController, FVector2D CenterPosition, float Radius, TArray<AActor*>& OutActors);

};
