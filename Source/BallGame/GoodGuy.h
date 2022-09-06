// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBall.h"
#include "GoodGuy.generated.h"

/**
 * 
 */
UCLASS()
class BALLGAME_API AGoodGuy : public ABaseBall
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:

	AGoodGuy();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Ball Game | Components")
	class UCameraComponent *Camera;

	UPROPERTY(VisibleAnywhere, Category = "Ball Game | Components")
	class USpringArmComponent *SpringArm;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
	void Launch();
	void Hover(float DeltaTime);
	bool HoverDestinationReach() const;
	float GetDistancedMoved() const;

	UPROPERTY(EditAnywhere, Category = "Ball Game | Hover | Properties")
	FVector HoverVelocity = FVector(0, 0, 1000);

	UPROPERTY(EditAnywhere, Category = "Ball Game | Hover | Properties")
	float HoverDistance = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Ball Game | Launch | Properties")
	FVector LaunchVelocity = FVector(500, 0, 0);

	UPROPERTY(EditAnywhere, Category = "Ball Game | Launch | Properties")
	float LaunchSpeed = 5.f;

	UPROPERTY()
	FVector StartLocation;	

	UPROPERTY()
	FVector LaunchDestination;

	UPROPERTY()
	bool bLaunch;
};
