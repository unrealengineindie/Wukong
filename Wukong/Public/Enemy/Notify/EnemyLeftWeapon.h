// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EnemyLeftWeapon.generated.h"

// Declarations
class AEnemyMelee;

/**
 * 
 */
UCLASS()
class WUKONG_API UEnemyLeftWeapon : public UAnimNotifyState
{
	GENERATED_BODY()

public:

	UPROPERTY()
	AEnemyMelee* EnemyMelee;

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference) override;
};
