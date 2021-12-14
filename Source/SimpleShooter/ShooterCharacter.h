// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.h"
#include "ShooterCharacter.generated.h"



UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraArmComp")
		class USpringArmComponent * CameraArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraComp")
		class UCameraComponent * CameraComp;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//virtual FVector GetPawnViewLocation() const override;
	UFUNCTION(BlueprintPure)
	    bool IsDead() const;

	
	void Shoot();
	void ShootDown();
	void ShootUp();

    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
private:
	void Moveforward(float Axisvalue);
	void Moveright(float Axisvalue);
	void Lookuprate(float Axisvalue);
	void Lookrightrate(float Axisvalue);

	//void Lookup(float Axisvalue);
	UPROPERTY(EditAnywhere)
		float Rotationrate = 10;
	UPROPERTY(EditAnywhere)
		float Health ;
	UPROPERTY(EditAnywhere)
		float Maxhealth= 100;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGun> GunClass;
	UPROPERTY()
		AGun* Guns;
	FTimerHandle FireTimer;

};
