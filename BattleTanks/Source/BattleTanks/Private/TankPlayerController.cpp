// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay(); // This ensures that the parent BeginPlay() function still gets called! (i.e. the class from which this inherits)
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) { UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has a tank: %s"), *(ControlledTank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("TankPlayerController does not have a tank")); }


	// This is a hack to avoid having to take information from the UI Widget itself when aiming
	m_CrossHairXLocation = 0.5;
	m_CrossHairYLocation = 0.33333;

}

void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s "), *HitLocation.ToString());
		// TODO Tell the controlled tank to aim at this point
	}



}

// Get world location of linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); // this fills these variables

	FVector2D ScreenLocation(m_CrossHairXLocation * ViewportSizeX, m_CrossHairYLocation * ViewportSizeY);
	UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	// "De-project" the screen position of the crosshair to a world direction
	FVector WorldDirection;
	if (GetWorldDirection(ScreenLocation, WorldDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("WorldDirectionn: %s"), *WorldDirection.ToString());
	}

	// Line-trace along that direction
	// See what we hit (up to a maximum range)

	return true;

}


bool ATankerPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const {

	FVector CameraWorldLocation; // gets discarded as we don't use it
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection));

}