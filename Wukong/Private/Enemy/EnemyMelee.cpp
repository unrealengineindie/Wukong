// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyMelee.h"

#include "GameFramework/CharacterMovementComponent.h"

AEnemyMelee::AEnemyMelee()
{
	
}

// Enemy melee attack montage
void AEnemyMelee::MeleeAttack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	
	if (AnimInstance && MeleeAttackMontage)
	{
		// get number of montage section
		int32 const SectionCount = MeleeAttackMontage->CompositeSections.Num();

		// Get random animation to play
		// Get section index and playtime to use for the timer
		FName const SectionName = GetAttackSectionName(SectionCount);
		int32 const SectionIndex = MeleeAttackMontage->GetSectionIndex(SectionName);
		float const SectionLength = MeleeAttackMontage->GetSectionLength(SectionIndex);

		// Disable enemy movement then re-enable after timer finishes
		GetCharacterMovement()->DisableMovement();

		// Play montage section
		AnimInstance->Montage_Play(MeleeAttackMontage);
		AnimInstance->Montage_JumpToSection(SectionName, MeleeAttackMontage);
		GetWorldTimerManager().SetTimer(TimerAttack, this, &AEnemyMelee::ResetMovementWalking, SectionLength);
	}
}

void AEnemyMelee::ResetMovementWalking()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

// Get random attack section name
FName AEnemyMelee::GetAttackSectionName(int32 SectionCount)
{
	FName SectionName;

	// Get random section in montage
	const int32 Section{ FMath::RandRange(1, SectionCount) };

	switch (Section)
	{
	case 1:
		SectionName = FName("Attack1");
		break;
	case 2:
		SectionName = FName("Attack2");
		break;
	}

	return SectionName;
}

// @TODO Refactor this when doing behavior tree
// Called from enemy blueprint
void AEnemyMelee::MainMeleeAttack()
{
	// Logic to run anim montage attack from section
	MeleeAttack();
}
