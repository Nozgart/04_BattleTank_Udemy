// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto TankPawn = GetControlledTank();

	if (!TankPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("AIController missing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is %s"), *(TankPawn->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




