// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterplantWheel.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraActor.h"
#include "NiagaraFunctionLibrary.h"
#include "PowerPlantSpinner.h"
#include "Engine/SpotLight.h"
#include "Components/SpotLightComponent.h"

AWaterplantWheel::AWaterplantWheel()
{
	PrimaryActorTick.bCanEverTick = true;

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelMesh"));
	RootComponent = WheelMesh;

	WheelSound = CreateDefaultSubobject<UAudioComponent>(TEXT("WheelSound"));
	//WaterSound = CreateDefaultSubobject<UAudioComponent>(TEXT("WaterSound"));
}

void AWaterplantWheel::BeginPlay()
{
	Super::BeginPlay();

	//WheelSound = FindAudioComponentByName(this, TEXT("WheelSound"));
	//WaterSound = FindAudioComponentByName(this, TEXT("WaterSound"));

	if (WaterPlane)
	{
		WaterPlane->SetActorLocation(WaterPlaneStart);
	}

	// if (WaterSound)
	// {
	// 	WaterSound->Play();
	// }
	
	
}

void AWaterplantWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SwitchedOn)
	{
		for (ANiagaraActor* Waterfall : Waterfalls)
		{
			if (Waterfall && Waterfall->GetNiagaraComponent())
			{
				//UE_LOG(LogTemp, Error, TEXT("Action"));
				Waterfall->GetNiagaraComponent()->SetVisibility(true);
			}
		}

		if (WaterPlane)
		{
			FVector CurrentLocation = WaterPlane->GetActorLocation();
			CurrentLocation.Z += WaterRiseRate * DeltaTime;
			WaterPlane->SetActorLocation(CurrentLocation);
		}
		
	}
	else
	{
		for (ANiagaraActor* Waterfall : Waterfalls)
		{
			if (Waterfall && Waterfall->GetNiagaraComponent())
			{
				//Waterfall->GetNiagaraComponent()->Deactivate();
				Waterfall->GetNiagaraComponent()->SetVisibility(false);

			}
		}
	}

	if (Spinner)
	{
		if (Spinner->IsOn)
		{
			if (WaterPlane)
			{
				FVector CurrentLocation = WaterPlane->GetActorLocation();
				CurrentLocation.Z -= WaterFallRate * DeltaTime;
				WaterPlane->SetActorLocation(CurrentLocation);
			}
		}
	}
	
	if (WaterPlane)
	{
		FVector PlaneLocation = WaterPlane->GetActorLocation();

		if (PlaneLocation.Z >= WaterPlaneEnd.Z)
		{
			EnoughWater = true;
			WaterPlane->SetActorLocation(WaterPlaneEnd);
		}
		else
		{
			EnoughWater = false;
		}

		if (PlaneLocation.Z <= WaterPlaneStart.Z)
		{
			WaterPlane->SetActorLocation(WaterPlaneStart);
			
			NoWater = true;
			for (ASpotLight* CausticsLight : CausticsLights)
			{
				if (CausticsLight && CausticsLight->GetLightComponent())
				{
					CausticsLight->GetLightComponent()->SetVisibility(false); // Activate the light
					CausticsLight->GetLightComponent()->SetHiddenInGame(true); // Ensure it's not hidden in the game
				}
			}
			

			

			if (Spinner)
			{
				Spinner->IsCooling = false;
			}
		}
		else
		{
			NoWater = false;
			for (ASpotLight* CausticsLight : CausticsLights)
			{
				if (CausticsLight && CausticsLight->GetLightComponent())
				{
					CausticsLight->GetLightComponent()->SetVisibility(true); // Activate the light
					CausticsLight->GetLightComponent()->SetHiddenInGame(false); // Ensure it's not hidden in the game
				}
			}
			if (Spinner)
			{
				Spinner->IsCooling = true;
			}
		}
	}

	if (EnoughWater && SwitchedOn)
	{
		SelfTurnOff();
	}

	UpdateRotation(DeltaTime);
	
	
}

void AWaterplantWheel::Action()
{
	Super::Action();

	SwitchedOn = !SwitchedOn;
	
	if (WheelSound)
	{
		if (WheelSoundClip1)
		{
			WheelSound->SetSound(WheelSoundClip1);
			WheelSound->Play();
		}
	}

	
	
}

void AWaterplantWheel::UpdateRotation(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	FRotator TargetRotation = SwitchedOn? OnRotation : OffRotation;

	float LerpStep = SwitchSpeed * DeltaTime;

	FRotator NewRotation = FMath::Lerp(CurrentRotation, TargetRotation, LerpStep);

	SetActorRotation(NewRotation);	
}

void AWaterplantWheel::SelfTurnOff()
{
	SwitchedOn = false;

	STO();
	
	// if (WheelSound)
	// {
	// 	if (WheelSoundClip1)
	// 	{
	// 		WheelSound->SetSound(WheelSoundClip2);
	// 		WheelSound->Play();
	// 	}
	// }
}

UAudioComponent* AWaterplantWheel::FindAudioComponentByName(AActor* Actor, const FName& ComponentName)
{
	if (!Actor)
	{
		return nullptr;
	}

	// Iterate through all components of type UAudioComponent
	TArray<UAudioComponent*> Components;
	Actor->GetComponents<UAudioComponent>(Components);
	for (UAudioComponent* Component : Components)
	{
		// Check if the component's name matches the specified name
		if (Component->GetFName() == ComponentName)
		{
			return Component;
		}
	}

	return nullptr; 
}
