// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; };
	FoundAimingComponenet(AimingComponent);
	FoundOwningPawn(GetPawn());

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }  // Not currently posessing a tank
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; };
	// Get World Location through crosshair
	FVector HitLocation; // Out parameter
	bool bDidHit = GetSightRayHitLocation(HitLocation);
	if (bDidHit) {
		AimingComponent->AimAt(HitLocation);
	}
	//

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

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// Subscribe to the tank's death event
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::OnTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("The Player Tank Has Died"));
}