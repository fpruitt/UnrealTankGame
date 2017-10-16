// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

/// Forward Declerations 
class UTankBarrel;
class UTankTurret;
class UTankTrack;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTrackReferences(UTankTrack* LeftTrack, UTankTrack* RightTrack);

	UFUNCTION(BlueprintCallable)
	void Fire();

	double LastFireTime = 0.;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Local Barrel reference for spawning projectilee
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	UTankTrack* TankLeftTrack = nullptr;
	UTankTrack* TankRightTrack = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.;

private:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.;

};
