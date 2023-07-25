// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/XGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "Base/XGameplayTags.h"

UXGameplayAbility::UXGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationBlockedTags.AddTag(TAG_Status_Dead);
	ActivationBlockedTags.AddTag(TAG_Status_Stun);
}

void UXGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if(ActivateOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
		
}
