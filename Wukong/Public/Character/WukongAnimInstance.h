// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WukongAnimInstance.generated.h"

// Declarations
class AWukongCharacter;

/**
 * 
 */
UCLASS()
class WUKONG_API UWukongAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	// Used in animation blueprint
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	// We can initialize our variables and be able to use them in BP
	virtual void NativeInitializeAnimation() override;

private:

	// Create variable to have reference to Wukong character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	AWukongCharacter* WukongCharacter;

	// Speed of Wukong
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float Speed;

	// Movement offset yaw to be used in anim instance blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement", meta=(AllowPrivateAccess="true"))
	float MovementOffsetYaw;
};
