// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ensure(ControlledTank)) {return;}

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponenet(AimingComponent);
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	auto ControlledTank = GetControlledTank();
	if (!ensure(ControlledTank)) {return;}
	// Get World Location through crosshair
	FVector HitLocation; // Out parameter
	bool bDidHit = GetSightRayHitLocation(HitLocation);
	if (bDidHit) {
		GetControlledTank()->AimAt(HitLocation);
	}
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutLocation) const {
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);	
	/// Get Look Direction
	FVector LookDirection, WorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection)) 
	{
		return GetLookVectorHitLocation(LookDirection, OutLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	const FVector Start = PlayerCameraManager->GetCameraLocation();
	const FVector End = Start + LookDirection * LineTraceRange;

	// Setup Our Collision Query Params
	//UE_LOG(LogTemp, Warning, TEXT("TRACE: Start: %s  , End: %s"), *Start.ToString(), *End.ToString());
	FHitResult LineTraceHit;
	bool bDidHit = GetWorld()->LineTraceSingleByChannel(
		LineTraceHit,
		Start,
		End,
		ECollisionChannel::ECC_Visibility
	);
	if (bDidHit) {
		HitLocation = LineTraceHit.Location;
	}
	return bDidHit;
}