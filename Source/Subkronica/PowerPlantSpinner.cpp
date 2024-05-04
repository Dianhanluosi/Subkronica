// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerPlantSpinner.h"
#include "TimerManager.h"

// Sets default values
APowerPlantSpinner::APowerPlantSpinner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpinnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpinnerMesh"));

	RootComponent = SpinnerMesh;

}

// Called when the game starts or when spawned
void APowerPlantSpinner::BeginPlay()
{
	Super::BeginPlay();

	Temp = MinimumTemp;
	
}

// Called every frame
void APowerPlantSpinner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateRotation(DeltaTime);

	if (Temp < MinimumTemp)
	{
		Temp = MinimumTemp;
	}
	
	if (IsSpinning)
	{
		Temp += TempRiseRate * DeltaTime;
	}
	else
	{
		Temp -= TempFallRate * DeltaTime;
	}
	if (IsCooling)
	{
		Temp -= TempCoolingRate * DeltaTime;
	}

	if (Temp >= TerminalTemp)
	{
		IsOverHeating = true;
	}
	else
	{
		IsOverHeating = false;
	}

	ControlCountdown();
	
}

void APowerPlantSpinner::UpdateRotation(float DeltaTime)
{
	float Direction = IsOn? 1.0f : -1.0f;

	RotationSpeed += Direction *= RotationAcceleration * DeltaTime;

	RotationSpeed = FMath::Clamp(RotationSpeed,0.0f, TerminalRotationSpeed);

	IsSpinning  = RotationSpeed != 0.0f;
	
	if (IsSpinning)
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += RotationSpeed * DeltaTime;
		SetActorRotation(NewRotation);
	} 
}

void APowerPlantSpinner::ControlCountdown()
{
	if (IsOverHeating)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(CountdownTimerHandle))
		{
			UE_LOG(LogTemp, Error, TEXT("Start"));
			CountdownRemaining = OverHeatCountdown;
			GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle,
				this, &APowerPlantSpinner::HandleCountdown, 1.0f, true);
		}
		// else
		// {
		// 	UE_LOG(LogTemp, Error, TEXT("End"));
		// 	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		// 	CountdownRemaining = OverHeatCountdown;
		// }
	}
	else
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(CountdownTimerHandle))
		{
			UE_LOG(LogTemp, Error, TEXT("End"));
			GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
			CountdownRemaining = OverHeatCountdown;
		}
		
	}
}

void APowerPlantSpinner::HandleCountdown()
{
	if (CountdownRemaining > 0)
	{
		CountdownRemaining--;
		UE_LOG(LogTemp, Error, TEXT("Countdown: %f seconds remaining"), CountdownRemaining);

	}
	else
	{
		Explosion = true;
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
		UE_LOG(LogTemp, Error, TEXT("Countdown finished!"));
	}
		
}

