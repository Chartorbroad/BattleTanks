// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Engine/Public/DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay(); // This ensures that the parent BeginPlay() function still gets called! (i.e. the class from which this inherits)
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) { UE_LOG(LogTemp, Warning, TEXT("TankPlayerController has a tank: %s"), *(ControlledTank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("TankPlayerController does not have a tank")); }


	// This is a hack to avoid having to take information from the UI Widget itself when aiming
	m_CrossHairXLocation = 0.5;
	m_CrossHairYLocation = 0.33333;

	// this is editable also in BP
	m_LineTraceRange = 100000; //1km in cm

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
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s "), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
	}



}

// Get world location of linetrace through crosshair, return true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); // this fills these variables

	FVector2D ScreenLocation(m_CrossHairXLocation * ViewportSizeX, m_CrossHairYLocation * ViewportSizeY);

	// "De-project" the screen position of the crosshair to a world direction
	FVector WorldDirection;
	if (GetWorldDirection(ScreenLocation, WorldDirection)) {

		// Line-trace along that direction
		// See what we hit (up to a maximum range)
		GetLookVectorHitLocation(HitLocation, WorldDirection);

	}

	return true;

}

bool ATankPlayerController::GetWorldDirection(FVector2D ScreenLocation, FVector& WorldDirection) const {

	FVector CameraWorldLocation; // gets discarded as we don't use it
	return (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection));

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector WorldDirection) const {

	/// Ray-cast (Line-trace) out to reach distance
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (WorldDirection * m_LineTraceRange);
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
		
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;

}