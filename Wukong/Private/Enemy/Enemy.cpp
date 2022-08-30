// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"

// Sets default values
AEnemy::AEnemy() :
	Health(100.f),
	MaxHealth(100.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::MeleeHIt_Implementation(FHitResult HitResult)
{
	// Do impact sound

	// Play niagra affects

	// play hit montage
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (Health - DamageAmount <= 0.f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Died"));
	}
	else
	{
		Health -= DamageAmount;
	}

	return DamageAmount;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


