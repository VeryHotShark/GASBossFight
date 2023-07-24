// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "XAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GASBOSSFIGHT_API UXAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;
};
