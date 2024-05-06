// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEndingManager::AEndingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndingManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	// if (PlayerController)
	// {
	// 	PlayerController->SetInputMode(FInputModeUIOnly()); // Switches input mode to UI only, no game input
	// 	PlayerController->bShowMouseCursor = true; // Optionally show the cursor for UI interaction
	// 	PlayerController->UnPossess();
	// }
		

}

void AEndingManager::ReceiveEndingNumber(int EndingNumber)
{
	if (!EndingTrigger)
	{
		switch (EndingNumber)
		{
		case 1:
			UE_LOG(LogTemp, Error, TEXT("Escaped Through the Train."));
			break;
		case 2:
			UE_LOG(LogTemp, Error, TEXT("Stuck Here Forever."));
			break;
		case 3:
			UE_LOG(LogTemp, Error, TEXT("Nuclear Explosion."));
			break;
		case 4:
			UE_LOG(LogTemp, Error, TEXT("You're Obliterated By The Reactor."));
			break;
		case 5:
			UE_LOG(LogTemp, Error, TEXT("You Accidentally Shot Yourself."));
			break;
		case 6:
			UE_LOG(LogTemp, Error, TEXT("A Day Has Passed, Time Has Reset, Start Over."));
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("No Ending Number Received."));
			break;
		}

		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->SetInputMode(FInputModeUIOnly()); // Switches input mode to UI only, no game input
			PlayerController->bShowMouseCursor = true; // Optionally show the cursor for UI interaction
			PlayerController->UnPossess();
		}
		



		EndingTrigger = true;
	}
	
}

