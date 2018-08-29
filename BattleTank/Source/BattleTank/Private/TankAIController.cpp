// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h "
#include "Engine/World.h"
#include "GameFramework/Pawn.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	ControlledTank = GetPawn();
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ensure(ControlledTank))
	{
		if (ensure(PlayerTank))
		{
			MoveToActor(PlayerTank, AcceptanceRadius);

			AimingComponent->AimAt(PlayerTank->GetActorLocation());
			
			if (AimingComponent->GetFiringState() == EFiringState::Locked)
			{
				AimingComponent->Fire();
			}
		}
	}
}