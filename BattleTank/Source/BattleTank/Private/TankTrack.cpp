// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "GameFramework/Actor.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.f, 1.f);
	DriveTrack(CurrentThrottle);
	//UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentThrottle)
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto WheelsArr = GetWheels();
	auto ForcePerWheel = ForceApplied / WheelsArr.Num();

	for (USceneComponent* Wheel : WheelsArr)
	{
		//auto Name = Cast<USpawnPoint>(Wheel)->GetSpawnedWheel();
		//UE_LOG(LogTemp, Warning, TEXT("%s is child of %s, Drive force is %f"), *Name->GetName(), *this->GetName(), ForcePerWheel);
		Cast<USpawnPoint>(Wheel)->GetSpawnedWheel()->AddDrivingForce(ForcePerWheel);
	}

	//for (ASprungWheel* Wheel : WheelsArr)
	//{
	//	Wheel->AddDrivingForce(ForcePerWheel);
	//}

}

//TArray<ASprungWheel*> UTankTrack::GetWheels() const
//{
//	TArray<ASprungWheel*> ResultArray;
//	TArray<USceneComponent*> Children;
//
//	GetChildrenComponents(true, Children);
//
//	for (USceneComponent* Child : Children)
//	{
//		auto SpawnPointChild = Cast<USpawnPoint>(Child);
//		if (!SpawnPointChild) { continue; }
//
//		AActor* SpawnedChild = SpawnPointChild->GetSpawnedWheel();
//		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
//		if (!SpawnedChild) { continue; }
//
//		ResultArray.Add(SprungWheel);
//	}
//
//	return ResultArray;
//}

TArray<USceneComponent*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> WheelsArray;

	this->GetChildrenComponents(false, WheelsArray);
	
	//for (USceneComponent* i : WheelsArray)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("%s is child of %s"), *i->GetName(), *this->GetName());
	//}
	return WheelsArray;
}
