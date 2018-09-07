// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(Constraint);
	
	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("NotNULL %s"), *GetAttachParentActor()->GetName());
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

