// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "SimpleShooterGameModeBase.h"
// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = Maxhealth;
	Guns = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Guns->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,TEXT("weapon_socket"));
	Guns->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Moveforward"),this,&AShooterCharacter::Moveforward);
	PlayerInputComponent->BindAxis(TEXT("Lookup"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Moveright"), this, &AShooterCharacter::Moveright);
	PlayerInputComponent->BindAxis(TEXT("Lookright"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("Lookrightrate"), this, &AShooterCharacter::Lookrightrate);
	PlayerInputComponent->BindAxis(TEXT("Lookuprate"), this, &AShooterCharacter::Lookuprate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ShootDown);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, this, &AShooterCharacter::ShootUp);


}

//FVector AShooterCharacter::GetPawnViewLocation() const
//{
//	
//	if (CameraComp)
//	{
//		return CameraComp->GetComponentLocation();
//	}
//	return Super::GetPawnViewLocation();
//}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}





float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//float DamageApplied = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigatorDamageCauser);
	DamageAmount = FMath::Min(Health, DamageAmount);
	Health -= DamageAmount;
	UE_LOG(LogTemp,Warning,TEXT("health left %f"),Health);
	if( IsDead()) {
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		

	}
	return DamageAmount;
	
}

void AShooterCharacter::Moveforward(float Axisvalue)
{
	AddMovementInput(GetActorForwardVector()*Axisvalue);
}

void AShooterCharacter::Moveright(float Axisvalue)
{
	AddMovementInput(GetActorRightVector()*Axisvalue);
}


void AShooterCharacter::Lookuprate(float Axisvalue)
{
	AddControllerPitchInput(Axisvalue*Rotationrate*GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Lookrightrate(float Axisvalue)
{
	AddControllerYawInput(Axisvalue*Rotationrate*GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Guns->PullTrigger();
}

void AShooterCharacter::ShootDown()
{
	GetWorld()->GetTimerManager().SetTimer(FireTimer,this, &AShooterCharacter::Shoot, 0.1f, true, 0.f);
}

void AShooterCharacter::ShootUp()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

//void AShooterCharacter::Lookup(float Axisvalue)
//{
	//AddControllerPitchInput(Axisvalue);
//}
