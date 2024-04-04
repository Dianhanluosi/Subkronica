// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h" 
#include "InteractableMother.h"
#include "DrawDebugHelpers.h"
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

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();

	

	if (PhysicsHandle && PhysicsHandle-> GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	

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
		Hitcomponent->SetSimulatePhysics(true);
		Hitcomponent-> WakeAllRigidBodies();
		AActor* HitActor = HitResult.GetActor();
		HitActor-> Tags.Add("Grabbed");
		HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		//HitResult.GetActor()->Tags.Add("Grabbed");
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			Hitcomponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);


		
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Blue, false, 5);
		//DrawDebugSphere(GetWorld(),HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		//AActor* HitActor = HitResult.GetActor();
		//HitResult.
		//UE_LOG(LogTemp, Display, TEXT("%s"), *HitResult.GetActor()->GetActorNameOrLabel());

	}
	else
	{
		//UE_LOG(LogTemp, Display, TEXT("No Hit"));
	}

	
	
	
}

void UGrabber::Release()
{
	//UE_LOG(LogTemp, Display, TEXT("Release"));
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();
	
	//if(PhysicsHandle == nullptr)
	//{
	//	return;
	//}

	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor-> Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::LoseGrabbedItem()
{
	UPhysicsHandleComponent* PhysicsHandle =  GetPhysicsHandle();
	/*if(PhysicsHandle == nullptr || PhysicsHandle->GrabbedComponent == nullptr)
	{
		return;
	}*/
	
	
	if(PhysicsHandle && PhysicsHandle->GrabbedComponent && FVector::Dist(PhysicsHandle->GrabbedComponent->GetComponentLocation(), GetComponentLocation()) >= (MaxGrabDistance + LoseDistance))
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor-> Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
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

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	//DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1,Sphere);

	

}


