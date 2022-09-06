// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseBall.generated.h"

UCLASS()
class BALLGAME_API ABaseBall : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Ball Game | Base | Properties")
	float MovementSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Ball Game | Base | Properties")
	float RotationRate = 50.f;

	UPROPERTY(VisibleAnywhere, Category = "Ball Game | Base | Properties")
	FVector MovementDirection;

	UPROPERTY(VisibleAnywhere, Category = "Ball Game | Base | Properties")
	FRotator ViewRotation;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Ball Game | Components")
	UStaticMeshComponent * Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Ball Game | Component")
	class UCapsuleComponent *CapsuleComp;



};
