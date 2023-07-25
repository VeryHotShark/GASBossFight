// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/XBaseCharacter.h"
#include "XPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class GASBOSSFIGHT_API AXPlayerCharacter : public AXBaseCharacter
{
	GENERATED_BODY()

public:
	AXPlayerCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category= "Camera")
	FORCEINLINE float GetInitialCameraBoomLength() const {return InitialCameraBoomArmLength;}

	UFUNCTION(BlueprintCallable, Category= "Camera")
	FORCEINLINE FVector GetInitialCameraBoomLocation() const {return InitialCameraBoomLocation;}
	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const {return  CameraBoom;}
	FORCEINLINE UCameraComponent* GetFollowCamera() const {return  FollowCamera;}

protected:
	UPROPERTY(BlueprintReadOnly, Category="Camera")
	float InitialCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly, Category="Camera")
	FVector InitialCameraBoomLocation;

	UPROPERTY(BlueprintReadOnly, Category= "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, Category= "Camera")
	UCameraComponent* FollowCamera;

	bool ASCInputBound = false;

	void BindASCInput();

	virtual void BeginPlay() override;
};
