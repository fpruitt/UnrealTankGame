// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank."));
	}
	UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *ControlledTank->GetName());
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
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
	if (!ControlledTank) {return;}
	// Get World Location through crosshair
	FVector HitLocation; // Out parameter
	bool bDidHit = GetSightRayHitLocation(HitLocation);
	if (bDidHit) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
	}
	//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	
	// If it hits the landscape
		//Tell controlled tank to aim at point

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutLocation) const {
	/// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation of Crosshair: %s"), *ScreenLocation.ToString());
	
	/// Get Look Direction
	FVector LookDirection, WorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("WorldDirection of Crosshair: %s"), *LookDirection.ToString());
		/// Line-trace along that look direction, and see what we hit (up to some  max range)
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