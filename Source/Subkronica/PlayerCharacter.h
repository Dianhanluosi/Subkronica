// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterCameraShaker.h"
#include "Components/SceneComponent.h"
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

	//Set up physics handle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics Handle")
	class UPhysicsHandleComponent* PhysicsHandle;

	//Set up pee socket
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pee")
	class USceneComponent* PeeEmitter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pee")
	class UNiagaraComponent* PeeParticle;

	//Set up control keywords
	//Axis
	UPROPERTY(EditAnywhere, Category = "Control Axis")
	bool IsClimbing = false;
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
	FString Pee = "Pee";
	
	//Action
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Jumping = "Jump";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Hold = "Hold";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString LeftClick = "Interact";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString RightClick = "Shoot";
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	FString Crouching = "Crouch";
	// UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	// FString RightClick = "RightClick";
	// UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	// FString Scroll = "Scroll";
	// UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	// FString Collect = "Collect";

	//Camera Shake
	UPlayerCharacterCameraShaker* CamShake;

	//Set up movement rate
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float RunningSpeed = 500;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float WalkingSpeed = 200;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float ClimbingSpeed = 200;
	UPROPERTY(EditDefaultsOnly, Category = "Control Axis")
	float MoveSpeed = 100;

	//Set up jump speed
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	float WalkingJumpSpeed = 800;
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	float RunningJumpSpeed = 1500;

	//Crouch stuff
	//Set up crouch
	//void CrouchCtrl(float AxisValue);
	void CrouchCtrl();
	
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	void CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult) override;
	
	bool bIsCrouching = false;
	UPROPERTY(EditDefaultsOnly, Category = "Control Action")
	float CrouchWalkingSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Control Action")
	FVector CrouchEyeOffSet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Control Action")
	float CrouchSpeed;

	UPROPERTY(EditDefaultsOnly)
	float CrouchRatio = 0.4f;
	UPROPERTY(EditDefaultsOnly)
	float CrouchHeight;

	FVector GetCharacterScale();

	class AInteractableMother* Interactable;
	class AClickableMother* Clickable;

	
	//Sound Shit
	


	//UI Shit
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool IsLookingAtThings;

	
	
private:
	//Set up movement
	void ClimbCtrl (bool bClimb);
	void MoveFowardCtrl (float AxisValue);
	void MoveRightCtrl (float AxisValue);
	void SprintCtrl (float AxisValue);

	bool IsRunning = false;

	//Set up camera movement
	void LookUpCtrl (float AxisValue);
	void TurnRightCtrl (float AxisValue);

	//Hold things
	//UPROPERTY()
	class UGrabber *Grabber;
	
	void HoldThings();
	void LetGoOfThings();

	bool IsHolding = false;

	void Interact();
	void Shoot();

	void PeeCtrl(float AxisValue);
	bool IsPeeing = false;
	
	
	
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


