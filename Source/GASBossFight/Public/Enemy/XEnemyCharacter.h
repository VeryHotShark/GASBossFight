// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XBaseCharacter.h"
#include "XEnemyCharacter.generated.h"

class AXEnemyController;
class AXPlayerCharacter;

UCLASS()
class GASBOSSFIGHT_API AXEnemyCharacter : public AXBaseCharacter
{
	GENERATED_BODY()

public:
	AXEnemyCharacter();

	UPROPERTY(BlueprintReadOnly, Category="Enemy")
	AXEnemyController* EnemyController;

	UPROPERTY(BlueprintReadOnly, Category="Enemy")
	AXPlayerCharacter* Player;

	virtual void PossessedBy(AController* NewController) override;
};
