// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto TargetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(TargetTank && ControlledTank)) { return; }
	
	// Move
	MoveToActor(TargetTank, AcceptanceRadius);
	
	// Aim
	AimTowardsTarget();

	//Fire
	// TODO refactor to not need reference to Tank class
	//GetPawn()->Fire();
}


void ATankAIController::AimTowardsTarget() {
	auto TargetTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(TargetTank->GetActorLocation());
}