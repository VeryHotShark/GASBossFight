#include "Base/XBaseCharacter.h"

#include "Base/XGameplayTags.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/XAbilitySystemComponent.h"
#include "GAS/XAttributeSet.h"
#include "GAS/XGameplayAbility.h"
#include "Player/XPlayerState.h"

class AXPlayerState;

AXBaseCharacter::AXBaseCharacter()
{
	
}

AXBaseCharacter::AXBaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));
}

void AXBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(DeathMontage)
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AXBaseCharacter::DeathMontageEnded);
}

void AXBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(AXPlayerState* PS = GetPlayerState<AXPlayerState>())
	{
		AbilitySystemComponent = Cast<UXAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
		AttributeSet = PS->GetAttributeSet();

		AbilitySystemComponent->SetTagMapCount(TAG_Status_Dead, 0);
		InitializeAttributes();
		SetHealth(GetMaxHealth());
		SetStamina(GetMaxStamina());
		AddStartupEffects();
		AddAbilities();
	}
}


bool AXBaseCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

float AXBaseCharacter::GetHealth() const
{
	return AttributeSet.IsValid() ? AttributeSet->GetHealth() : 0.0f;
}

float AXBaseCharacter::GetMaxHealth() const
{
	return AttributeSet.IsValid() ? AttributeSet->GetMaxHealth() : 0.0f;
}

float AXBaseCharacter::GetStamina() const
{
	return AttributeSet.IsValid() ? AttributeSet->GetStamina() : 0.0f;
}

float AXBaseCharacter::GetMaxStamina() const
{
	return AttributeSet.IsValid() ? AttributeSet->GetMaxStamina() : 0.0f;
}

void AXBaseCharacter::Death()
{
	RemoveAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0.0f;
	GetCharacterMovement()->Velocity = FVector::ZeroVector;

	OnDeath.Broadcast(this);

	if(AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();
		
		FGameplayTagContainer EffectsTagsToRemove;
		EffectsTagsToRemove.AddTag(TAG_Event_RemoveOnDeath);

		int NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(TAG_Status_Dead);
	}

	if(DeathMontage)
		PlayAnimMontage(DeathMontage);
	else
		DeathEnd();
}

void AXBaseCharacter::DeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if(Montage == DeathMontage)
		DeathEnd();
}

void AXBaseCharacter::DeathEnd()
{
	Destroy();
}


UAbilitySystemComponent* AXBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void AXBaseCharacter::SetHealth(float Health)
{
	if(AttributeSet.IsValid())
		AttributeSet->SetHealth(Health);
}

void AXBaseCharacter::SetStamina(float Stamina)
{
	if(AttributeSet.IsValid())
		AttributeSet->SetStamina(Stamina);
}

void AXBaseCharacter::RemoveAbilities()
{
	if(!AbilitySystemComponent.IsValid())
		return;

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;

	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if(Spec.SourceObject == this && Abilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int i = 0; i < AbilitiesToRemove.Num(); ++i)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}
}

void AXBaseCharacter::AddAbilities()
{
	if(!AbilitySystemComponent.IsValid())
		return;

	for (TSubclassOf<UXGameplayAbility> Ability : Abilities)
	{
		const FGameplayAbilitySpec Spec(Ability
			, 1
			, static_cast<int32>(Ability.GetDefaultObject()->InputID)
			, this);
		AbilitySystemComponent->GiveAbility(Spec);
	}
}

void AXBaseCharacter::InitializeAttributes()
{
	if(!AbilitySystemComponent.IsValid() || !DefaultAttributes)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);

	if(NewHandle.IsValid())
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
}

void AXBaseCharacter::AddStartupEffects()
{
	if(!AbilitySystemComponent.IsValid())
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (const TSubclassOf<UGameplayEffect> StartupEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(StartupEffect, 1, EffectContext);

		if(NewHandle.IsValid())
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}