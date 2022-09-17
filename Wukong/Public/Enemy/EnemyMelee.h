// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
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

protected:

	// Melee attack montage
	void MeleeAttack();

	// Used after disabling movement
	void ResetMovementWalking();

	FName GetAttackSectionName(int32 SectionCount);
	
private:
	// Montage for melee attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess = "true"))
	UAnimMontage* MeleeAttackMontage;

	// Timer for playing attack montage
	FTimerHandle TimerAttack;

	// @TODO remove when behavior tree is working
	UFUNCTION(BlueprintCallable)
	void MainMeleeAttack();
};
