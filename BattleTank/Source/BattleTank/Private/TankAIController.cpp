// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
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

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)){ return; }
		PossessedTank->OnDead.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}

}

void ATankAIController::OnTankDeath()
{
	ControlledTank->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("Dead AI"));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ensure(ControlledTank))
	{
		if (ensure(PlayerTank))
		{
			MoveToActor(PlayerTank, AcceptanceRadius);

			AimingComponent->AimAt((PlayerTank->GetActorLocation() + FVector(0.f,0.f,50.f)));
			
			if (AimingComponent->GetFiringState() == EFiringState::Locked)
			{
				AimingComponent->Fire();
			}
		}
	}
}


