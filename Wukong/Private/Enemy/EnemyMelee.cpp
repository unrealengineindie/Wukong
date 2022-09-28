// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyMelee.h"

#include "Character/WukongCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyMelee::AEnemyMelee()
{
	// Right weapon collision box
	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Weapon Box"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponSocket"));

	// Left weapon collision box
	LeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Weapon Box"));
	LeftWeaponCollision->SetupAttachment(GetMesh(), FName("LeftWeaponSocket"));
}

void AEnemyMelee::ActivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Right Activate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AEnemyMelee::DeactivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Right Deactivate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyMelee::ActivateLeftWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Left Activate weapon"));
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AEnemyMelee::DeactivateLeftWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Left Deactivate weapon"));
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyMelee::BeginPlay()
{
	Super::BeginPlay();

	// Bind function to overlap event for weapon box
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyMelee::OnRightWeaponOverlap);
	LeftWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyMelee::OnLeftWeaponOverlap);
	
	// Setup right weapon collision box
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
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

void AEnemyMelee::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	auto Character = Cast<AWukongCharacter>(OtherActor);

	if (Character)
	{
		UGameplayStatics::ApplyDamage(Character, GetBaseDamage(), EnemyAIController, this, UDamageType::StaticClass());
	}
}

void AEnemyMelee::OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	auto Character = Cast<AWukongCharacter>(OtherActor);

	if (Character)
	{
		UGameplayStatics::ApplyDamage(Character, GetBaseDamage(), EnemyAIController, this, UDamageType::StaticClass());
	}
}

// @TODO Refactor this when doing behavior tree
// Called from enemy blueprint
void AEnemyMelee::MainMeleeAttack()
{
	// Logic to run anim montage attack from section
	MeleeAttack();
}
