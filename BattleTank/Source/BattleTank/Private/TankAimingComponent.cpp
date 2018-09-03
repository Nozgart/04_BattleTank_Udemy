// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h" 
#include "Kismet/GameplayStatics.h" 
#include "Kismet/GameplayStaticsTypes.h" 

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}
// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	LastFireTime = FPlatformTime::Seconds();
}
// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if (RoundsLeft <= 0)
	{
	FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Locked;
	}
	else
	{
		FiringState = EFiringState::Aiming;
	}
}

EFiringState UTankAimingComponent::GetFiringState()
{
	return FiringState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector BarrelForwardVector = Barrel->GetForwardVector();

	return BarrelForwardVector.Equals(AimDirection, 0.01);
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet)) {  return; }
	Barrel = BarrelToSet;
	if (!ensure(TurretToSet)) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	))
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelAndTurretTowards(AimDirection);
	}
	else
	{
	}
}

void UTankAimingComponent::MoveBarrelAndTurretTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) > 180.f)
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }

		if (FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked)
		{
			if (!ensure(ProjectileBluePrint)) { return; }

			FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
			FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));

			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, StartLocation, StartRotation);

			if (Projectile)
			{
				Projectile->LaunchProjectile(LaunchSpeed);

				LastFireTime = FPlatformTime::Seconds();

			}
			RoundsLeft--;
		}
}