// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/XAssetManager.h"
#include "AbilitySystemGlobals.h"

void UXAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
