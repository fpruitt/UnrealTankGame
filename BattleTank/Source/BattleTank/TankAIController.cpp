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

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Error, TEXT("Player Tank Not Found..."));
	}
	UE_LOG(LogTemp, Warning, TEXT("Found Player Tank: %s"), *PlayerTank->GetName());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ATankAIController::AimTowardsPlayer() {
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}