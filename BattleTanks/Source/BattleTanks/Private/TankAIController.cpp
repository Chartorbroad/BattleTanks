// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay(); // This ensures that the parent BeginPlay() function still gets called! (i.e. the class from which this inherits)
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) { UE_LOG(LogTemp, Warning, TEXT("TankAIController has a tank: %s"), *(ControlledTank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("TankAIController does not have a tank")); }

}

ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());

}