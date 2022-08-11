// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NotifyStateRightWeapon.h"

void UNotifyStateRightWeapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		WukongCharacter = Cast<AWukongCharacter>(MeshComp->GetOwner());
		if (WukongCharacter)
		{
			WukongCharacter->ActivateRightWeapon();
		}
	}
}

void UNotifyStateRightWeapon::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		if (WukongCharacter)
		{
			WukongCharacter->DeactivateRightWeapon();
		}
	}
}
