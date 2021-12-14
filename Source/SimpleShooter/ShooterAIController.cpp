// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackBoardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior != nullptr) 
	{
		RunBehaviorTree(AIBehavior);
		APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (MyPawn != nullptr)
		{
			GetBlackboardComponent()->SetValueAsVector("StartLocation", GetPawn()->GetActorLocation());
		}
	}
}
void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (LineOfSightTo(MyPawn))
	{
	GetBlackboardComponent()->SetValueAsVector("PlayerLocation", MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector("LastKnownPlayerlocation", MyPawn->GetActorLocation());*/
	////	/*SetFocus(PlayerPawn);
	////	MoveToActor(PlayerPawn,200);*/
	//}
	/*else
	{
	GetBlackboardComponent()->ClearValue("PlayerLocation");*/
	////	/*ClearFocus(EAIFocusPriority::Gameplay);
	////	StopMovement();*/
	//}
	
}

bool AShooterAIController::isDead() const
{
	AShooterCharacter* controller1 = Cast<AShooterCharacter>(GetPawn());
	if (controller1 != nullptr)
	{
		return controller1->IsDead();
	}
	return true;
}
