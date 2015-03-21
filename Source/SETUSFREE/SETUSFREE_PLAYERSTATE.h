// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "UnrealNetwork.h"
#include "SETUSFREE_PLAYERSTATE.generated.h"

/**
 * 
 */
UCLASS()
class SETUSFREE_API ASETUSFREE_PLAYERSTATE : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Replicated, BlueprintReadWrite, Category = PlayerDeets)
	FString MY_PLAYER_NAME;
	
};
