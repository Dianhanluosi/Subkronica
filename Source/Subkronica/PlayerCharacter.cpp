// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/ITargetDevice.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/CapsuleComponent.h"
#include "InteractableMother.h"
#include "Grabber.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Follow Camera
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Cam->SetupAttachment(RootComponent); // Attach the camera to the end of the swing arm
	
	//initialize camera shaker as null pointer
	CamShake = nullptr;

	// Initialize Physics Handle
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	
	//GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	//set up crouching stuff
	CrouchEyeOffSet = FVector(0.f);
	CrouchSpeed = 12.f;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveSpeed = WalkingSpeed;

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	float OriginalHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	CrouchHeight = -(OriginalHeight * CrouchRatio);

	Grabber = FindComponentByClass<UGrabber>();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get the current velocity
	FVector Velocity = GetVelocity();
    
	// Calculate the speed from the velocity vector
	float Speed = Velocity.Size();

	// Log the speed to the output log
	//UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f units/s"), Speed);

	if (GetVelocity().Size() > 0)
	{
		if (CamShake == nullptr)
			  {
			  	CamShake = Cast<UPlayerCharacterCameraShaker>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(UPlayerCharacterCameraShaker::StaticClass()));
			  }
	}
	else
	{
		if (CamShake != nullptr)
		{
			UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StopAllCameraShakes(false);
			CamShake = nullptr;
		}
	}

	//crouch transition setup
	float CroucHInterpTime = FMath::Min(1.f, CrouchSpeed * DeltaTime);
	CrouchEyeOffSet = (1.f - CroucHInterpTime) * CrouchEyeOffSet;

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(*MoveForward, this, &APlayerCharacter::MoveFowardCtrl);
	PlayerInputComponent->BindAxis(*MoveRight, this, &APlayerCharacter::MoveRightCtrl);
	PlayerInputComponent->BindAxis(*Sprint, this, &APlayerCharacter::SprintCtrl);

	PlayerInputComponent->BindAxis(*LookUp, this, &APlayerCharacter::LookUpCtrl);
	PlayerInputComponent->BindAxis(*TurnRight, this, &APlayerCharacter::TurnRightCtrl);

	PlayerInputComponent->BindAxis(*Crouching, this, &APlayerCharacter::CrouchCtrl);

	PlayerInputComponent->BindAxis(*Hold, this, &APlayerCharacter::HoldThings);

	PlayerInputComponent->BindAction(*Jumping, EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	

}

void APlayerCharacter::MoveFowardCtrl(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
	//UE_LOG(LogTemp, Log, TEXT("MoveSpeed: %f"), MoveSpeed);

	// if (CamShake == nullptr)
	//  {
	//  	CamShake = Cast<UPlayerCharacterCameraShaker>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(UPlayerCharacterCameraShaker::StaticClass()));
	//  }
	
}

void APlayerCharacter::MoveRightCtrl(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
	//UE_LOG(LogTemp, Log, TEXT("MoveSpeed: %f"), MoveSpeed);
}

void APlayerCharacter::SprintCtrl(float AxisValue)
{
	if (AxisValue == 1)
	{
		IsRunning = true;
		// MoveSpeed = RunningSpeed;
		// GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
		// GetCharacterMovement()->JumpZVelocity = RunningJumpSpeed;

	}
	else
	{
		IsRunning = false;
		// MoveSpeed = WalkingSpeed;
		// GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		// GetCharacterMovement()->JumpZVelocity = WalkingJumpSpeed;

	}
}


void APlayerCharacter::LookUpCtrl(float AxisValue)
{
	if (Cam)
	{
		FRotator NewRotation = Cam->GetRelativeRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + AxisValue * RotationRateUp * GetWorld()->GetDeltaSeconds(), MinPitchAngle, MaxPitchAngle);
		Cam->SetRelativeRotation(NewRotation);
	}
	
	//AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::TurnRightCtrl(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRateRight * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::CrouchCtrl(float AxisValue)
{
	if (AxisValue == 1)
	{
		//Crouch();
		OnStartCrouch(CrouchHeight, CrouchHeight);
		bIsCrouching = true;
		GetCharacterMovement()->MaxWalkSpeed = CrouchWalkingSpeed;
		GetCharacterMovement()->JumpZVelocity = 0;
	}
	else
	{
		//UnCrouch();
		if (bIsCrouching)
		{
			OnEndCrouch(-CrouchHeight, -CrouchHeight);
			bIsCrouching = false;
			
		}
		if (!IsRunning)
		{
			GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			GetCharacterMovement()->JumpZVelocity = WalkingJumpSpeed;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
			GetCharacterMovement()->JumpZVelocity = RunningJumpSpeed;
		}
		
	}
	
}

//crouching stuff
void APlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0)
	{
		return;
	}

	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffSet.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	Cam->SetRelativeLocation(FVector(0,0,BaseEyeHeight), false);
	//CrouchHeight = -CrouchHeight;
}

void APlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0)
	{
		return;
	}

	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffSet.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	Cam->SetRelativeLocation(FVector(0,0,BaseEyeHeight), false);
	//CrouchHeight = -CrouchHeight;

}

void APlayerCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	if (Cam)
	{
		Cam->GetCameraView(DeltaTime, OutResult);
		OutResult.Location += CrouchEyeOffSet;
	}
	
	//Super::CalcCamera(DeltaTime, OutResult);
}

void APlayerCharacter::HoldThings(float AxisValue)
{
	if (Grabber != nullptr)
	{
		if (AxisValue == 1)
		{

			Grabber->Grab();
		}
		else
		{
			Grabber->Release();
		}
	}
	
	
}


