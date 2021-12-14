// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	FVector shotDirection;
	FRotator Rotation;
	FHitResult Onhit;

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	
	FVector Muzzlelocation = Mesh->GetSocketLocation("MuzzleFlashSocket");
	FVector  End = Muzzlelocation + Rotation.Vector() * MaxRange;
	UParticleSystemComponent* TraceComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, Muzzlelocation, shotDirection.Rotation(), true);
	TraceComp->SetVectorParameter("ShockBeamEnd", End);
	
	bool  Hitsuccess = GunTrace(Onhit, shotDirection);
	if (Hitsuccess) {
		
		//DrawDebugPoint(GetWorld(), Onhit.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect , Onhit.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Onhit.Location);
		
		AActor* HitActor = Onhit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent Damagevent(Damage, Onhit, shotDirection, nullptr);
			AController *PawnController = GetOwnerCtroller();
			HitActor->TakeDamage(Damage, Damagevent, PawnController, this);
		}
	}
	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector ShotDirection)
{
	AController *PawnController = GetOwnerCtroller();
	if (PawnController == nullptr) 
		return false;
	FVector Location;
	FRotator Rotation;
	PawnController->GetPlayerViewPoint(Location, Rotation);
    ShotDirection = -Rotation.Vector();
	FVector  End = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, params);
}

AController * AGun::GetOwnerCtroller() const
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (PawnOwner == nullptr) 
		return nullptr;
	return PawnOwner->GetController();
	

}

