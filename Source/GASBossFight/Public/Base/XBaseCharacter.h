// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "XBaseCharacter.generated.h"

class UGameplayEffect;
class UXGameplayAbility;
class UXAttributeSet;
class UXAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, AXBaseCharacter*, BaseCharater);

UCLASS()
class GASBOSSFIGHT_API AXBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AXBaseCharacter();
	
	// Sets default values for this character's properties
	AXBaseCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category="Base Character")
	FOnDeathDelegate OnDeath;
	
	UFUNCTION(BlueprintCallable, Category="Base Character")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category="Base Character | Attributes")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category="Base Character | Attributes")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable, Category="Base Character | Attributes")
	float GetStamina() const;
	
	UFUNCTION(BlueprintCallable, Category="Base Character | Attributes")
	float GetMaxStamina() const;
	
	virtual void Death();
	virtual void DeathEnd();

	UFUNCTION()
	void DeathMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	TWeakObjectPtr<UXAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UXAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Base Character | Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Base Character | Abilities")
	TArray<TSubclassOf<UXGameplayAbility>> Abilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Base Character | Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Base Character | Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	virtual void RemoveAbilities();
	virtual void AddAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();

	virtual void SetHealth(float Health);
	virtual void SetStamina(float Stamina);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
