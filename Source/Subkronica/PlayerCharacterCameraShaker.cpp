// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterCameraShaker.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

UPlayerCharacterCameraShaker::UPlayerCharacterCameraShaker()
{
	// OscillationDuration = -1.0f;
	// OscillationBlendInTime = 0.1f;
	// OscillationBlendOutTime = 0.2f;
	//
	// RotOscillation.Pitch.Amplitude = 25.0f;
	// RotOscillation.Pitch.Frequency = 2.0f;
	// RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	// RotOscillation.Pitch.Waveform = EOscillatorWaveform::PerlinNoise;
	//
	// LocOscillation.Y.Amplitude = 5.0f;
	// LocOscillation.Y.Frequency = 1.0f;
	// LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	// LocOscillation.Y.Waveform = EOscillatorWaveform::PerlinNoise;
	//
	// LocOscillation.Z.Amplitude = 5.0f;
	// LocOscillation.Z.Frequency = 1.0f;
	// LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	// LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;


	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();
		if (MovementComponent)
		{
			if (MovementComponent->MaxWalkSpeed == PlayerCharacter->WalkingSpeed)
			{
				OscillationDuration = -1.0f; // Continuous shake
				OscillationBlendInTime = 0.1f; // Smooth, quick start
				OscillationBlendOutTime = 0.2f; // Smooth, quick end

				// Rotational Oscillation (Enhance this a bit for walking)
				RotOscillation.Pitch.Amplitude = 2.0f; // Slightly more noticeable pitch movement
				RotOscillation.Pitch.Frequency = 0.8f; // Adjust for a natural feel, not too fast
				RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
				RotOscillation.Pitch.Waveform = EOscillatorWaveform::PerlinNoise; // Smooth natural movement

				// Lateral (Y) Oscillation (Enhance sideways shake for walking)
				LocOscillation.Y.Amplitude = 0.4f; // More noticeable side to side movement
				LocOscillation.Y.Frequency = 0.8f; // Adjusted for a more natural movement rhythm
				LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
				LocOscillation.Y.Waveform = EOscillatorWaveform::PerlinNoise;

				// Vertical (Z) Oscillation (Enhance this for a more pronounced 'bob')
				LocOscillation.Z.Amplitude = 1.0f; // More noticeable up and down movement
				LocOscillation.Z.Frequency = 2.0f; // Adjusted to better match the pace of walking
				LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
				LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;

			}
			else if (MovementComponent->MaxWalkSpeed == PlayerCharacter->RunningSpeed)
			{
				OscillationDuration = -1.0f;
				OscillationBlendInTime = 0.1f;
				OscillationBlendOutTime = 0.2f;
				
				RotOscillation.Pitch.Amplitude = 25.0f;
				RotOscillation.Pitch.Frequency = 2.0f;
				RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
				RotOscillation.Pitch.Waveform = EOscillatorWaveform::PerlinNoise;
				
				LocOscillation.Y.Amplitude = 5.0f;
				LocOscillation.Y.Frequency = 1.0f;
				LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
				LocOscillation.Y.Waveform = EOscillatorWaveform::PerlinNoise;
				
				LocOscillation.Z.Amplitude = 5.0f;
				LocOscillation.Z.Frequency = 1.0f;
				LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
				LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;

			}
		}
	}
	
	// OscillationDuration = -1.0f; // Continuous shake
	// OscillationBlendInTime = 0.1f; // Smooth, quick start
	// OscillationBlendOutTime = 0.2f; // Smooth, quick end
	//
	// // Rotational Oscillation (You might want to minimize or eliminate this for walking)
	// RotOscillation.Pitch.Amplitude = 1.0f; // Very subtle pitch movement
	// RotOscillation.Pitch.Frequency = 0.5f; // Slower, to not induce motion sickness
	// RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	// RotOscillation.Pitch.Waveform = EOscillatorWaveform::PerlinNoise; // Smooth natural movement
	//
	// // Lateral (Y) Oscillation (Sideways shake - might be very subtle or none for walking)
	// LocOscillation.Y.Amplitude = 0.2f; // Very subtle side to side movement
	// LocOscillation.Y.Frequency = 0.5f; // Slower, more natural for walking
	// LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	// LocOscillation.Y.Waveform = EOscillatorWaveform::PerlinNoise;
	//
	// // Vertical (Z) Oscillation (This is where most of the walking 'bob' would come from)
	// LocOscillation.Z.Amplitude = 0.5f; // Subtle up and down movement
	// LocOscillation.Z.Frequency = 1.5f; // Adjust to match the pace of walking
	// LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetZero;
	// LocOscillation.Z.Waveform = EOscillatorWaveform::PerlinNoise;
	
}
