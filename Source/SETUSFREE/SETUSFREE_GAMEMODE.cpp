// Fill out your copyright notice in the Description page of Project Settings.

#include "SETUSFREE.h"
#include "SETUSFREE_GAMEMODE.h"

FString ASETUSFREE_GAMEMODE::InitNewPlayer(class APlayerController* NewPlayerController, const TSharedPtr<FUniqueNetId>& UniqueId, const FString& Options, const FString& Portal)
{
	FString NAME_FROM_PARAMS = ParseOption(Options, TEXT("CHARACTER_NAME"));

	ASETUSFREE_PLAYERSTATE* pstate = Cast<ASETUSFREE_PLAYERSTATE>(NewPlayerController->PlayerState);
	if (pstate != NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "CONNECTING PLAYER: " + NAME_FROM_PARAMS);

		pstate->MY_PLAYER_NAME = "Un-named Player";
		if (NAME_FROM_PARAMS.Len() > 0) pstate->MY_PLAYER_NAME = NAME_FROM_PARAMS;

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, "ADDING PLAYER: " + pstate->MY_PLAYER_NAME);
	}

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void ASETUSFREE_GAMEMODE::REPORT_GAME()
{
	FHttpModule* Http = &FHttpModule::Get();
	if (!Http) return;
	if (!Http->IsHttpEnabled()) return;

	int numPlayers = 1;

	FString qstring("?op=42ad5d32-9fec-4959-ad2e-203d422134a7&v=0.0.3&p=" + FString::FromInt(numPlayers) + "&pmax=6" + "&n=RCTRAINER");

	TSharedRef <IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("POST");
	Request->SetURL("http://pewpewcraft.com/include/_apps/_gameserver/notify.aspx" + qstring);
	Request->SetContentAsString("");
	Request->SetHeader("User-Agent", "ppcGameClient/0.0.6");
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");

	/*
	Request->OnProcessRequestComplete().BindUObject(this, &Appc_mainMenuController::RefreshPPCServers_Reponse);
	*/
	if (!Request->ProcessRequest()) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "ProcessRequest Failed - Get Games");
}



