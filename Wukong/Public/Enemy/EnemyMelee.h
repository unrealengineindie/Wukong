// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Components/BoxComponent.h"
#include "EnemyMelee.generated.h"

// Declarations
class UAnimMontage;

/**
 * 
 */
UCLASS()
class WUKONG_API AEnemyMelee : public AEnemy
{
	GENERATED_BODY()

public:

	AEnemyMelee();

	// Activate and deactivate weapon boxes
	virtual void ActivateRightWeapon();
	virtual void DeactivateRightWeapon();
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Melee attack montage
	void MeleeAttack();

	// Used after disabling movement
	void ResetMovementWalking();

	FName GetAttackSectionName(int32 SectionCount);

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
	// Montage for melee attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess = "true"))
	UAnimMontage* MeleeAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	UBoxComponent* RightWeaponCollision;
	
	// Timer for playing attack montage
	FTimerHandle TimerAttack;

	// @TODO remove when behavior tree is working
	UFUNCTION(BlueprintCallable)
	void MainMeleeAttack();
};
