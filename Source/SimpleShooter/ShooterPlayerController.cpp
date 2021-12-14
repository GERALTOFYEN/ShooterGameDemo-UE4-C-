// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"



void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HUD = CreateWidget(this, HUDclass);
	if (HUD != nullptr) {
		HUD->AddToViewport();
	}
}
void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner )
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	HUD->RemoveFromViewport();
	if (bIsWinner)
	{
		UUserWidget*WinSscreen = CreateWidget(this, Winscreenclass);
		if (WinSscreen != nullptr) {
			WinSscreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget*LoseSscreen = CreateWidget(this, screenclass);
		if (LoseSscreen != nullptr) {
			LoseSscreen->AddToViewport();
	}

	}
	GetWorldTimerManager().SetTimer(RestartHandle, this, &APlayerController::RestartLevel, RestartDelay);
}
