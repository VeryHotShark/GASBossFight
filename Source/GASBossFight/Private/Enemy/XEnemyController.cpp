// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/XEnemyController.h"

#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/XEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/XPlayerCharacter.h"
#include "Player/XPlayerState.h"


class AXPlayerState;

AXEnemyController::AXEnemyController(const FObjectInitializer& ObjectInitializer)
	 :Super(ObjectInitializer)
{
	bWantsPlayerState = true;
}

void AXEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(AXPlayerState* PS = GetPlayerState<AXPlayerState>(); PS != nullptr)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}

	Player = Cast<AXPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Enemy = Cast<AXEnemyCharacter>(InPawn);

	if(BT)
	{
		RunBehaviorTree(BT);

		if(!Player)
		{
			FTimerDelegate TimerDelegate;
			TimerDelegate.BindLambda([&]
			{
				Player = Cast<AXPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
				GetBlackboardComponent()->SetValueAsObject(PlayerKey, Player);	
			});
			
			GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
		}
		else
			GetBlackboardComponent()->SetValueAsObject(PlayerKey, Player);	
			
	}
}
