// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToActor(GetPlayerTank(), AcceptanceRadius);
	AimTowardsPlayer();
	GetControlledTank()->Fire();
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