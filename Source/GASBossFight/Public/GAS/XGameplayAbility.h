// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "XGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class AbilityID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
};

UCLASS()
class GASBOSSFIGHT_API UXGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UXGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	AbilityID InputID = AbilityID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Ability")
	bool ActivateOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
