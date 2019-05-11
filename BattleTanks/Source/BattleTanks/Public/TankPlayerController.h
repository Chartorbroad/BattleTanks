// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h" //must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


private:

	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetWorldDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;
	bool GetLookVectorHitLocation(FVector& HitLocation, FVector WorldDirection) const;

	UPROPERTY(EditAnywhere)
	float m_CrossHairXLocation;
	UPROPERTY(EditAnywhere)
	float m_CrossHairYLocation;

	//UPROPERTY(BlueprintAssignable)
	float m_LineTraceRange;
	
};
