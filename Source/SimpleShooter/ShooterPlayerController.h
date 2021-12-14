// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> screenclass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> Winscreenclass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDclass;
	FTimerHandle RestartHandle;
	UUserWidget* HUD;
protected:
	virtual void BeginPlay() override;

};
