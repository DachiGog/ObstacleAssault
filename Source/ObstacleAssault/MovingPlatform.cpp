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

	FString Name = GetName();
	
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);


}

void AMovingPlatform::MovePlatform(float DeltaTime)
{	
	if(ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatforVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatforVelocity *= -1;
	}
	else
	{
	FVector CurentLocation = GetActorLocation();
	CurentLocation += PlatforVelocity * DeltaTime;
	SetActorLocation(CurentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{	
	AddActorLocalRotation(RotateVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{	
	return GetDistanceMoved() >= MoveDistance;
}
float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
