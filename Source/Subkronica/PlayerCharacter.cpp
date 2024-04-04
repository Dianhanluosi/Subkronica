// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Follow Camera
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Cam->SetupAttachment(RootComponent); // Attach the camera to the end of the swing arm

	CamShake = nullptr;
	
	//GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveSpeed = WalkingSpeed;

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
	
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
	UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f units/s"), Speed);

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

	PlayerInputComponent->BindAxis(*Hold, this, &APlayerCharacter::HoldThings);

	PlayerInputComponent->BindAction(*Jumping, EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::CrouchCtrl);
	

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
	if (AxisValue == 1 && !bIsCrouching)
	{
		MoveSpeed = RunningSpeed;
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
		GetCharacterMovement()->JumpZVelocity = RunningJumpSpeed;

	}
	else if (!bIsCrouching)
	{
		MoveSpeed = WalkingSpeed;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		GetCharacterMovement()->JumpZVelocity = WalkingJumpSpeed;

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
	if(!bIsCrouching)
	{
		Crouch();
		bIsCrouching = true;
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
		GetCharacterMovement()->JumpZVelocity = 0;
	}
	else
	{
		UnCrouch();
		bIsCrouching = false;
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		GetCharacterMovement()->JumpZVelocity = WalkingJumpSpeed;
	}
}

void APlayerCharacter::HoldThings(float AxisValue)
{
}


