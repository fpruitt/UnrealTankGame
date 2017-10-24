// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (DamageAmount > CurrentHealth) {
		DamageAmount = CurrentHealth;
	}
	CurrentHealth -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Hit, new health: %f"), CurrentHealth);
	if (CurrentHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Tank Died!"));
		OnTankDeath.Broadcast();
	}
	
	return DamageAmount;
}

float ATank::GetHealthPercent() const
{
	return CurrentHealth / StartingHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin Play to run
}
