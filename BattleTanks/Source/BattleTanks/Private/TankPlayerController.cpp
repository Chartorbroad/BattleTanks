// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay(); // This ensures that the parent BeginPlay() function still gets called! (i.e. the class from which this inherits)
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) { UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has a tank: %s"), *(ControlledTank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("TankPlayerController does not have a tank")); }

}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());

}