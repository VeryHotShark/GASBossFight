// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/XPlayerCharacter.h"

#include "Base/XGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/XAbilitySystemComponent.h"
#include "GAS/XGameplayAbility.h"
#include "Player/XPlayerState.h"

AXPlayerCharacter::AXPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
}

void AXPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	BindASCInput();
}
void AXPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitialCameraBoomArmLength = CameraBoom->TargetArmLength;
	InitialCameraBoomLocation = CameraBoom->GetRelativeLocation();
}

void AXPlayerCharacter::BindASCInput()
{
	if(AbilitySystemComponent.IsValid() && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent
			, FGameplayAbilityInputBinds(
			FString("ConfirmTarget")
			,FString("CancelTarget")
			,		FString("AbilityID")
			, static_cast<int32>(AbilityID::Confirm)
			, static_cast<int32>(AbilityID::Cancel)));
	}
}