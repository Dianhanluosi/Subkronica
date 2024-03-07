// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Follow Camera
	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Cam->SetupAttachment(RootComponent); // Attach the camera to the end of the swing arm

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MoveSpeed = WalkingSpeed;
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	PlayerInputComponent->BindAction(*Jumping, EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void APlayerCharacter::MoveFowardCtrl(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
	UE_LOG(LogTemp, Log, TEXT("MoveSpeed: %f"), MoveSpeed);
}

void APlayerCharacter::MoveRightCtrl(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
	UE_LOG(LogTemp, Log, TEXT("MoveSpeed: %f"), MoveSpeed);
}

void APlayerCharacter::SprintCtrl(float AxisValue)
{
	if (AxisValue == 1)
	{
		MoveSpeed = RunningSpeed;
	}
	else
	{
		MoveSpeed = WalkingSpeed;
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


