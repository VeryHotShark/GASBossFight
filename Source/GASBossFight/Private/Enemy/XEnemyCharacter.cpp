// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/XEnemyCharacter.h"

#include "Enemy/XEnemyController.h"

AXEnemyCharacter::AXEnemyCharacter()
{
	AIControllerClass = AXEnemyController::StaticClass();
}

void AXEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	EnemyController = Cast<AXEnemyController>(NewController);

	if(EnemyController != nullptr)
	{
		Player = EnemyController->Player;
	}
}
