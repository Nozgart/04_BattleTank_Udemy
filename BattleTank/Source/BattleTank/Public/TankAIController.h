// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float AcceptanceRadius = 8000.f;

private:

	APawn* PlayerTank = nullptr;

	APawn* ControlledTank = nullptr;

	UTankAimingComponent* AimingComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;
	


	UFUNCTION()
	void OnTankDeath();
};
