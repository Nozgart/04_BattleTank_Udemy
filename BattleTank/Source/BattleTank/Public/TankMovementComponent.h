// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

		UFUNCTION(BlueprintCallable, Category = CustomMoving)
		void IntendMoveForward(float Throw);

		UFUNCTION(BlueprintCallable, Category = CustomMoving)
		void IntendTurnRight(float Throw);

		UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankTrack* LeftToSet, UTankTrack* RightToSet);

		virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
	
};
