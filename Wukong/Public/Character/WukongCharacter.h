// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WukongCharacterInterface.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "WukongCharacter.generated.h"

// Declarations
class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

UCLASS()
class WUKONG_API AWukongCharacter : public ACharacter, public IWukongCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWukongCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Activate and deactivate weapon boxes
	virtual void ActivateRightWeapon();
	virtual void DeactivateRightWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Move forward and backward
	void MoveForward(float Value);

	// Move left and right
	void MoveRight(float Value);

	// Input to turn at normalized rate given
	void TurnRate(float Rate);

	// Input to lookup or down at normalized rate given
	void LookUpRate(float Rate);

	// Running and stop running
	void Running();
	void StopRunning();

	// Recall ability
	void Recall();

	// Play animation montage that disable movement
	void PlayAnimMontage(UAnimMontage* MontageToPlay, FName SectionName = "Default");
	
	// Set character movement back to walking
	void EnableWalk();

	// LMB main attack
	void MainAttack();

	// Right weapon overlap
	UFUNCTION()
	void OnRightWeaponOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
private:

	// Spring Arm Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmComponent;

	// Follow Camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCameraComponent;

	// Default turn rate 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	float DefaultTurnRate;

	// Default lookup rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	float DefaultLookUpRate;

	// Set walk speed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess="true"))
	float WalkSpeed;

	// Set run speed
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess="true"))
	float RunSpeed;

	// Timer handle to disable character movement used with montages.
	FTimerHandle TimerMovementWalking;
	
    // Recall montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Montage", meta=(AllowPrivateAccess="true"))
	UAnimMontage* RecallMontage;

    // Main attack montage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Montage", meta=(AllowPrivateAccess="true"))
	UAnimMontage* MainAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	UBoxComponent* RightWeaponCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	float BaseDamage;
};
