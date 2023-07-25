// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GAS/XAttributeSet.h"
#include "XPlayerState.generated.h"

struct FGameplayTag;
class UXAttributeSet;
class UXAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GASBOSSFIGHT_API AXPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AXPlayerState();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UXAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category="Player State")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category="Player State | UI")
	void ShowAbilityConfirmCancelText(bool ShowText);

	UFUNCTION(BlueprintCallable, Category="Player State | Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category="Player State | Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category="Player State | Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category="Player State | Attributes")
	float GetMaxStamina() const;

protected:
	UPROPERTY()
	UXAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UXAttributeSet* AttributeSet;

	FDelegateHandle OnHealthChanged;
	FDelegateHandle OnMaxHealthChanged;
	FDelegateHandle OnStaminaChanged;
	FDelegateHandle OnMaxStaminaChanged;

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);
	
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
};
