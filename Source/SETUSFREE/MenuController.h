// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Http.h"
#include "MenuController.generated.h"



USTRUCT(BlueprintType)
struct FInternetGame
{

public:

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GHETTO_NET")
	FString GAME_NAME;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GHETTO_NET")
	FString VERSION;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GHETTO_NET")
	FString IP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GHETTO_NET")
	int32 PLAYERS_CURRENT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GHETTO_NET")
	int32 PLAYERS_MAX;

	/** defaults */
	FInternetGame() : GAME_NAME(""), VERSION(""), IP(""), PLAYERS_CURRENT(0), PLAYERS_MAX(0)
	{
	}
};

/**
 * 
 */
UCLASS()
class SETUSFREE_API AMenuController : public APlayerController
{
	GENERATED_BODY()
	
		FHttpModule* Http;



public:

	//ReplicatedUsing = OnRep_ChatUpdated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GHETTO_NET)
	TArray<FInternetGame> GAMES_FOUND;

	UPROPERTY(BlueprintReadWrite, Category = GHETTO_NET)
	FString LastError;

	UFUNCTION(BlueprintImplementableEvent, Category = GHETTO_NET)
	void REFRESH_SUCCESS();

	UFUNCTION(BlueprintImplementableEvent, Category = GHETTO_NET)
	void REFRESH_ERROR();

	UFUNCTION(BlueprintCallable, Category = GHETTONET)
	void REFRESH();

	void REFRESH_RESPONSE(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, Category = GHETTONET)
	void JOIN_GAME(FString URLFString, FString CHARACTER_NAME);
		
};
