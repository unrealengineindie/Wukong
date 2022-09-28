// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeleeHitInterface.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AEnemyAIController;

UCLASS()
class WUKONG_API AEnemy : public ACharacter, public IMeleeHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Enemy Controller
	UPROPERTY()
	AEnemyAIController* EnemyAIController;
	
private:
	// Enemy name to display on HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName EnemyName;

	// Starting damage for enemy character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess = "true"))
	float BaseDamage;

	// Current health of enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	float Health;

	// Maximum allowed health of enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
	float MaxHealth;

public:

	// Override melee hit interface
	virtual  void MeleeHIt_Implementation(FHitResult HitResult) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Getters
	FORCEINLINE float GetBaseDamage() const { return  BaseDamage; }
};
