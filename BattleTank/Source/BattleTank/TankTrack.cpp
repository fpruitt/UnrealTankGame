// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	
	
	// TODO clamp throttle
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce * AccelerationScalar;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	UE_LOG(LogTemp, Warning, TEXT("%s TrackMaxDrivingForce: %f -- force applied: %s"), *Name, TrackMaxDrivingForce, *ForceApplied.ToString());
}


