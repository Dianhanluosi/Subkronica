// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SUBKRONICA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Set up camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Cam;

	//Set up control keywords
	//Axis
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	FString MoveForward = "MoveForward";
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	FString MoveRight = "MoveRight";
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	FString LookUp = "LookUp";
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	FString TurnRight = "TurnRight";
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	FString Sprint = "Sprint";
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	FString Hold = "Hold";
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	FString Pee = "Pee";
	
	//Actions
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Crouching = "Crouch";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Jumping = "Jump";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Click = "Click";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString RightClick = "RightClick";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Scroll = "Scroll";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Collect = "Collect";
	
private:
	//Set up movement
	void MoveFowardCtrl (float AxisValue);
	void MoveRightCtrl (float AxisValue);
	void SprintCtrl (float AxisValue);

	//Set up camera movement
	void LookUpCtrl (float AxisValue);
	void TurnRightCtrl (float AxisValue);

	//Set up movement rate
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float RunningSpeed = 500;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float WalkingSpeed = 200;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float MoveSpeed = 100;
	
	//Set up camera rate
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float RotationRateRight = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float RotationRateUp = 50;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float MinPitchAngle = -85;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float MaxPitchAngle = 85;
	
};
