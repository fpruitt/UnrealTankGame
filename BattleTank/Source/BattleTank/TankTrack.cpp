// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Track Ticking"));
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	
	
	// TODO clamp throttle
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce * AccelerationScalar;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("%s TrackMaxDrivingForce: %f -- force applied: %s"), *Name, TrackMaxDrivingForce, *ForceApplied.ToString());
}


