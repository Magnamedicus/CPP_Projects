// Fill out your copyright notice in the Description page of Project Settings.


#include "Flyer.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AFlyer::AFlyer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//movement functions
void AFlyer::ProcessKeyRoll(float Rate) {
	if (FMath::Abs(Rate) > 0.2f) {

		ProcessRoll(Rate * 2.f);
	}

}

void AFlyer::ProcessKeyThrottle(float Rate) {
	if (FMath::Abs(Rate) > 0.2f) {

		ProcessThrottle(Rate *2.f);
	}

	else if (FMath::Abs(Rate) < 0.2f) {
		Acceleration = 0;
	}

}

void AFlyer::ProcessThrottle(float Value){

	Acceleration += Value * 10.0f;
}

void AFlyer::ProcessRoll(float Value) {

	bIntentionalRoll = FMath::Abs(Value) > 0.0f;

	if (bIntentionalPitch && !bIntentionalRoll) {
		return;
	}

	float TargetRollSpeed = bIntentionalRoll ? (Value * RollRateMultiplier) : (GetActorRotation().Roll * -2.f); 
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld() -> GetDeltaSeconds(), 2.f);
}

void AFlyer::ProcessKeyPitch(float Rate) {

	if (FMath::Abs(Rate) > 0.2f) {

		ProcessPitch(Rate * 2.f);
	}


}

void AFlyer::ProcessPitch(float Value) {

	bIntentionalPitch = FMath::Abs(Value) > 0.0f;

	float TargetPitchSpeed = Value * PitchRateMultiplier; 
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed,TargetPitchSpeed, GetWorld() -> GetDeltaSeconds(), 2.f);


}


void AFlyer::ProcessMouseXInput(float Value) {

		ProcessRoll(Value);


}

void AFlyer::ProcessMouseYInput(float Value) {

		ProcessPitch(Value);

}

void AFlyer::NotifyHit(
    UPrimitiveComponent* MyComp, 
    AActor* Other, 
    UPrimitiveComponent* OtherComp,  
    bool bSelfMoved, 
    FVector HitLocation, 
    FVector HitNormal, 
    FVector NormalImpulse, 
    const FHitResult& Hit
) {
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    // Deflect along surface
    const FRotator CurrentRotation = GetActorRotation();
    SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));

    // Slow down
    CurrentForwardSpeed = FMath::FInterpTo(CurrentForwardSpeed, MinSpeed, GetWorld()->GetDeltaSeconds(), 5.0f);
}


// Called when the game starts or when spawned
void AFlyer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Display, TEXT("Acceleration: %f"), Acceleration);
	UE_LOG(LogTemp, Display, TEXT("CurrentForwardSpeed: %f"), CurrentForwardSpeed);

	//Calculate Thrust
		//This line slows or speeds the plane based on nose pitch
	//const float CurrentAcc = GetActorRotation().Pitch * DeltaTime * Acceleration;
	const float CurrentAcc = DeltaTime * Acceleration;
	const float NewForwardSpeed = CurrentForwardSpeed + CurrentAcc;

	//Clamping keeps a value from going below or above given parameters
	//NewForwardSpeed will not drop below MinSpeed or rise above MaxSpeed
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
	Acceleration = FMath::Clamp(Acceleration, 0, 100);

	const FVector LocalMove = FVector(NewForwardSpeed * DeltaTime, 0.0f, 0.0f);
	AddActorLocalOffset(LocalMove, true);


	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;

	AddActorLocalRotation(DeltaRotation);

}

// Called to bind functionality to input
void AFlyer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis("Turn", this, &AFlyer::ProcessMouseXInput);
	PlayerInputComponent -> BindAxis("TurnRate", this, &AFlyer::ProcessKeyRoll);
	PlayerInputComponent -> BindAxis("LookUp", this, &AFlyer::ProcessMouseYInput);
	PlayerInputComponent -> BindAxis("LookUpRate", this, &AFlyer::ProcessKeyPitch);
	PlayerInputComponent -> BindAxis("ThrottleRate", this, &AFlyer::ProcessKeyThrottle);

	

}