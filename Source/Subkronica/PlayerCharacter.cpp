// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/ITargetDevice.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/CapsuleComponent.h"
#include "InteractableMother.h"
#include "ClickableMother.h"
#include "Grabber.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"

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

	PeeEmitter = CreateDefaultSubobject<USceneComponent>(TEXT("PeeEmitter"));
	PeeEmitter->SetupAttachment(RootComponent);

	PeeParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PeeParticle"));
	PeeParticle->SetupAttachment(PeeEmitter);
	
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
	CrouchHeight = OriginalHeight * CrouchRatio;

	Grabber = FindComponentByClass<UGrabber>();

	
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// if (GetCapsuleComponent())
	// {
	// 	float HalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	//
	// 	// Log the half-height to the console
	// 	UE_LOG(LogTemp, Warning, TEXT("Capsule Half-Height: %f"), HalfHeight);
	// }

	// if (Cam)
	// {
	// 	FVector CameraLocation = Cam->GetComponentLocation();
	// 	//UE_LOG(LogTemp, Warning, TEXT(" %f"), BaseEyeHeight);
	// 	UE_LOG(LogTemp, Warning, TEXT(" %f"), CameraLocation.Z);	
	// }

	// if (Cam)
	// {
	// 	FVector CameraLocation = Cam->GetRelativeLocation();
	// 	//UE_LOG(LogTemp, Warning, TEXT(" %f"), BaseEyeHeight);
	// 	UE_LOG(LogTemp, Warning, TEXT(" %f"), CameraLocation.Z);	
	// }

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		EMovementMode CurrentMode = MovementComponent->MovementMode; // Retrieve current movement mode
        
		// Example: Log current movement mode
		//UE_LOG(LogTemp, Log, TEXT("Current Movement Mode: %d"), static_cast<int32_t>(CurrentMode));
	
		
	}

	
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

	
	ClimbCtrl(IsClimbing);

	if (bIsCrouching)
	{
		MoveSpeed = CrouchWalkingSpeed;
		GetCharacterMovement()->MaxWalkSpeed = CrouchWalkingSpeed;
		GetCharacterMovement()->JumpZVelocity = 0;
	}
	else if (IsClimbing)
	{
		MoveSpeed = ClimbingSpeed;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		GetCharacterMovement()->MaxFlySpeed = ClimbingSpeed;
		GetCharacterMovement()->JumpZVelocity = 0;
	}
	else if (!IsRunning)
	{
		MoveSpeed = WalkingSpeed;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		GetCharacterMovement()->JumpZVelocity = WalkingJumpSpeed;
	}
	else
	{
		MoveSpeed = RunningSpeed;
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
		GetCharacterMovement()->JumpZVelocity = RunningJumpSpeed;
	}

	//crouch transition setup
	// float CroucHInterpTime = FMath::Min(1.f, CrouchSpeed * DeltaTime);
	// CrouchEyeOffSet = (1.f - CroucHInterpTime) * CrouchEyeOffSet;

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(*MoveForward, this, &APlayerCharacter::MoveFowardCtrl);
	PlayerInputComponent->BindAxis(*MoveRight, this, &APlayerCharacter::MoveRightCtrl);

	if (!IsClimbing)
	{
		PlayerInputComponent->BindAxis(*Sprint, this, &APlayerCharacter::SprintCtrl);
	}
		
	PlayerInputComponent->BindAxis(*LookUp, this, &APlayerCharacter::LookUpCtrl);
	PlayerInputComponent->BindAxis(*TurnRight, this, &APlayerCharacter::TurnRightCtrl);

	if (!IsClimbing)
	{
		PlayerInputComponent->BindAction(*Crouching, EInputEvent::IE_Pressed, this, &APlayerCharacter::CrouchCtrl);
		//PlayerInputComponent->BindAxis(*Crouching, this, &APlayerCharacter::CrouchCtrl);
	}

	if (!IsClimbing)
	{
		PlayerInputComponent->BindAxis(*Pee, this, &APlayerCharacter::PeeCtrl);
	}
		
	PlayerInputComponent->BindAction(*Hold, EInputEvent::IE_Pressed, this, &APlayerCharacter::HoldThings);
	PlayerInputComponent->BindAction(*Hold, EInputEvent::IE_Released, this, &APlayerCharacter::LetGoOfThings);

	if (!IsClimbing)
	{
		PlayerInputComponent->BindAction(*Jumping, EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	}
	PlayerInputComponent->BindAction(*LeftClick, EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction(*RightClick, EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);

	
	

}

FVector APlayerCharacter::GetCharacterScale()
{
	return GetActorScale3D();
}

void APlayerCharacter::ClimbCtrl(bool bClimb)
{
	 if(bClimb)
	 {
	 	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	 }
	 else
	 {
	}
}

void APlayerCharacter::MoveFowardCtrl(float AxisValue)
{
	if (!IsClimbing)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
	}
	else
	{
		AddMovementInput(GetActorUpVector()  * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
	}
	
	
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


void APlayerCharacter::CrouchCtrl()
{
	if (!bIsCrouching)
	{
		//Crouch();
		OnStartCrouch(CrouchHeight, CrouchHeight * GetCharacterScale().Z);
		bIsCrouching = true;
	}
	else 
	{
		
			OnEndCrouch(CrouchHeight, CrouchHeight * GetCharacterScale().Z);
			bIsCrouching = false;
		
	}
	
}

//crouching stuff
void APlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0)
	{
		return;
	}

	//float StartBaseEyeHeight = BaseEyeHeight;

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule)
	{
		Capsule->SetCapsuleHalfHeight(HalfHeightAdjust, true);
	}
	
	//CrouchEyeOffSet.Z -= StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	//Cam->SetRelativeLocation(FVector(0,0,BaseEyeHeight- (HalfHeightAdjust/CrouchRatio - HalfHeightAdjust)), false);
}

void APlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0)
	{
		return;
	}
	
	//float StartBaseEyeHeight = BaseEyeHeight;
	
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule)
	{
		Capsule->SetCapsuleHalfHeight(HalfHeightAdjust/CrouchRatio, true);
	}
	
	//CrouchEyeOffSet.Z -= StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	//Cam->SetRelativeLocation(FVector(0,0,BaseEyeHeight), false);

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

void APlayerCharacter::HoldThings()
{
	if (Grabber)
	{
		if (!IsHolding)
		{
			Grabber->Grab();
			IsHolding = true;
		}
		
	}
	
	
}

void APlayerCharacter::LetGoOfThings()
{
	if (Grabber)
	{
		
		if (IsHolding)
		{
			Grabber->Release();
			IsHolding = false;
		}
	}
}

void APlayerCharacter::Interact()
{
	if (Interactable)
	{
		Interactable->Action();
	}
	if (!Interactable && Clickable)
	{
		Clickable->Action();
	}
}

void APlayerCharacter::Shoot()
{
	if (Interactable)
	{
		Interactable->Shoot();
		Grabber->Release();
	}
}

void APlayerCharacter::PeeCtrl(float AxisValue)
{
	if (AxisValue == 1)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Peeing!"));
		if (!bIsCrouching)
		{
			if (!IsPeeing)
			{
				IsPeeing = true;
			}
			if (PeeParticle)
			{
				if (!PeeParticle->IsActive())
				{
					PeeParticle->Activate();
				}
			}
		}
		else
		{
			IsPeeing = false;
			if (PeeParticle)
			{
				PeeParticle->Deactivate();
			
			}
		}
	}
	else
	{
		IsPeeing = false;
		if (PeeParticle)
		{
				PeeParticle->Deactivate();
			
		}
		//UE_LOG(LogTemp, Warning, TEXT("Not Peeing!"));
	}
}



