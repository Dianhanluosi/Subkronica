// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainController.h"
#include "PowerPlantSpinner.h"
#include "Components/StaticMeshComponent.h"
#include "TrainSwitch.h"
#include "TrainIgnition.h"
#include "Components/AudioComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ATrainController::ATrainController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));

	DetectionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionBox"));
	DetectionBox->SetupAttachment(RootComponent);
	DetectionBox->SetCollisionProfileName(TEXT("Trigger"));

}

// Called when the game starts or when spawned
void ATrainController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	DetectionBox->OnComponentBeginOverlap.AddDynamic(this, &ATrainController::OnPlayerEnter);
	DetectionBox->OnComponentEndOverlap.AddDynamic(this, &ATrainController::OnPlayerExit);
	
	
}

// Called every frame
void ATrainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AudioComponent && OnSound && OffSound)
	{
		if (HasPower && !OnPlayed)
		{
			AudioComponent->Stop();
			AudioComponent->SetSound(OnSound);
			AudioComponent->Play();
			OnPlayed = true;
			OffPlayed = false;
		}
		else if (!HasPower && !OffPlayed)
		{
			AudioComponent->Stop();
			AudioComponent->SetSound(OffSound);
			AudioComponent->Play();
			OffPlayed = true;
			OnPlayed = false;
		}
	}

	if (HasPower)
	{
		if (bGo)
		{
			Go(DeltaTime);
		}
		else
		{
			Stop();
		}
	}
	else
	{
		Stop();
	}
	
	

}

void ATrainController::Go(float DeltaTime)
{
	// if (bPlayerIn)
	// {
	// 	if (PlayerCharacter)
	// 	{
	// 		PlayerCharacter->GetRootComponent()->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	// 	}
	// }
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);
	
}

void ATrainController::Stop()
{
	// if (PlayerCharacter)
	// {
	// 	if (PlayerCharacter->GetRootComponent() && PlayerCharacter->GetRootComponent()->GetAttachParent()
	// 		&& PlayerCharacter->GetRootComponent()->GetAttachParent() == GetRootComponent())
	// 	{
	// 		PlayerCharacter->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	// 	}
	// }
}

void ATrainController::OnPlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("Overlap began with: %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		bPlayerIn = true;
		UE_LOG(LogTemp, Error, TEXT("Player has entered the detection box."));
	}
}

void ATrainController::OnPlayerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Error, TEXT("Overlap ended with: %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		bPlayerIn = false;
		UE_LOG(LogTemp, Error, TEXT("Player has exited the detection box."));
	}
}

