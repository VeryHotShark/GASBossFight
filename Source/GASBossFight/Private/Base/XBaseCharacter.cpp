#include "Base/XBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/XAbilitySystemComponent.h"
#include "GAS/XAttributeSet.h"

AXBaseCharacter::AXBaseCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	DeathTag = FGameplayTag::RequestGameplayTag(FName("State.Tag"));
	RemoveEffectOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveEffect"));
}


// Called when the game starts or when spawned
void AXBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AXBaseCharacter::DeathMontageEnded);
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
		EffectsTagsToRemove.AddTag(RemoveEffectOnDeathTag);

		int NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeathTag);
	}

	if(DeathMontage)
		PlayAnimMontage(DeathMontage);
	else
		DeathEnd();
}

void AXBaseCharacter::DeathMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
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
	
}

void AXBaseCharacter::SetStamina(float Stamina)
{
	
}

void AXBaseCharacter::RemoveAbilities()
{
	if(!AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
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

	AbilitySystemComponent->CharacterAbilitiesGiven = false;
}

void AXBaseCharacter::AddAbilities()
{
	if(!AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven)
		return;

	for (TSubclassOf<UXGameplayAbility> Ability : Abilities)
	{
		const FGameplayAbilitySpec Spec(Cast<UGameplayAbility>(Ability), 1 , INDEX_NONE, this);
		AbilitySystemComponent->GiveAbility(Spec);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void AXBaseCharacter::InitializeAttributes()
{
	
}

void AXBaseCharacter::AddStartupEffects()
{
	
}