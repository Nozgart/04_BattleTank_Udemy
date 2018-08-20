// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankTrack.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("C++ CONSTRUCTOR"))
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("C++ BEGIN PLAY"))
}

void  ATank::AimAt(FVector HitLocation)
{
	if (ensure(TankAimingComponent))
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
	else
	{
		return;
	}
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if (!ensure(Barrel)) { return; }

	if (IsReloaded)
	{
		UE_LOG(LogTemp, Warning, TEXT("fire"))
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, StartLocation, StartRotation);

		if (Projectile)
		{
			Projectile->LaunchProjectile(LaunchSpeed);

			LastFireTime = FPlatformTime::Seconds();
		}
	}
}
