// Fill out your copyright notice in the Description page of Project Settings.

#include "SETUSFREE.h"
#include "SETUSFREE_PLAYERSTATE.h"


void ASETUSFREE_PLAYERSTATE::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(ASETUSFREE_PLAYERSTATE, MY_PLAYER_NAME);
}
