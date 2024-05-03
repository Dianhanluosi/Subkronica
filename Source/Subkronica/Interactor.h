// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interactor.generated.h"

class AClickableMother;
class UGrabber;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBKRONICA_API UInteractor : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AClickableMother* Clickable = nullptr;

	UFUNCTION(BlueprintCallable)
	void IsLooking();

	UFUNCTION(BlueprintCallable)
	void StopLooking();

private:
	UPROPERTY(EditAnywhere)
	float MaxClickDistance = 400;

	UPROPERTY(EditAnywhere)
	float ClickRadius = 0;
	
	class UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetGrabbableInReach(FHitResult& OutHitResult) const;

	bool IsItemInView() const;
	
	UGrabber* Grabber = nullptr;
	
};
