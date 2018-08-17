// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "GameFramework/Actor.h"


void UTankMovementComponent::Initialise(UTankTrack * LeftToSet, UTankTrack * RightToSet)
{
	LeftTrack = LeftToSet;
	RightTrack = RightToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	auto MoveVelocitySpeed = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s go to %s"), *TankName, *MoveVelocitySpeed)
	Velocity = MoveVelocity;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}