// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeySocket.generated.h"

UCLASS()
class SUBKRONICA_API AKeySocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeySocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	class AKeys* Key;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float RotationSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bRotating;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bKeyInserted;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* KeyHole;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* KeyMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FRotator EndRotation;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnKeyInserted();
	
};
