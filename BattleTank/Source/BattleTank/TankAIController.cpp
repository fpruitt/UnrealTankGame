// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("TankAIController not possessing a tank."));
	}
	UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank: %s"), *ControlledTank->GetName());
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}



