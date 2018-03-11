// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto TankPawn = GetControlledTank();

	if (!TankPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController missing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is %s"), *(TankPawn->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{ 
		return Cast<ATank>(GetPawn());
}

