// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/XAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UXAttributeSet::UXAttributeSet() {}

void UXAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
}
