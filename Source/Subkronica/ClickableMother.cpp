// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableMother.h"
#include "Interactor.h"

// Sets default values
AClickableMother::AClickableMother()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClickableMother::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* RootMeshComponent = Cast<UStaticMeshComponent>(GetRootComponent());

	if (RootMeshComponent)
	{
		RootMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Block);

	}
	
}

// Called every frame
void AClickableMother::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT(" %d"), LookedAt);
	
}

void AClickableMother::Action()
{
	UE_LOG(LogTemp, Warning, TEXT("Action"));

}

