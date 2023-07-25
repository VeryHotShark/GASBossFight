// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XPlayerController.h"

#include "Player/XPlayerState.h"

void AXPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(AXPlayerState* PS = GetPlayerState<AXPlayerState>(); PS != nullptr)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}
