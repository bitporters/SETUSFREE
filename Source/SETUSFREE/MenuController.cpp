// Fill out your copyright notice in the Description page of Project Settings.

#include "SETUSFREE.h"
#include "MenuController.h"


void AMenuController::REFRESH()
{
	GAMES_FOUND.Empty();

	Http = &FHttpModule::Get();
	if (!Http) return;
	if (!Http->IsHttpEnabled()) return;

	TSharedRef <IHttpRequest> Request = Http->CreateRequest();
	Request->SetVerb("POST");
	Request->SetURL("http://pewpewcraft.com/include/_apps/_gameserver/getgames.aspx?op=42ad5d32-9fec-4959-ad2e-203d422134a7");
	Request->SetContentAsString("");
	Request->SetHeader("User-Agent", "ppcGameClient/0.0.6");
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	Request->OnProcessRequestComplete().BindUObject(this, &AMenuController::REFRESH_RESPONSE);
	
	if (!Request->ProcessRequest())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "ProcessRequest Failed - Get Games");
	}
}

void AMenuController::REFRESH_RESPONSE(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{


	// If HTTP fails client-side, this will still be called but with a NULL shared pointer!
	if (!Response.IsValid())
	{
		LastError = "RESPONSE WAS NOT VALID";
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, LastError);
		REFRESH_ERROR();
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		FString MessageBody = "";
		MessageBody = Response->GetContentAsString();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, MessageBody);
		FString left;
		FString right;

		while (MessageBody.Len() > 0)
		{
			if (MessageBody.Split("~", &left, &MessageBody))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, MessageBody);
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, left);
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, right);
				TArray<FString> tokens;
				left.ParseIntoArray(&tokens, TEXT("|"), 1);

				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(tokens.Num()));

				FInternetGame game;
				game.IP = tokens[0];
				game.VERSION = tokens[1];
				game.PLAYERS_CURRENT = FCString::Atoi(*tokens[2]);
				game.PLAYERS_MAX = FCString::Atoi(*tokens[3]);
				game.GAME_NAME = tokens[4];
				GAMES_FOUND.Add(game);
			}
		}

		REFRESH_SUCCESS();
	}
	else
	{
		LastError = FString::Printf(TEXT("{\"success\":\"HTTP Error: %d\"}"), Response->GetResponseCode());
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, LastError);
		REFRESH_ERROR();
	}


}

void AMenuController::JOIN_GAME(FString URL, FString CHARACTER_NAME)
{
	this->ClientTravel(URL + "?CHARACTER_NAME=" + CHARACTER_NAME, ETravelType::TRAVEL_Absolute, false, FGuid());
}



