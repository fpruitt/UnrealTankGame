// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAIController.generated.h"

/// Forward Declerations
class AActor;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()

class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimTowardsTarget();

protected:
	UTankAimingComponent* AimingComponent = nullptr;

private:
	// How close can the AI Tank get before it stops moving towards us.
	float AcceptanceRadius = 3000;
};
