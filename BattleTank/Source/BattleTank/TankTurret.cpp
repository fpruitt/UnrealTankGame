// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Clamp given speed to a -1 <= x <= 1 value, 1 being the fastest it can move up and -1 being the fastest it can move down. 
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1., 1.);
	// Calculate the requested change in elevation based on frameratee
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	/// Calculate then bind the new rotation of this turret to a value between the minimum elevation and maximum elevation.
	auto Rotation = RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0., Rotation, 0.));
}
