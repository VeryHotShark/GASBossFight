// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "XAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

UCLASS()
class GASBOSSFIGHT_API UXAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public :

	UXAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, MaxStamina);

	// META ATTRIBUTE
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UXAttributeSet, Damage);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
