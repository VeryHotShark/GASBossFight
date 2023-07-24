// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "XAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnReceivedDamageDelegate, UXAbilitySystemComponent*, ASC, float, UnmitigatedDamage, float, MitigatedDamage);

UCLASS()
class GASBOSSFIGHT_API UXAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FOnReceivedDamageDelegate OnReceivedDamage;

	virtual void ReceiveDamage(UXAbilitySystemComponent* ASC, float UnmitigatedDamage, float MitigatedDamage);
	
};
