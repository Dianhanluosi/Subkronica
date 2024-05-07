// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableMother.generated.h"

UCLASS()
class SUBKRONICA_API AInteractableMother : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableMother();

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool Grabbed = false;

	UPROPERTY(EditDefaultsOnly)
	bool PickedUp = false;

	//Pick up control
	virtual void Holding();
	virtual void letGo();

	virtual void Action();
	virtual void Shoot();


	class APlayerController* PlayerController = nullptr;
	class APlayerCharacter* Player = nullptr;
	class UCameraComponent* PlayerCam = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Spawnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OriginalZ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZBobOffset = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZBobSpeed = 4.f;

	UFUNCTION(BlueprintCallable)
	void Bobbing();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LookedAt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PromptType;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetPrompt();
	
};
