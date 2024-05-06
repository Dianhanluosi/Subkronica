// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickableMother.h"
#include "Interactor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

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

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	SetPrompt();
	
	if (LookedAt)
	{
		PromptType = 1;

	}
	else if (PlayerCharacter && PlayerCharacter->FindComponentByClass<UInteractor>() &&
		FVector::Dist(GetActorLocation(),
			PlayerCharacter->FindComponentByClass<UInteractor>()->GetComponentLocation())
			<= (PlayerCharacter->FindComponentByClass<UInteractor>()->MaxClickDistance)*2)
	{
		PromptType = 2;
	}
	else
	{
		PromptType = 0;
	}
	
}

void AClickableMother::Action()
{
	UE_LOG(LogTemp, Warning, TEXT("Action"));

}

