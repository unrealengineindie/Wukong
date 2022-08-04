// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NotifyStateRightWeapon.h"

void UNotifyStateRightWeapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Notify Begin"));
}

void UNotifyStateRightWeapon::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Notify End"));
}
