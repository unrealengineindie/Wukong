// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WukongAnimInstance.h"

#include "Character/WukongCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Acts like tick for animation. Get speed.
void UWukongAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (WukongCharacter == nullptr)
	{
		WukongCharacter = Cast<AWukongCharacter>(TryGetPawnOwner());
	}

	if (WukongCharacter)
	{
		// Get speed of Wukong from velocity
		FVector Velocity{ WukongCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// Is the player in the air
		bIsInAir = WukongCharacter->GetCharacterMovement()->IsFalling();
		
		// Get offset yaw to player in blend spaces
		FRotator const AimRotation = WukongCharacter->GetBaseAimRotation();
		FRotator const MovementRotation = UKismetMathLibrary::MakeRotFromX(WukongCharacter->GetVelocity());

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
}

// Acts like begin play create reference to Wukong Character
void UWukongAnimInstance::NativeInitializeAnimation()
{
	WukongCharacter = Cast<AWukongCharacter>(TryGetPawnOwner()); 
}
