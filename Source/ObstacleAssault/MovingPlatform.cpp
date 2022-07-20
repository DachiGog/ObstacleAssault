// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move platform Forwards
		//Get current location
	FVector CurentLocation = GetActorLocation();
		//add vector to that location
		CurentLocation += PlatforVelocity * DeltaTime;
		// Set location
	SetActorLocation(CurentLocation);
	// Send Platform Back if gone too far
		// check how far
	float DistanceMoved = FVector::Dist(StartLocation, CurentLocation);
		//reverse 
	if(DistanceMoved >= MoveDistance){
		FVector MoveDirection = PlatforVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatforVelocity *= -1;
	}
}

