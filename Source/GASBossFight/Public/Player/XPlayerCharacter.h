// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XBaseCharacter.h"
#include "XPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GASBOSSFIGHT_API AXPlayerCharacter : public AXBaseCharacter
{
	GENERATED_BODY()

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
