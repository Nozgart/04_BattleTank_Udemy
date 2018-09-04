// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("C++ CONSTRUCTOR"))
}
// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartHealth;
	UE_LOG(LogTemp, Warning, TEXT("C++ BEGIN PLAY"))
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor* DamageCauser)
{
	CurrentHealth = CurrentHealth - FMath::Clamp(FGenericPlatformMath::RoundToInt(DamageAmount), int32(0), CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("%i"), CurrentHealth)
	return DamageAmount;
}