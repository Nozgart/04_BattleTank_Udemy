// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h "
#include "Engine/World.h"
#include "GameFramework/Pawn.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledPawn = GetControlledTank();

	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController missing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is %s"), *(ControlledPawn->GetName()));
	}

	auto PlayerPawn = GetPlayerTank();

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Can not find player controller"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Find player controller in %s"), *(PlayerPawn->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}	
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




