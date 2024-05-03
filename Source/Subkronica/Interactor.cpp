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
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (!PhysicsHandle || !Grabber)
	{
		return;
	}
    
	FHitResult HitResult;
	if (GetGrabbableInReach(HitResult))
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && !Clickable && !Grabber->Interactable)
		{
			Clickable = Cast<AClickableMother>(HitActor);
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (PlayerCharacter)
			{
				PlayerCharacter->Clickable = Clickable;
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
	FHitResult HitResult;
    if (!GetGrabbableInReach(HitResult) || !Clickable ||
        FVector::Dist(Clickable->GetActorLocation(), GetComponentLocation()) >= MaxClickDistance ||
        !IsItemInView())
    {
        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
        if (PlayerCharacter && Clickable)
        {
            PlayerCharacter->Clickable = nullptr;
            Clickable->LookedAt = false;
            Clickable = nullptr;
        }
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

	// FCollisionShape Sphere = FCollisionShape::MakeSphere(ClickRadius);
	// return GetWorld()->SweepSingleByChannel(
	// 	OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2,Sphere);

	// return GetWorld()->LineTraceSingleByChannel(
	// 	OutHitResult, Start, End, ECC_GameTraceChannel2);

	bool bResult = GetWorld()->LineTraceSingleByChannel(
	   OutHitResult, Start, End, ECC_GameTraceChannel2, FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));

	// Draw the debug line
	// FColor LineColor = bResult ? FColor::Green : FColor::Red; // Green if hit, Red if no hit
	// float Duration = 5.0f; // Duration the line should remain visible (in seconds)
	// DrawDebugLine(
	// 	GetWorld(),
	// 	Start,
	// 	End,
	// 	LineColor,
	// 	false,        // bPersistentLines
	// 	Duration,
	// 	0,            // DepthPriority
	// 	5.0f          // Thickness
	// );

	return bResult;
	

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

