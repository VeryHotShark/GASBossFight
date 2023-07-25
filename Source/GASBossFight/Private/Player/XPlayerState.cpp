// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XPlayerState.h"

#include "Base/XGameplayTags.h"
#include "GAS/XAbilitySystemComponent.h"
#include "GAS/XAttributeSet.h"

AXPlayerState::AXPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UXAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	AttributeSet = CreateDefaultSubobject<UXAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AXPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;	
}

UXAttributeSet* AXPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

bool AXPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void AXPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	// TODO
}

float AXPlayerState::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float AXPlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float AXPlayerState::GetStamina() const
{
	return AttributeSet->GetStamina();
}

float AXPlayerState::GetMaxStamina() const
{
	return AttributeSet->GetMaxStamina();
}

void AXPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		OnHealthChanged = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AXPlayerState::HealthChanged);
		OnMaxHealthChanged = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AXPlayerState::MaxHealthChanged);
		OnStaminaChanged = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetStaminaAttribute()).AddUObject(this, &AXPlayerState::StaminaChanged);
		OnMaxStaminaChanged = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &AXPlayerState::MaxStaminaChanged);

		AbilitySystemComponent->RegisterGameplayTagEvent(TAG_Status_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AXPlayerState::StunTagChanged);
	}
}

void AXPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning, TEXT("Health Changed"));
}

void AXPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning, TEXT("Max Health Changed"));
}

void AXPlayerState::StaminaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning, TEXT("Stamina Changed"));
}

void AXPlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning, TEXT("Max Stamina Changed"));
}

void AXPlayerState::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if(NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(TAG_Ability);

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(TAG_Event_NotCanceledByStun);
		
		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}
}
