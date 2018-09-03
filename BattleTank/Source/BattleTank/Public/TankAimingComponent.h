// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState: uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	EFiringState GetFiringState();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	int32 GetRoundsLeft() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:

	bool IsBarrelMoving();

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0.;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 8000.f;

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;
	
	FVector AimDirection;

	void MoveBarrelAndTurretTowards(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 RoundsLeft = 3;
};
