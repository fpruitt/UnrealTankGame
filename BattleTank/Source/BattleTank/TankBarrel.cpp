// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	// Clamp given speed to a -1 <= x <= 1 value, 1 being the fastest it can move up and -1 being the fastest it can move down. 
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	// Calculate the requested change in elevation based on frameratee
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	/// Calculate then bound the new elevation of this barrel to a value between the minimum elevation and maximum elevation.
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	//UE_LOG(LogTemp, Warning, TEXT("Elevate Debug: Initial Rotation: %s --- RelativeSpeed: %f --- ElevationChange: %f --- RawNewElevation: %f --- Elevation: %f"), *RelativeRotation.ToString(), ElevationChange, RawNewElevation, Elevation);
	//UE_LOG(LogTemp, Warning, TEXT("Calculated Final Rotation: %s"), *RelativeRotation.ToString());
	SetRelativeRotation(FRotator(Elevation, 0, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Actual Final Rotation: %s"), *RelativeRotation.ToString());

}


