// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h" 
#include "InteractableMother.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("Interactable Pointer: %p"), Interactable)

	LoseGrabbedItem();
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();

	if (PhysicsHandle == nullptr)
	{
		return;
	}
	
	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit)
	{
		UPrimitiveComponent* Hitcomponent = HitResult.GetComponent();
		
		AActor* HitActor = HitResult.GetActor();
		if (!HitActor) return;

		if (!Interactable)
		{
			Interactable = Cast<AInteractableMother>(HitActor);
		}
		if (Interactable)
		{
			Interactable->Grabbed = true;
		}

	}
	

	
	
	
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();
	
	

	if (Interactable)
	{
		Interactable->Grabbed = false;
		Interactable = nullptr;
	}
	
	
}

void UGrabber::LoseGrabbedItem()
{
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();
	
	
	
	if(Interactable && FVector::Dist(Interactable->GetActorLocation(), GetComponentLocation()) >= (MaxGrabDistance + LoseDistance) || Interactable && !IsItemInView())
	{
		Interactable->Grabbed = false;
		Interactable = nullptr;
		
	}
}


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber required a UPhysicsHandleComponent"));
	}
	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1,Sphere);

	

}

bool UGrabber::IsItemInView() const
{
	if (!Interactable) return false;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return false;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector ToItem = Interactable->GetActorLocation() - PlayerViewPointLocation;
	ToItem.Normalize();

	FVector PlayerViewPointDirection = PlayerViewPointRotation.Vector();

	float DotProduct = FVector::DotProduct(PlayerViewPointDirection, ToItem);

	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	float AngleRadians = FMath::Acos(DotProduct);
	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);


	const float PlayerFOV =	PlayerController->PlayerCameraManager->GetFOVAngle();

	return AngleDegrees <= PlayerFOV / 2;
	
}


