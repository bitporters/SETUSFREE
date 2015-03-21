// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "SETUSFREE_PLAYERSTATE.h"
#include "Http.h"
#include "SETUSFREE_GAMEMODE.generated.h"

/**
 * 
 */
UCLASS()
class SETUSFREE_API ASETUSFREE_GAMEMODE : public AGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = SYSTEM_OVERRIDES)
	virtual void REPORT_GAME();

	virtual FString InitNewPlayer(class APlayerController* NewPlayerController, const TSharedPtr<FUniqueNetId>& UniqueId, const FString& Options, const FString& Portal = TEXT(""));
};
