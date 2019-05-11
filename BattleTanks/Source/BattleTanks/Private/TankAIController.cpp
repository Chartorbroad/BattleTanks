// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay(); // This ensures that the parent BeginPlay() function still gets called! (i.e. the class from which this inherits)
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) { UE_LOG(LogTemp, Warning, TEXT("TankAIController has a tank: %s"), *(ControlledTank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("TankAIController does not have a tank")); }

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) { UE_LOG(LogTemp, Warning, TEXT("TankAIController has identifed in the scene a PlayerTank: %s"), *(PlayerTank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("TankAIController has not identified in the scene a PlayerTank")); }

}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		// TODO Move towards the player

		// Aim towards the player
		if (GetControlledTank()) {
			GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation()); //i.e. AI tanks are *always* aiming at the player
		}

		// Fire at the player if ready
	}

}

ATank* ATankAIController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());

}

ATank* ATankAIController::GetPlayerTank() const {

	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!playerTank) { return nullptr; }
	else { return playerTank; }

}