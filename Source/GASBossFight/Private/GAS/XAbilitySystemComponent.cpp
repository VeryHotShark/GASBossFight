// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/XAbilitySystemComponent.h"

void UXAbilitySystemComponent::ReceiveDamage(UXAbilitySystemComponent* ASC, float UnmitigatedDamage,
	float MitigatedDamage)
{
	OnReceivedDamage.Broadcast(ASC, UnmitigatedDamage, MitigatedDamage);
}
