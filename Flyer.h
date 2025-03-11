// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Flyer.generated.h"

UCLASS()
class FANTASYLANDSCAPE_API AFlyer : public ACharacter
{
	GENERATED_BODY()


	



public:
	// Sets default values for this character's properties
	AFlyer();

	UPROPERTY(EditAnywhere, Category = "Flight")
	float Acceleration{30.f};

	UPROPERTY(EditAnywhere, Category = "Flight")
	float MaxSpeed{4000.f};

	UPROPERTY(EditAnywhere, Category = "Flight")
	float MinSpeed{500.f};


	UPROPERTY(EditAnywhere, Category = "Flight")
	float CurrentForwardSpeed{2500.f};

	float CurrentYawSpeed;
	float CurrentPitchSpeed;
	float CurrentRollSpeed;

	UPROPERTY(EditAnywhere, Category = "Flight")
	float RollRateMultiplier{200.f};

	UPROPERTY(EditAnywhere, Category = "Flight")
	float PitchRateMultiplier{200.f};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ProcessKeyPitch(float Rate);
	void ProcessKeyRoll(float Rate);

	void ProcessMouseYInput(float Value);
	void ProcessMouseXInput(float Value);


	//For Calculating Rotation

	void ProcessRoll(float Value);
	void ProcessPitch(float Value);

	//For detecting whether we are intentionally rolling or pitching
	//Will be used to level us off when not actively rolling or pitching
	bool bIntentionalPitch{false};
	bool bIntentionalRoll{false};


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyHit(class UPrimitiveComponent * MyComp, class AActor * Other, class UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

