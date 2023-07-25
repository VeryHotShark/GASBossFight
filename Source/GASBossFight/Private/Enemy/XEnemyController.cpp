// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/XEnemyController.h"

AXEnemyController::AXEnemyController()
{
	bWantsPlayerState = true;
}

void AXEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
