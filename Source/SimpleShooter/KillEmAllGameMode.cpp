// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr) {
		Endgame(false);
	}
	for (AShooterAIController* controller :TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!controller->isDead())
		{
			return;
		}
	}
	Endgame(true);

}

void AKillEmAllGameMode::Endgame(bool IsPlayerWinner)
{
	for (AController*controller :TActorRange<AController>(GetWorld()))
	{
		bool Iswinner = controller->IsPlayerController() == IsPlayerWinner;
		controller->GameHasEnded(controller->GetPawn(), Iswinner);
	}
}
