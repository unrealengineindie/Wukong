// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Notify/EnemyLeftWeapon.h"

#include "Enemy/EnemyMelee.h"

void UEnemyLeftWeapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyMelee = Cast<AEnemyMelee>(MeshComp->GetOwner());
		if (EnemyMelee)
		{
			EnemyMelee->ActivateLeftWeapon();
		}
	}
}

void UEnemyLeftWeapon::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyMelee = Cast<AEnemyMelee>(MeshComp->GetOwner());
		if (EnemyMelee)
		{
			EnemyMelee->DeactivateLeftWeapon();
		}
	}
}
