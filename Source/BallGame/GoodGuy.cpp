// Fill out your copyright notice in the Description page of Project Settings.


#include "GoodGuy.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

void AGoodGuy::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
}

AGoodGuy::AGoodGuy()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void AGoodGuy::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGoodGuy::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGoodGuy::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AGoodGuy::LookRight);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AGoodGuy::LookUp);
    PlayerInputComponent->BindAction(TEXT("Launch"), EInputEvent::IE_Pressed, this, &AGoodGuy::Launch);
}

void AGoodGuy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bLaunch)
    {
        FVector CurrentLocation = GetActorLocation();
        if (!FVector::PointsAreNear(CurrentLocation, LaunchDestination, 2))
        {
            FVector TargetLocation = FMath::VInterpTo(CurrentLocation, LaunchDestination, DeltaTime, LaunchSpeed);
            SetActorLocation(TargetLocation);
        }
        else 
        {
            bLaunch = false;
            LaunchDestination = FVector::Zero();
            StartLocation = CurrentLocation;
        }
        return;
    }

    if (!MovementDirection.IsZero())
    {
        UE_LOG(LogTemp, Warning, TEXT("Manual Movement"));

        FVector TargetLocation = GetActorLocation() + MovementDirection * MovementSpeed * DeltaTime;
        SetActorLocation(TargetLocation);
        StartLocation = TargetLocation;
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("Auto Movement"));

        Hover(DeltaTime);
    }
}

void AGoodGuy::MoveForward(float Value)
{
    MovementDirection.X = FMath::Clamp(Value, -1, 1);
}

void AGoodGuy::MoveRight(float Value)
{
    MovementDirection.Y = FMath::Clamp(Value, -1, 1);
}

void AGoodGuy::LookUp(float Value)
{
    AddControllerPitchInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AGoodGuy::LookRight(float Value)
{
    AddControllerYawInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());

    // FRotator DeltaRotation = FRotator::ZeroRotator;
    // DeltaRotation.Yaw = Value * RotationRate * GetWorld()->GetDeltaSeconds();
   
    // AddActorLocalRotation(DeltaRotation);
}

void AGoodGuy::Launch()
{
    if (!bLaunch)
    {
        FVector CurrentLocation = GetActorLocation();   
        LaunchDestination = CurrentLocation + LaunchVelocity;
        bLaunch = true;
    }
}

void AGoodGuy::Hover(float DeltaTime)
{
    if (HoverDestinationReach())
    {
        FVector MoveDirection = HoverVelocity.GetSafeNormal();
        StartLocation = StartLocation + MoveDirection * HoverDistance;
        SetActorLocation(StartLocation);

        HoverVelocity = -HoverVelocity; 
    }
    else 
    {
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = CurrentLocation + HoverVelocity * DeltaTime;
        SetActorLocation(NewLocation);
    }
    
}

bool AGoodGuy::HoverDestinationReach() const 
{
    return GetDistancedMoved() > HoverDistance;
}

float AGoodGuy::GetDistancedMoved() const
{
    return FVector::Dist(StartLocation, GetActorLocation());
}
