// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
	float AccelerationScalar = 4.;


private:
	virtual void BeginPlay() override;
	UTankTrack();
	//virtual void OnRegister();
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void ApplySidewaysForce();
	void DriveTrack();
	// Based on average tank mass of 40kg and a 0-60mph in 10 seconds acceleration. Unit is Newtons.
	float TrackMaxDrivingForce = 10729000.;
	float CurrentThrottle = 0.;
	// OnHit Event Delegate
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
