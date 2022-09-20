// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Notify/EnemyRightWeapon.h"

#include "Enemy/EnemyMelee.h"

void UEnemyRightWeapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyMelee = Cast<AEnemyMelee>(MeshComp->GetOwner());
		if (EnemyMelee)
		{
			EnemyMelee->ActivateRightWeapon();
		}
	}
}

void UEnemyRightWeapon::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		EnemyMelee = Cast<AEnemyMelee>(MeshComp->GetOwner());
		if (EnemyMelee)
		{
			EnemyMelee->DeactivateRightWeapon();
		}
	}
}
