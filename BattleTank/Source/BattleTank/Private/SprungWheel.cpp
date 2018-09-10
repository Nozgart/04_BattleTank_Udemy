// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Constraint"));
	SetRootComponent(Constraint);

	Axie = CreateDefaultSubobject<USphereComponent>(FName("Axie"));
	Axie->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axie, FAttachmentTransformRules::KeepRelativeTransform);

	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	WheelConstraint->AttachToComponent(Axie, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	SetupConstraint();
	
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* Root = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!Root) { return; }
	Constraint->SetConstrainedComponents(Root, NAME_None, Cast<UPrimitiveComponent>(Wheel), NAME_None);
	WheelConstraint->SetConstrainedComponents(Root, NAME_None, Cast<UPrimitiveComponent>(Axie), NAME_None);
	UE_LOG(LogTemp, Warning, TEXT("NotNULL %s"), *GetAttachParentActor()->GetName());
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

