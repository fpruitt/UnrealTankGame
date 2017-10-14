// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankPlayerController.generated.h"

/// Forward Declerations
class ATank;

/**
 * Player Controller for Tanks controlled by humans, not AI 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutLocation) const;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
