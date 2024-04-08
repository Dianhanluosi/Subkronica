// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"
#include "ClickableMother.h"
#include "Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UInteractor::UInteractor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Grabber = GetOwner()->FindComponentByClass<UGrabber>();

	
	
}


// Called every frame
void UInteractor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IsLooking();
	StopLooking();
	
	// ...
}

void UInteractor::IsLooking()
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

		if (!Clickable && !Grabber->Interactable)
		{
			Clickable = Cast<AClickableMother>(HitActor);
			if (GetOwner())
			{
				Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Clickable = Clickable;
			}
		}
		if (Clickable)
		{
			Clickable->LookedAt = true;
		}

	}
}

void UInteractor::StopLooking()
{
	if (Clickable && Grabber->Interactable ||
		Clickable && FVector::Dist(Clickable->GetActorLocation(), GetComponentLocation()) >= MaxClickDistance ||
		Clickable && !IsItemInView())
	{
		Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Clickable = nullptr;
		Clickable->LookedAt = false;
		Clickable = nullptr;
		
	}
}

UPhysicsHandleComponent* UInteractor::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result =  GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber required a UPhysicsHandleComponent"));
	}
	return Result;
}

bool UInteractor::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxClickDistance;

	FCollisionShape Sphere = FCollisionShape::MakeSphere(ClickRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2,Sphere);

	

}

bool UInteractor::IsItemInView() const
{
	if (!Clickable) return false;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return false;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector ToItem = Clickable->GetActorLocation() - PlayerViewPointLocation;
	
	ToItem.Normalize();

	FVector PlayerViewPointDirection = PlayerViewPointRotation.Vector();

	float DotProduct = FVector::DotProduct(PlayerViewPointDirection, ToItem);

	DotProduct = FMath::Clamp(DotProduct, -1.0f, 1.0f);
	float AngleRadians = FMath::Acos(DotProduct);
	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);


	const float PlayerFOV =	PlayerController->PlayerCameraManager->GetFOVAngle();

	return AngleDegrees <= PlayerFOV / 2;
	
}

