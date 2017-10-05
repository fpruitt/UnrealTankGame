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

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}
