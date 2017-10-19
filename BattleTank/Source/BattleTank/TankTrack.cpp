// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	Super::BeginPlay();
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.;
}

void UTankTrack::ApplySidewaysForce()
{
	/// Calculate and apply the amount of force to stop this track's owning tank from sliding.
	// Calculate Slippage Speed, or the amount of sideways movement this tank is currently undergoing.
	auto RightVector = GetRightVector();
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), RightVector);
	// Find the acceleration required to correct for this speed in the current frame.
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * RightVector;
	auto TankBody = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// Using f = ma , where m is the mass of the tank and a is the correction acceleration.
	// Note, this is divided by 2 because there are two tracks doing this calculation.
	auto CorrectionForce = (TankBody->GetMass() * CorrectionAcceleration) / 2;
	// Apply the calculated correction force.
	TankBody->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack()
{
	auto Name = GetName();
	// TODO clamp throttle
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce * AccelerationScalar;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	//UE_LOG(LogTemp, Warning, TEXT("%s TrackMaxDrivingForce: %f -- force applied: %s"), *Name, TrackMaxDrivingForce, *ForceApplied.ToString());
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}


