// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "XEnemyController.generated.h"

class AXPlayerCharacter;
class AXEnemyCharacter;

UCLASS()
class GASBOSSFIGHT_API AXEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	inline static const FName PlayerKey = FName("Player");

	AXEnemyController();

	UPROPERTY(EditDefaultsOnly, Category="AI")
	UBehaviorTree* BT;

	UPROPERTY(BlueprintReadOnly, Category="Controller")
	AXPlayerCharacter* Player;

	UPROPERTY(BlueprintReadOnly, Category="Controller")
	AXEnemyCharacter* Enemy;

	virtual void OnPossess(APawn* InPawn) override;
};
