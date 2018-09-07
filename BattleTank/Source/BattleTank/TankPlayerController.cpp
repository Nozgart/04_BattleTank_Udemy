// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h "
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{	}
	else
	{
		FoundAimingComponent(AimingComponent);
	}
	auto TankPawn = GetPawn();

	if (!ensure(TankPawn))
	{	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is %s"), *(TankPawn->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDead.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Dead Player"));
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetPawn())) { return; }

	FVector HitLocation;
	bool bGotHitLocatiom = GetSightRayHitLocation(HitLocation);

	//UE_LOG(LogTemp, Warning, TEXT("%i"), bGotHitLocatiom);

	if (bGotHitLocatiom)
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	FVector LookDirection;

	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	auto ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation*ViewportSizeY);

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;

	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraWorldLocation,
		OUT LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel
	(
		OUT HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0.f, 0.f, 0.f);
		return false;
	}
}



